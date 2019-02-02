/*
 * lcd_i2c.c
 *
 *  Created on: 29Jan.,2019
 *      Author: Falcon
 */

#include "lcd_i2c.h"

void lcd_i2c_sendCmd(uint8_t cmd)
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


void lcd_i2c_sendData(char data)
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


void lcd_i2c_print(char string[]) //  doing char myArray = "hello" creates an array of characters
// char *string is equivalent to string[]
{
	int length = strlen(string); // We are passing the array to find the length of the string. Remember string[0] will return first  element and so on ...

	for (int i =0; i<length; i++)
	{
		lcd_i2c_sendData(string[i]); //
	}


}

void lcd_i2c_init()
{
	lcd_i2c_sendCmd(0x33);
	delay_mS(5);
	lcd_i2c_sendCmd(0x32);
	delay_mS(5);
	lcd_i2c_sendCmd(0x28);
	delay_mS(5);
	lcd_i2c_sendCmd(0x0E);
	delay_mS(5);
	lcd_i2c_sendCmd(0x01);
	delay_mS(5);
	lcd_i2c_sendCmd(0x80);
}

void lcd_i2c_clear()
{
	lcd_i2c_sendCmd(0x01);
	delay_mS(10); // Added delay because some LCD commands would not work
}



void lcd_i2c_goto_xy(int x, int y) // need to expand this for 2004a lcd
{
	if (y==1) // First row
	{
		lcd_i2c_sendCmd(0x80+x-1); // Minus 1, so you can write 1,1 for 1st row 1st column and not 0,1.
	}

	else // Second Row. This only works for 16x2. Need to change for 20 x 4 lcd sometime
	{
		lcd_i2c_sendCmd(0xC0+x-1);
	}



}
