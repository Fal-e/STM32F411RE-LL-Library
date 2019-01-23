/*
 * I2C_Library.c
 *
 *  Created on: 17Jan.,2019
 *      Author: Falcon
 */

#include "I2C_Library.h"


void I2C_enable()
{
	// I2C will not work unless the config_clock_50MHz(); is used before enabling I2C.
	int SCL = 6;
	int SDA = 7;

	// PORTB alternate mode setup pin 6 and 7
	GPIO_TYPE myI2C;
	myI2C.port = PORTB;
	myI2C.mode = ALT_MODE;

	myI2C.speed = SPEED_LOW;
	myI2C.alt_func = AF4;
	gpio_port_config(myI2C,(int []) {SCL,SDA},2);

	// Enabling clock for I2C
	RCC->APB1ENR |=RCC_APB1ENR_I2C1EN;


	// The APB clock frequency is 50 MHz.
	I2C1->CR2 |= 0b110010;
	// Standard I2C master mode
	I2C1->CCR &= ~I2C_CCR_FS;
	// Clock control register as 100 kHZ for an APB frequency of 50 MHz.
	// (2*100khz)^-1 = RCC*(1/50Mhz)
	I2C1->CCR |= 250;
	// Maximum rise time. In standard mode, the maximum SCL rise time is 1000ns. We have 50MHz apb freq
	// which is 20ns. 1000/20 +1 = 51
	I2C1->TRISE |= 51;

	// Peripheral Enable
	I2C1->CR1 |= I2C_CR1_PE;
}




void I2C_addressWrite(uint8_t i2c_address)
{

	I2C1->DR = (i2c_address<<1) & 0b11111110; //lsb is 0 (Reset), therefore master is in transmitter mode


	// EV6
	while(!(I2C1->SR1 & I2C_SR1_ADDR));
	while(!(I2C1->SR2 & I2C_SR2_BUSY));

}

void I2C_data(uint8_t i2c_data)
{
		I2C1->DR = i2c_data;
		while(!(I2C1->SR1 & I2C_SR1_TXE));

}

void I2C_stop()
{
	while (!(I2C1->SR1 & I2C_SR1_BTF)); // Byte transfer finished succeeded
	I2C1->CR1 |= I2C_CR1_STOP;

}


void I2C_start()
{
	//while(I2C1->SR2 & I2C_SR2_BUSY);// Unnecessary
	I2C1->CR1 |= I2C_CR1_START;
	while(!(I2C1->SR1 & I2C_SR1_SB)); // keep waiting until the SB bit has been set
}
