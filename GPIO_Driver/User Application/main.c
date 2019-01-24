
/* Includes */
#include "stm32f4xx.h"
#include "GPIO_Driver.h"
#include "Timer_Delay.h"
//#include "lcd_8bit.h"
#include "lcd_4bit.h"
#include "I2C_Library.h"

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


I2C1->CR2 = I2C_CR2_ITERREN;
NVIC_EnableIRQ(I2C1_ER_IRQn);

I2C_start();
I2C1->DR = (0x26<<1) & 0b11111110; //lsb is 0 (Reset), therefore master is in transmitter mode


// Need to add code that checks for acknowledge. If not acknowledged then skip the code below,
// otherwise run it.

//while(!(I2C1->SR1 & I2C_SR1_ADDR)); // Wait for Received Address matched

//while(!(I2C1->SR2 & I2C_SR2_BUSY));



I2C_start();

I2C_addressWrite(0x27);
I2C_data(0x27);
I2C_data(0x17);
I2C_stop();

gpio_write(PORTA,5,1);
// TODO: Code that handles NACK from slave.
// The program is currently stuck in an infinite loop in the I2C_data command
// Specifically: while(!(I2C1->SR1 & I2C_SR1_TXE));
// This is because when a NACK is received (e.g. wrong address), TXE is not set, therefore remaining in the loop.
// Need to fix this by adding an interrupt, which STOPs or restarts communication.
// Otherwise, will be stuck in loop and no more communication can continue.

//
}


void I2C1_ER_IRQHandler()
{
	I2C1->SR1 &= ~I2C_SR1_AF;
	I2C1->CR1 |= I2C_CR1_STOP;

	//while(I2C1->SR2 & I2C_SR2_BUSY);

	//I2C1->SR1 &= ~I2C_SR1_AF;
	//I2C1->CR1 |= I2C_CR1_STOP;

}











