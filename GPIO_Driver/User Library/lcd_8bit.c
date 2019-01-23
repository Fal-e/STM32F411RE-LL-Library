/*
 * lcd_8bit.c
 *
 *  Created on: 25Dec.,2018
 *      Author: Falcon
 */
/*
#include "lcd_8bit.h"
// Get the other includes from the lcd_8bit that are needed such as GPIO_Driver and Timer_Delay

void lcd_send_cmd(uint32_t command) // Send a command to the LCD. e.g. display on cursor on etc.
{
	gpio_port_clear(LCD_PORT_DATA,0xFFFF); //clear the GPIOA before sending the new command



	// This is used so that the pins don't have to be in order. For example you can have PA9 as D0 or D4
	// and the code would still work.
	 PORTA->BSRR = (0b00000001 & command)<<D0;
	 PORTA->BSRR = (0b00000010 & command)<<(D1-1); // E.g. you have PA9 as D1. This would shift the data 8 times (9-1)
	 PORTA->BSRR = (0b00000100 & command)<<(D2-2); // from bit 1, so that the correct data is held in bit 9.
	 PORTA->BSRR = (0b00001000 & command)<<(D3-3);
	 PORTA->BSRR = (0b00010000 & command)<<(D4-4);
	 PORTA->BSRR = (0b00100000 & command)<<(D5-5);
	 PORTA->BSRR = (0b01000000 & command)<<(D6-6);
	 PORTA->BSRR = (0b10000000 & command)<<(D7-7);





	 // Previous code, only worked for a specific scenario.
	//gpio_port_set(LCD_PORT_DATA,(((command & 0b00001100)<<6) | command) & 0xFFF3);

	gpio_write(LCD_PORT_CTRL,RS,0);
	gpio_write(LCD_PORT_CTRL,RW,0);

	gpio_write(LCD_PORT_CTRL,EN,1);
	delay_mS(5);
	gpio_write(LCD_PORT_CTRL,EN,0);


	delay_mS(5);
}


void lcd_send_data(char data) // Send a character to the LCD
{


	gpio_port_clear(LCD_PORT_DATA,0xFFFF); //clear the GPIOA before sending the new command

	 PORTA->BSRR = (0b00000001 & data)<<D0;
	 PORTA->BSRR = (0b00000010 & data)<<(D1-1); // E.g. you have PA9 as D1. This would shift the data 8 times (9-1)
	 PORTA->BSRR = (0b00000100 & data)<<(D2-2); // from bit 1, so that the correct data is held in bit 9.
	 PORTA->BSRR = (0b00001000 & data)<<(D3-3);
	 PORTA->BSRR = (0b00010000 & data)<<(D4-4);
	 PORTA->BSRR = (0b00100000 & data)<<(D5-5);
	 PORTA->BSRR = (0b01000000 & data)<<(D6-6);
	 PORTA->BSRR = (0b10000000 & data)<<(D7-7);


	//gpio_port_set(LCD_PORT_DATA,(((data & 0b00001100)<<6) | data) & 0xFFF3);

	gpio_write(LCD_PORT_CTRL,RS,1);
	gpio_write(LCD_PORT_CTRL,RW,0);


	// For 8-bit mode, only needs 1 pulse on the enable pin to send data
	gpio_write(LCD_PORT_CTRL,EN,1);
	delay_mS(5);
	gpio_write(LCD_PORT_CTRL,EN,0);
	//delay_mS(5); // Probably not needed


}


void lcd_print(char string[]) //  doing char myArray = "hello" creates an array of characters
// char *string is equivalent to string[]
{
	int length = strlen(string); // We are passing the array to find the length of the string. Remember string[0] will return first  element and so on ...

	for (int i =0; i<length; i++)
	{
		lcd_send_data(string[i]); //
	}


}


void lcd_init()
{
	 GPIO_TYPE myGPIO;
	myGPIO.port = LCD_PORT_DATA; // In the lcd_8bit.h file, this is GPIOA (PORTA)
	myGPIO.mode = OUTPUT_MODE;
	//myGPIO.speed = SPEED_V_HIGH;
	myGPIO.mode_type = OUTPUT_PUP;
	gpio_port_config(myGPIO,(int []) {D0,D1,D2,D3,D4,D5,D6,D7},8);

	GPIO_TYPE myCMD;
	myCMD.port = LCD_PORT_CTRL;
	myCMD.mode = OUTPUT_MODE;
	//myGPIO.speed = SPEED_V_HIGH;
	myCMD.mode_type = OUTPUT_PUP;
	gpio_port_config(myCMD,(int []) {EN,RS,RW},3);



	gpio_port_clear(LCD_PORT_DATA,0xFFFF);

	delay_mS(100);

	lcd_send_cmd(0x38); // Configure as 8-bit mode
	lcd_send_cmd(0x0E); // Display on, cursor on
	lcd_send_cmd(0x01); // clears the screen
	lcd_send_cmd(0x80); // sets the position to 1,1 C0 sets it to 2nd row 1st column



}

void lcd_clear()
{
	lcd_send_cmd(0x01);
}


// Changes the position of the character entry. x is 1, 2, 3 ... 16.
// 1 being the first, 16 being the last
// y is 1, for first row, 2 for second row.
// This is done for 16x2 LCD.
void lcd_goto_xy(int x, int y) // need to expand this for 2004a lcd
{
	if (y==1) // First row
	{
		lcd_send_cmd(0x80+x-1);
	}

	else // Second Row
	{
		lcd_send_cmd(0xC0+x-1);
	}



}
*/


