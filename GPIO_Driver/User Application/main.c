
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


void I2C_Enable();
void I2C_AddressWrite(uint8_t i2c_address);
void I2C_Data(uint8_t i2c_address);

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
I2C_enable();


//I2C1->CR2 = I2C_CR2_ITERREN;
//NVIC_EnableIRQ(I2C1_ER_IRQn);

I2C_start();
I2C_addressWrite(0x27);
I2C_data(0x33);
I2C_data(0x22);
I2C_data(0x28);
I2C_stop();


delay_mS(10);

I2C_start();
I2C_addressWrite(0x27);
I2C_data(0x33);
I2C_stop();






// TODO: Code that handles NACK from slave.
// The program is currently stuck in an infinite loop in the I2C_data command
// Specifically: while(!(I2C1->SR1 & I2C_SR1_TXE));
// This is because when a NACK is received (e.g. wrong address), TXE is not set, therefore remaining in the loop.
// Need to fix this by adding an interrupt, which STOPs or restarts communication.
// Otherwise, will be stuck in loop and no more communication can continue.





//
}


/*void I2C1_ER_IRQHandler()
{
	I2C1->SR1 = 0x00;
	//I2C1->SR1 &= ~I2C_SR1_AF;
	I2C_stop();
}
*/









