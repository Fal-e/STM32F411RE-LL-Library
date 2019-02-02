/*
 * lcd_i2c.c
 *
 *  Created on: 29Jan.,2019
 *      Author: Falcon
 */

#include "lcd_i2c.h"

/*

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

*/
