/*
 * ss_mpu6050.c
 *
 *  Created on: 11May,2019
 *      Author: Falcon
 */
#include "ss_mpu6050.h"
#include "I2C_Library.h"

uint16_t imu_accel_x(void)
{
	uint16_t accel_x;
	I2C_start();
	I2C_addressWrite(0x68); // I2C address of MPU6050
	I2C_data(59);  //Register address that is going to be read
	I2C_data(59);

	I2C_start();
	I2C_addressRead(0x68);
	accel_x |= I2C_dataRead()<<8;
	I2C_stop();
	return accel_x;

}