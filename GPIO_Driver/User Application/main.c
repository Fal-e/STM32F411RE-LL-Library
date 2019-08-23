
/* Includes */
#include "stm32f4xx.h"
#include "GPIO_Driver.h"
#include "Timer_Delay.h"
//#include "lcd_8bit.h"
#include "lcd_4bit.h"
#include "I2C_Library.h"
#include "lcd_i2c.h"
#include <stdlib.h>
#include "ss_mpu6050.h"

/* Private macro */
/* Private variables */
/* Private function prototypes */
/* Private functions */

/**
**===========================================================================
**
**  	GPIO Driver
**
**===========================================================================
*/

/* READ IMPORTANT
 *
 * The code below contains an three examples.
 * - It shows how to set up pins. For example how to set up the on-board LED and an analog pin.
 * - Shows how to use the custom I2C functions
 * - Shows how to use ADC and print to an 16 x 02 LCD screen via I2C
 *
 */


int main(void) {

    config_clock_50MHz();

    // Setting up PORT C Pin 0 as an analog input
    GPIO_TYPE myGPIO;
    myGPIO.port = PORTC;
    myGPIO.mode = ANALOG_MODE;
    gpio_port_config(myGPIO,(int []) {0},1); // 0 is the Pin number, 1 is the number of pins you want to configure
    // It is possible to setup multiple pins with the function above.

    /* Example below is how to set up the STM32F411RE on board LED.
     * It is not */
    GPIO_TYPE myLed;
    myLed.port = PORTA;
    myLed.mode = OUTPUT_MODE;
    myLed.mode_type = OUTPUT_PUP;
    gpio_port_config(myLed,(int []) {5},1);

    I2C_enable(); // Setting up I2C

/* Printing to LCD via I2C Example: */

/*for (int i = 0; i < 50; i++) {
	lcd_i2c_print("Suad");
	delay_mS(250);
	lcd_i2c_clear();
	//delay_mS(500);
	lcd_i2c_goto_xy(1,2);
	lcd_i2c_print("Shahini");
	delay_mS(250);
	lcd_i2c_clear();

} */


    char str[16];
    // Setting up ADC and printing it to the LCD via I2C
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    ADC1->SQR1 |= ADC_SQR1_L_0; // One conversion ->  0001. 1111
    ADC1->SQR3 |= ADC_SQR3_SQ1_1 | ADC_SQR3_SQ1_3; // 2 or 10, gives us 1100 which is 10. We want
    ADC1->CR2 |= ADC_CR2_CONT; // continous mode
    ADC1->CR2 |= ADC_CR2_ADON;
    // maybe put a check that adon is 1
    ADC1->CR2 |= ADC_CR2_SWSTART; // Continous Conversion Mode

    while(1) {
        int result = ADC1->DR;
        float new_result = result/819.0f;
        snprintf(str,6,"%f", new_result); //snprintf not supported in c99...?
        //ftoa(new_result, 3, str);
        //itoa(result, str, 10); // convert from integer to string
        lcd_i2c_print("Voltage: ");
        lcd_i2c_print(str);
        lcd_i2c_print("V");
        delay_mS(1000);
        lcd_i2c_clear();
    }

}





