/*
 * I2C_Library.h
 *
 *  Created on: 17Jan.,2019
 *      Author: Falcon
 */

#ifndef I2C_LIBRARY_H_
#define I2C_LIBRARY_H_

#include "GPIO_Driver.h"
#include "Timer_Delay.h"


void I2C_enable();
void I2C_addressWrite(uint8_t i2c_address);
void I2C_start();
void I2C_stop();
void I2C_data(uint8_t i2c_data);








#endif /* I2C_LIBRARY_H_ */