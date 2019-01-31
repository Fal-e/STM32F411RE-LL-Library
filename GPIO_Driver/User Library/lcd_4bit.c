/*
 * lcd_4bit.c
 *
 *  Created on: 26Dec.,2018
 *      Author: Falcon
 */
#include "lcd_4bit.h"
// Get the other includes from the lcd_4bit that are needed such as GPIO_Driver and Timer_Delay


// TODO
/*
 * PINOUT
 *
 * D7 D6 D5 D4 X  EN RW RS
 * P7 P6 P5 P4 P3 P2 P1 P0
 *
 * The I2C backpack is run in 4-bit mode
 * Therefore the high nibble is sent first and then the
 *
 */





void lcd_send_cmd(uint32_t command) // Send a command to the LCD. e.g. display on cursor on etc.
{
	gpio_port_clear(LCD_PORT_DATA,0xFFFF); //clear the GPIOA before sending the new command
	// maybe update this to only clear the pins that are being used, and not the whole port.



	gpio_write(LCD_PORT_CTRL,RS,0);
	gpio_write(LCD_PORT_CTRL,RW,0);



	// High nibble gets sent first
	LCD_PORT_DATA->BSRR = (0b00010000 & command)<<(D4-4);
	LCD_PORT_DATA->BSRR = (0b00100000 & command)<<(D5-5);
	LCD_PORT_DATA->BSRR = (0b01000000 & command)<<(D6-6);
	LCD_PORT_DATA->BSRR = (0b10000000 & command)<<(D7-7);

	// Send the high nibble, by doing a high to low pulse on the enable pin
	gpio_write(LCD_PORT_CTRL,EN,1);
	delay_mS(5);
	gpio_write(LCD_PORT_CTRL,EN,0);
	delay_mS(5);


	gpio_port_clear(LCD_PORT_DATA,0xFFFF);

	// Low nibble gets sent after high nibble
	LCD_PORT_DATA->BSRR = (0b00000001 & command)<<(D4);
	LCD_PORT_DATA->BSRR = (0b00000010 & command)<<(D5-1); // because you start at bit 0.
	LCD_PORT_DATA->BSRR = (0b00000100 & command)<<(D6-2); // e.g. D5 is PA7. 7-1 = 6.
	LCD_PORT_DATA->BSRR = (0b00001000 & command)<<(D7-3); // Therefore the bit needs to be shifted 6 times.

	gpio_write(LCD_PORT_CTRL,EN,1);
	delay_mS(5);
	gpio_write(LCD_PORT_CTRL,EN,0);
	delay_mS(5);


}


void lcd_send_data(char data) // Send a character to the LCD
{

	gpio_port_clear(LCD_PORT_DATA,0xFFFF); //clear the GPIOA before sending the new command

	gpio_write(LCD_PORT_CTRL,RS,1);
	gpio_write(LCD_PORT_CTRL,RW,0);


	// High nibble gets sent first
	LCD_PORT_DATA->BSRR = (0b00010000 & data)<<(D4-4);
	LCD_PORT_DATA->BSRR = (0b00100000 & data)<<(D5-5);
	LCD_PORT_DATA->BSRR = (0b01000000 & data)<<(D6-6);
	LCD_PORT_DATA->BSRR = (0b10000000 & data)<<(D7-7);

		// Send the high nibble, by doing a high to low pulse on the enable pin
	gpio_write(LCD_PORT_CTRL,EN,1);
	delay_mS(5);
	gpio_write(LCD_PORT_CTRL,EN,0);
	delay_mS(5);

	gpio_port_clear(LCD_PORT_DATA,0xFFFF);

		// Low nibble gets sent after high nibble
	LCD_PORT_DATA->BSRR = (0b00000001 & data)<<(D4);
	LCD_PORT_DATA->BSRR = (0b00000010 & data)<<(D5-1);
	LCD_PORT_DATA->BSRR = (0b00000100 & data)<<(D6-2);
	LCD_PORT_DATA->BSRR = (0b00001000 & data)<<(D7-3);

	gpio_write(LCD_PORT_CTRL,EN,1);
	delay_mS(5);
	gpio_write(LCD_PORT_CTRL,EN,0);
	delay_mS(5);





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
	gpio_port_config(myGPIO,(int []) {D4,D5,D6,D7},4);

	GPIO_TYPE myCMD;
	myCMD.port = LCD_PORT_CTRL;
	myCMD.mode = OUTPUT_MODE;
	//myGPIO.speed = SPEED_V_HIGH;
	myCMD.mode_type = OUTPUT_PUP;
	gpio_port_config(myCMD,(int []) {EN,RS,RW},3);


	gpio_port_clear(LCD_PORT_DATA,0xFFFF);


	delay_mS(100);

	lcd_send_cmd(0x33);
	lcd_send_cmd(0x32);
	lcd_send_cmd(0x28); // Configure as 4-bit mode
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
		lcd_send_cmd(0x80+x-1); // Minus 1, so you can write 1,1 for 1st row 1st column and not 0,1.
	}

	else // Second Row
	{
		lcd_send_cmd(0xC0+x-1);
	}



}

