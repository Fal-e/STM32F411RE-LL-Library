
/* Includes */
#include "stm32f4xx.h"
#include "GPIO_Driver.h"
#include "Timer_Delay.h"
//#include "lcd_8bit.h"
#include "lcd_4bit.h"
#include "I2C_Library.h"
#include "lcd_i2c.h"
#include <stdlib.h>


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



int main(void)
{

/*config_clock_50MHz(); // Configuring the delays, as well as setting the clk freq
lcd_init();
lcd_goto_xy(2,1);
lcd_print("Suad");
lcd_goto_xy(4,2);
lcd_print("Shahini");
//delay_mS(2000);
*/

 config_clock_50MHz();


GPIO_TYPE myGPIO;
myGPIO.port = PORTC;
myGPIO.mode = ANALOG_MODE;
gpio_port_config(myGPIO,(int []) {0},1);


I2C_enable();
lcd_i2c_clear();

// Read data sheet for the GPIO expander in STM32 folder.
// The first data bit sent to the GPIO expander is whether it is input/output etc.


lcd_i2c_init();



/*for (int i = 0; i < 50; i++) {
	lcd_i2c_print("Suad");
	delay_mS(250);
	lcd_i2c_clear();
	//delay_mS(500);
	lcd_i2c_goto_xy(1,2);
	lcd_i2c_print("The King");
	delay_mS(250);
	lcd_i2c_clear();

}
*/


char str[16]; // Temporary placement


RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
ADC1->SQR1 |= ADC_SQR1_L_0; // One conversion ->  0001. 1111
ADC1->SQR3 |= ADC_SQR3_SQ1_1 | ADC_SQR3_SQ1_3; // 2 or 10, gives us 1100 which is 10. We want
ADC1->CR2 |= ADC_CR2_CONT; // continous mode
ADC1->CR2 |= ADC_CR2_ADON;
// maybe put a check that adon is 1
ADC1->CR2 |= ADC_CR2_SWSTART; // Continous Conversion Mode

while(1){
int result = ADC1->DR;
itoa(result, str, 10); // convert from integer to string
lcd_i2c_print(str);
delay_mS(1000);
lcd_i2c_clear();
}

// ADC on/off
// ADON in ADC_CR2 register.

// Conversion start
// SWSTART or JSWSTART is set

// Conversion stop clear ADON bit

// ADCLK is generated from APB2 clock. Ours is 50 MHz.
// Programmable prescalar allowed e.g. /2 /2 /6 /8


// We want to read the temperature and display it on the LCD.



// Need to add code that checks for acknowledge. If not acknowledged then skip the code below,
// otherwise run it.

//while(!(I2C1->SR1 & I2C_SR1_ADDR)); // Wait for Received Address matched

//while(!(I2C1->SR2 & I2C_SR2_BUSY));






// TODO: Code that handles NACK from slave.
// The program is currently stuck in an infinite loop in the I2C_data command
// Specifically: while(!(I2C1->SR1 & I2C_SR1_TXE));
// This is because when a NACK is received (e.g. wrong address), TXE is not set, therefore remaining in the loop.
// Need to fix this by adding an interrupt, which STOPs or restarts communication.
// Otherwise, will be stuck in loop and no more communication can continue.

//
}





