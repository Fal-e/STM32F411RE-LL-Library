/*
 * lcd_i2c.h
 *
 *  Created on: 29Jan.,2019
 *      Author: Falcon
 */

#ifndef LCD_I2C_H_
#define LCD_I2C_H_

#include "stm32f4xx.h"
#include <stdint.h>
#include "GPIO_Driver.h"
#include "Timer_Delay.h"
#include <string.h>
#include "I2C_Library.h"



void lcd_i2c_sendCmd(uint8_t cmd);
void lcd_i2c_sendData(char data);
void lcd_i2c_print(char string[]);
void lcd_i2c_init();
void lcd_i2c_clear();
void lcd_i2c_goto_xy(int x, int y);




#endif /* LCD_I2C_H_ */
