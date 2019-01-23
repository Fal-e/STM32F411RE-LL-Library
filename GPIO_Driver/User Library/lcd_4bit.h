/*
 * lcd_4bit.h
 *
 *  Created on: 26Dec.,2018
 *      Author: Falcon
 */

#ifndef LCD_4BIT_H_
#define LCD_4BIT_H_

#include "stm32f4xx.h"
#include <stdint.h>
#include "GPIO_Driver.h"
#include "Timer_Delay.h"
#include <string.h>


// These pins are working on the assumption that only one PORT is being used.
// These can be changed, however all the pins must be on the same port, otherwise new code must be written.

#define D4 4 // For example this is PORTA PIN 4, PA4
#define D5 5
#define D6 6
#define D7 7

#define LCD_PORT_DATA PORTA // GPIOA. This is the port that the LCD data pins are on



// ***************************************************************
//						POSSIBLE IMPROVEMENTS
//****************************************************************
// The code can be made even more robust. It can be made able to work with any pin from any port.
// This can be done by:
//		*Create more defines. Instead of one LCD_PORT_DATA, have LCD_PORT_D1, LCD_PORT_D2, etc...
//		*Create a for loop in lcd_4bit.c init function that enables the pins as output via GPIO_Driver function
//		*Each bitwise operation can be changed from LCD_PORT_DATA->BSRR, to LCD_PORT_D1->BSRR


// Enable, Register select and Read/Write pins
// These may be changed, but the code works on the assumption that they are on the same port.
#define EN 10 // PB10
#define RS 3 // PB3`
#define RW 4 //PB4

#define LCD_PORT_CTRL PORTB //GPIOB. This the the port the control pins are on


void lcd_send_cmd(uint32_t command);
void lcd_send_data(char data);
void lcd_print(char string[]);
void lcd_init();
void lcd_clear();
void lcd_goto_xy(int x, int y);

#endif /* LCD_4BIT_H_ */
