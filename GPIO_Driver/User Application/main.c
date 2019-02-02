
/* Includes */
#include "stm32f4xx.h"
#include "GPIO_Driver.h"
#include "Timer_Delay.h"
//#include "lcd_8bit.h"
#include "lcd_4bit.h"
#include "I2C_Library.h"
#include "lcd_i2c.h"

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
myGPIO.port = PORTA;
myGPIO.mode = OUTPUT_MODE;
myGPIO.mode_type = OUTPUT_PUP;
gpio_port_config(myGPIO,(int []) {5},1);


I2C_enable();


// Read data sheet for the GPIO expander in STM32 folder.
// The first data bit sent to the GPIO expander is whether it is input/output etc.


lcd_i2c_init();



for (int i = 0; i < 50; i++) {
	lcd_i2c_print("Suad");
	delay_mS(250);
	lcd_i2c_clear();
	//delay_mS(500);
	lcd_i2c_goto_xy(1,2);
	lcd_i2c_print("The King");
	delay_mS(250);
	lcd_i2c_clear();

}

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




