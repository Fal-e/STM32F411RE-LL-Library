
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

void sendCmd(uint8_t cmd);
void sendData(char data);

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


sendCmd(0x33);
delay_mS(5);
sendCmd(0x32);
delay_mS(5);
sendCmd(0x28);
delay_mS(5);
sendCmd(0x0E);
delay_mS(5);
sendCmd(0x01);
delay_mS(5);
sendCmd(0x80);


sendData(83);
sendData(85);
sendData(65);
sendData(68);




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



void sendCmd(uint8_t cmd)
{

I2C_start();
I2C_addressWrite(0x27); //hard coded address for testing purposes
// upper nibble
I2C_data((cmd&0xF0)|0b1100); //0x0C  is 1 1 0 0. i.e. enable 1
I2C_data((cmd&0xF0)|0b1000); //0x08  is 1 0 0 0 i.e. enable 0
// lower nibble
I2C_data(((cmd<<4)&0xF0)|0b1100);
I2C_data(((cmd<<4)&0xF0)|0b1000);
I2C_stop();

}


void sendData(char data)
{

I2C_start();
I2C_addressWrite(0x27); //hard coded for testing purposes
//									       EN RW RS    P3 is the backlight. P3 =1, backlight is on
// upper nibble				  //		P3 P2 P1 P0
I2C_data((data&0xF0)|0b1101); //0x0C is  1  1  0  0. i.e. enable 1 RS=1
I2C_data((data&0xF0)|0b1001); //0x08  is 1 0 0 0 i.e. enable 0 RS=1
// lower nibble
I2C_data(((data<<4)&0xF0)|0b1101);
I2C_data(((data<<4)&0xF0)|0b1001);
I2C_stop();

}







