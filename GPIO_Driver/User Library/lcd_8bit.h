/*
 * lcd_8bit.h
 *
 *  Created on: 25Dec.,2018
 *      Author: Falcon
 */

#ifndef LCD_8BIT_H_
#define LCD_8BIT_H_


#include "stm32f4xx.h"
#include <stdint.h>
#include "GPIO_Driver.h"
#include "Timer_Delay.h"
#include <string.h>


// These pins are working on the assumption that only one PORT is being used.
// These can be changed, however all the pins must be on the same port, otherwise new code must be written.
#define D0 0
#define D1 1
#define D2 8
#define D3 9
#define D4 4
#define D5 5
#define D6 6
#define D7 7

#define LCD_PORT_DATA PORTA // GPIOA. This is the port that the LCD data pins are on




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




#endif /* LCD_8BIT_H_ */
