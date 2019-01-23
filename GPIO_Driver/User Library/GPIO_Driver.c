/*
 * GPIO_Driver.c
 *
 *  Created on: 7Dec.,2018
 *      Author: Falcon
 */

#include "GPIO_Driver.h"
#include <stdint.h>

// array of type uint32_t
uint32_t PINPOS[16] = { //Needed for registers that have 2 bits for 1 I/O pin
		(0x00), //pin 0 starts at 0
		(0x02), //pin 1 starts at 2
		(0x04),
		(0x06),
		(0x08),
		(0x0A),
		(0x0C),
		(0x0E), //pin 7
		(0x10), //pin 8
		(0x12), //pin 9
		(0x14),
		(0x16),
		(0x18),
		(0x1A),
		(0x1C),
		(0x1E), //Pin 15 starts at 30 which is 1E in HEX
};


uint32_t alt_PINPOS[16] = {
		(0x00), //pin 0
		(0x04), //1
		(0x08), //2
		(0x0C), //3
		(0x10), //4
		(0x14), //5
		(0x18), //6
		(0x1C), //7

};

 static void config_pin(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t pinSpeed, uint32_t mode, uint16_t mode_type, uint32_t alt_func)
{

	if(mode == OUTPUT_MODE)
	{
		port->MODER |= (1<<PINPOS[pinNumber]);
		port->MODER &= ~(1<<PINPOS[pinNumber]+1);


			if(mode_type == OUTPUT_PUP)
			{
				port->OTYPER &= ~(1<<pinNumber);
			}

			if(mode_type == OUTPUT_OD)
			{
				port->OTYPER |= (1<<pinNumber);
			}


			switch(pinSpeed)
			{
			//Output speed
			case (SPEED_LOW):
			port->OSPEEDR &= ~(1<<PINPOS[pinNumber]) & ~(1<<PINPOS[pinNumber+1]); // Putting a 00
			break;

			case (SPEED_MEDIUM): //Putting a 01
			port->OSPEEDR |= (1<<PINPOS[pinNumber]);
			port->OSPEEDR &= ~(1<<PINPOS[pinNumber+1]);
			break;

			case (SPEED_HIGH): //Putting a 10
			port->OSPEEDR &= ~(1<<PINPOS[pinNumber]);
			port->OSPEEDR |= (1<<PINPOS[pinNumber+1]);
			break;

			case (SPEED_V_HIGH): //Putting a 11
			port->OSPEEDR |= (1<<PINPOS[pinNumber]);
			port->OSPEEDR |= (1<<PINPOS[pinNumber+1]);
			break;

			}

		}

	else
	{
		switch(mode)
					{

					case (INPUT_MODE): //00
					port->MODER &= ~(1<<PINPOS[pinNumber]) & ~(1<<PINPOS[pinNumber+1]);
					break;

					case (ALT_MODE): //10
					port->MODER &= ~(1<<PINPOS[pinNumber]);
					port->MODER |= (1<<(PINPOS[pinNumber]+1));
					break;

					case (ANALOG_MODE): //11
					port->MODER |= (1<<PINPOS[pinNumber]);
					port->MODER |= (1<<(PINPOS[pinNumber]+1));
					break;

					}

	}

	if (mode == ALT_MODE)
	{
		if (pinNumber <=7) //Low Register, AFRL
		{
			switch(alt_func)
				{

				case (AF0):
				port->AFR[0] &= ~(1<<alt_PINPOS[pinNumber]); // 0 in 1st position
				port->AFR[0] &= ~(1<<(alt_PINPOS[pinNumber]+1)); // 0 in 2nd position
				port->AFR[0] &= ~(1<<(alt_PINPOS[pinNumber]+2)); // 0 in 3rd position
				port->AFR[0] &= ~(1<<(alt_PINPOS[pinNumber]+3)); //0 in 4th position
				break;

				case (AF1):
				port->AFR[0] |= (1<<alt_PINPOS[pinNumber]); 	//1 in 1st position
				port->AFR[0] &= ~(1<<(alt_PINPOS[pinNumber]+1)); // 0 in 2nd position
				port->AFR[0] &= ~(1<<(alt_PINPOS[pinNumber]+2)); // 0 in 3rd position
				port->AFR[0] &= ~(1<<(alt_PINPOS[pinNumber]+3)); //0 in 4th position

				break;

				case (AF2):
				port->AFR[0] &= ~(1<<alt_PINPOS[pinNumber]); // 0 in 1st position
				port->AFR[0] |= (1<<(alt_PINPOS[pinNumber]+1)); //1 in 2nd position
				port->AFR[0] &= ~(1<<(alt_PINPOS[pinNumber]+2)); // 0 in 3rd position
				port->AFR[0] &= ~(1<<(alt_PINPOS[pinNumber]+3)); //0 in 4th position
				break;

				case (AF3):
				port->AFR[0] |= (1<<alt_PINPOS[pinNumber]); 	//1 in 1st position
				port->AFR[0] |= (1<<(alt_PINPOS[pinNumber]+1)); 	//1 in 2nd position
				port->AFR[0] &= ~(1<<(alt_PINPOS[pinNumber]+2)); // 0 in 3rd position
				port->AFR[0] &= ~(1<<(alt_PINPOS[pinNumber]+3)); //0 in 4th position
				break;

				case (AF4):
				port->AFR[0] &= ~(1<<alt_PINPOS[pinNumber]); // 0 in 1st position
				port->AFR[0] &= ~(1<<(alt_PINPOS[pinNumber]+1)); // 0 in 2nd position
				port->AFR[0] |= (1<<(alt_PINPOS[pinNumber]+2)); //1 in 3rd position
				port->AFR[0] &= ~(1<<(alt_PINPOS[pinNumber]+3)); //0 in 4th position
				break;

				case (AF5):
				port->AFR[0] |= (1<<alt_PINPOS[pinNumber]); 	//1 in 1st position
				port->AFR[0] &= ~(1<<(alt_PINPOS[pinNumber]+1)); // 0 in 2nd position
				port->AFR[0] |= (1<<(alt_PINPOS[pinNumber]+2)); //1 in 3rd position
				port->AFR[0] &= ~(1<<(alt_PINPOS[pinNumber]+3)); //0 in 4th position
				break;

				case (AF6):
				port->AFR[0] &= ~(1<<alt_PINPOS[pinNumber]); // 0 in 1st position
				port->AFR[0] |= (1<<(alt_PINPOS[pinNumber]+1)); //1 in 2nd position
				port->AFR[0] |= (1<<(alt_PINPOS[pinNumber]+2)); //1 in 3rd position
				port->AFR[0] &= ~(1<<(alt_PINPOS[pinNumber]+3)); //0 in 4th position
				break;

				case (AF7):
				port->AFR[0] |= (1<<alt_PINPOS[pinNumber]); 	//1 in 1st position
				port->AFR[0] |= (1<<(alt_PINPOS[pinNumber]+1)); //1 in 2nd position
				port->AFR[0] |= (1<<(alt_PINPOS[pinNumber]+2)); //1 in 3rd position
				port->AFR[0] &= ~(1<<(alt_PINPOS[pinNumber]+3)); //0 in 4th position
				break;

				case (AF8):
				port->AFR[0] &= ~(1<<alt_PINPOS[pinNumber]); // 0 in 1st position
				port->AFR[0] &= ~(1<<(alt_PINPOS[pinNumber]+1)); // 0 in 2nd position
				port->AFR[0] &= ~(1<<(alt_PINPOS[pinNumber]+2)); // 0 in 3rd position
				port->AFR[0] |= (1<<(alt_PINPOS[pinNumber]+3)); //1 in 4th position
				break;

				case (AF9):
				port->AFR[0] |= (1<<alt_PINPOS[pinNumber]); 	//1 in 1st position
				port->AFR[0] &= ~(1<<(alt_PINPOS[pinNumber]+1)); // 0 in 2nd position
				port->AFR[0] &= ~(1<<(alt_PINPOS[pinNumber]+2)); // 0 in 3rd position
				port->AFR[0] |= (1<<(alt_PINPOS[pinNumber]+3)); //1 in 4th position
				break;

				case (AF10):
				port->AFR[0] &= ~(1<<alt_PINPOS[pinNumber]); // 0 in 1st position
				port->AFR[0] |= (1<<(alt_PINPOS[pinNumber]+1)); //1 in 2nd position
				port->AFR[0] &= ~(1<<(alt_PINPOS[pinNumber]+2)); // 0 in 3rd position
				port->AFR[0] |= (1<<(alt_PINPOS[pinNumber]+3)); //1 in 4th position
				break;

				case (AF11):
				port->AFR[0] |= (1<<alt_PINPOS[pinNumber]); 	//1 in 1st position
				port->AFR[0] |= (1<<(alt_PINPOS[pinNumber]+1)); //1 in 2nd position
				port->AFR[0] &= ~(1<<(alt_PINPOS[pinNumber]+2)); // 0 in 3rd position
				port->AFR[0] |= (1<<(alt_PINPOS[pinNumber]+3)); //1 in 4th position
				break;

				case (AF12):
				port->AFR[0] &= ~(1<<alt_PINPOS[pinNumber]); // 0 in 1st position
				port->AFR[0] &= ~(1<<(alt_PINPOS[pinNumber]+1)); // 0 in 2nd position
				port->AFR[0] |= (1<<(alt_PINPOS[pinNumber]+2)); //1 in 3rd position
				port->AFR[0] |= (1<<(alt_PINPOS[pinNumber]+3)); //1 in 4th position
				break;

				case (AF13):
				port->AFR[0] |= (1<<alt_PINPOS[pinNumber]); 	//1 in 1st position
				port->AFR[0] &= ~(1<<(alt_PINPOS[pinNumber]+1)); // 0 in 2nd position
				port->AFR[0] |= (1<<(alt_PINPOS[pinNumber]+2)); //1 in 3rd position
				port->AFR[0] |= (1<<(alt_PINPOS[pinNumber]+3)); //1 in 4th position
				break;

				case (AF14):
				port->AFR[0] &= ~(1<<alt_PINPOS[pinNumber]); // 0 in 1st position
				port->AFR[0] |= (1<<(alt_PINPOS[pinNumber]+1)); //1 in 2nd position
				port->AFR[0] |= (1<<(alt_PINPOS[pinNumber]+2)); //1 in 3rd position
				port->AFR[0] |= (1<<(alt_PINPOS[pinNumber]+3)); //1 in 4th position
				break;

				case (AF15):
				port->AFR[0] |= (1<<alt_PINPOS[pinNumber]); 	//1 in 1st position
				port->AFR[0] |= (1<<(alt_PINPOS[pinNumber]+1)); //1 in 2nd position
				port->AFR[0] |= (1<<(alt_PINPOS[pinNumber]+2)); //1 in 3rd position
				port->AFR[0] |= (1<<(alt_PINPOS[pinNumber]+3)); //1 in 4th position
				break;

				}



		}

		else // High Register, AFRH
		{
			switch(alt_func)
				{

				case (AF0):
				port->AFR[1] &= ~(1<<alt_PINPOS[pinNumber]); // 0 in 1st position
				port->AFR[1] &= ~(1<<(alt_PINPOS[pinNumber]+1)); // 0 in 2nd position
				port->AFR[1] &= ~(1<<(alt_PINPOS[pinNumber]+2)); // 0 in 3rd position
				port->AFR[1] &= ~(1<<(alt_PINPOS[pinNumber]+3)); //0 in 4th position
				break;

				case (AF1):
				port->AFR[1] |= (1<<alt_PINPOS[pinNumber]); 	//1 in 1st position
				port->AFR[1] &= ~(1<<(alt_PINPOS[pinNumber]+1)); // 0 in 2nd position
				port->AFR[1] &= ~(1<<(alt_PINPOS[pinNumber]+2)); // 0 in 3rd position
				port->AFR[1] &= ~(1<<(alt_PINPOS[pinNumber]+3)); //0 in 4th position

				break;

				case (AF2):
				port->AFR[1] &= ~(1<<alt_PINPOS[pinNumber]); // 0 in 1st position
				port->AFR[1] |= (1<<(alt_PINPOS[pinNumber]+1)); //1 in 2nd position
				port->AFR[1] &= ~(1<<(alt_PINPOS[pinNumber]+2)); // 0 in 3rd position
				port->AFR[1] &= ~(1<<(alt_PINPOS[pinNumber]+3)); //0 in 4th position
				break;

				case (AF3):
				port->AFR[1] |= (1<<alt_PINPOS[pinNumber]); 	//1 in 1st position
				port->AFR[1] |= (1<<(alt_PINPOS[pinNumber]+1)); 	//1 in 2nd position
				port->AFR[1] &= ~(1<<(alt_PINPOS[pinNumber]+2)); // 0 in 3rd position
				port->AFR[1] &= ~(1<<(alt_PINPOS[pinNumber]+3)); //0 in 4th position
				break;

				case (AF4):
				port->AFR[1] &= ~(1<<alt_PINPOS[pinNumber]); // 0 in 1st position
				port->AFR[1] &= ~(1<<(alt_PINPOS[pinNumber]+1)); // 0 in 2nd position
				port->AFR[1] |= (1<<(alt_PINPOS[pinNumber]+2)); //1 in 3rd position
				port->AFR[1] &= ~(1<<(alt_PINPOS[pinNumber]+3)); //0 in 4th position
				break;

				case (AF5):
				port->AFR[1] |= (1<<alt_PINPOS[pinNumber]); 	//1 in 1st position
				port->AFR[1] &= ~(1<<(alt_PINPOS[pinNumber]+1)); // 0 in 2nd position
				port->AFR[1] |= (1<<(alt_PINPOS[pinNumber]+2)); //1 in 3rd position
				port->AFR[1] &= ~(1<<(alt_PINPOS[pinNumber]+3)); //0 in 4th position
				break;

				case (AF6):
				port->AFR[1] &= ~(1<<alt_PINPOS[pinNumber]); // 0 in 1st position
				port->AFR[1] |= (1<<(alt_PINPOS[pinNumber]+1)); //1 in 2nd position
				port->AFR[1] |= (1<<(alt_PINPOS[pinNumber]+2)); //1 in 3rd position
				port->AFR[1] &= ~(1<<(alt_PINPOS[pinNumber]+3)); //0 in 4th position
				break;

				case (AF7):
				port->AFR[1] |= (1<<alt_PINPOS[pinNumber]); 	//1 in 1st position
				port->AFR[1] |= (1<<(alt_PINPOS[pinNumber]+1)); //1 in 2nd position
				port->AFR[1] |= (1<<(alt_PINPOS[pinNumber]+2)); //1 in 3rd position
				port->AFR[1] &= ~(1<<(alt_PINPOS[pinNumber]+3)); //0 in 4th position
				break;

				case (AF8):
				port->AFR[1] &= ~(1<<alt_PINPOS[pinNumber]); // 0 in 1st position
				port->AFR[1] &= ~(1<<(alt_PINPOS[pinNumber]+1)); // 0 in 2nd position
				port->AFR[1] &= ~(1<<(alt_PINPOS[pinNumber]+2)); // 0 in 3rd position
				port->AFR[1] |= (1<<(alt_PINPOS[pinNumber]+3)); //1 in 4th position
				break;

				case (AF9):
				port->AFR[1] |= (1<<alt_PINPOS[pinNumber]); 	//1 in 1st position
				port->AFR[1] &= ~(1<<(alt_PINPOS[pinNumber]+1)); // 0 in 2nd position
				port->AFR[1] &= ~(1<<(alt_PINPOS[pinNumber]+2)); // 0 in 3rd position
				port->AFR[1] |= (1<<(alt_PINPOS[pinNumber]+3)); //1 in 4th position
				break;

				case (AF10):
				port->AFR[1] &= ~(1<<alt_PINPOS[pinNumber]); // 0 in 1st position
				port->AFR[1] |= (1<<(alt_PINPOS[pinNumber]+1)); //1 in 2nd position
				port->AFR[1] &= ~(1<<(alt_PINPOS[pinNumber]+2)); // 0 in 3rd position
				port->AFR[1] |= (1<<(alt_PINPOS[pinNumber]+3)); //1 in 4th position
				break;

				case (AF11):
				port->AFR[1] |= (1<<alt_PINPOS[pinNumber]); 	//1 in 1st position
				port->AFR[1] |= (1<<(alt_PINPOS[pinNumber]+1)); //1 in 2nd position
				port->AFR[1] &= ~(1<<(alt_PINPOS[pinNumber]+2)); // 0 in 3rd position
				port->AFR[1] |= (1<<(alt_PINPOS[pinNumber]+3)); //1 in 4th position
				break;

				case (AF12):
				port->AFR[1] &= ~(1<<alt_PINPOS[pinNumber]); // 0 in 1st position
				port->AFR[1] &= ~(1<<(alt_PINPOS[pinNumber]+1)); // 0 in 2nd position
				port->AFR[1] |= (1<<(alt_PINPOS[pinNumber]+2)); //1 in 3rd position
				port->AFR[1] |= (1<<(alt_PINPOS[pinNumber]+3)); //1 in 4th position
				break;

				case (AF13):
				port->AFR[1] |= (1<<alt_PINPOS[pinNumber]); 	//1 in 1st position
				port->AFR[1] &= ~(1<<(alt_PINPOS[pinNumber]+1)); // 0 in 2nd position
				port->AFR[1] |= (1<<(alt_PINPOS[pinNumber]+2)); //1 in 3rd position
				port->AFR[1] |= (1<<(alt_PINPOS[pinNumber]+3)); //1 in 4th position
				break;

				case (AF14):
				port->AFR[1] &= ~(1<<alt_PINPOS[pinNumber]); // 0 in 1st position
				port->AFR[1] |= (1<<(alt_PINPOS[pinNumber]+1)); //1 in 2nd position
				port->AFR[1] |= (1<<(alt_PINPOS[pinNumber]+2)); //1 in 3rd position
				port->AFR[1] |= (1<<(alt_PINPOS[pinNumber]+3)); //1 in 4th position
				break;


				case (AF15):
				port->AFR[1] |= (1<<alt_PINPOS[pinNumber]); 	//1 in 1st position
				port->AFR[1] |= (1<<(alt_PINPOS[pinNumber]+1)); //1 in 2nd position
				port->AFR[1] |= (1<<(alt_PINPOS[pinNumber]+2)); //1 in 3rd position
				port->AFR[1] |= (1<<(alt_PINPOS[pinNumber]+3)); //1 in 4th position
				break;
				}
		}


	}
}


void gpio_init(GPIO_TYPE gpio_type)
{
	if(gpio_type.port==PORTA)
		GPIO_CLOCK_ENABLE_PORTA;
	if(gpio_type.port==PORTB)
			GPIO_CLOCK_ENABLE_PORTB;
	if(gpio_type.port==PORTC)
			GPIO_CLOCK_ENABLE_PORTC;
	if(gpio_type.port==PORTD)
			GPIO_CLOCK_ENABLE_PORTD;

	config_pin(gpio_type.port,gpio_type.pin,gpio_type.speed,gpio_type.mode, gpio_type.mode_type,gpio_type.alt_func);

}





void gpio_write(GPIO_TypeDef *port, uint32_t pinNumber, uint8_t state)
{
	if(state==1)
	{
		port->BSRR=(1<<pinNumber);
	}
	else
	{
		port->BSRR = (1<<(pinNumber+16));
	}
}



/**
 * @brief Configures desired number of pins as input/output/alternate as well as the output mode (mode_type) and output speed.
 * @param myPins : GPIO pin numbers. Enter as an array.
 * @param numPins : The number of GPIO pins you want to configure.
 * @retval None
 * @example : gpio_port_config(myGPIO,(int []) {1, 2, 3, 5},4);
 */
void gpio_port_config(GPIO_TYPE gpio_type, int myPins[], int numPins)
{

	if(gpio_type.port==PORTA)
			GPIO_CLOCK_ENABLE_PORTA;
		if(gpio_type.port==PORTB)
				GPIO_CLOCK_ENABLE_PORTB;
		if(gpio_type.port==PORTC)
				GPIO_CLOCK_ENABLE_PORTC;
		if(gpio_type.port==PORTD)
				GPIO_CLOCK_ENABLE_PORTD;


	for (int i = 0; i<numPins; i++)
	{
			gpio_type.pin= myPins[i];
		config_pin(gpio_type.port,gpio_type.pin,gpio_type.speed,gpio_type.mode, gpio_type.mode_type,gpio_type.alt_func);

	}


}




/**
 * @brief Allows multiple pins of a port to be set HIGH
 * @param *port : Port of GPIO you want to set.
 * @param pins : The pins you want to set HIGH in either hex, binary or decimal.
 * @retval None
 * @example : gpio_port_set(PORTA,0x0f);
 * @example : gpio_port_set(PORTA,15);
 * @example : gpio_port_set(PORTA,0b1111);
 * @note : Maximum pins you could set would be 0xFFFF (pin 0 to pin 15).
 */
void gpio_port_set(GPIO_TypeDef *port, uint32_t pins)
{

	port->BSRR=pins;

}


/**
 * @brief Allows multiple pins of a port to be CLEARED (LOW)
 * @param *port : Port of GPIO you want to clear
 * @param pins : The pins you want to set LOW in either hex, binary or decimal.
 * @retval None
 * @example : gpio_port_set(PORTA,0x0f);
 * @example : gpio_port_set(PORTA,15);
 * @example : gpio_port_set(PORTA,0b1111);
 * @note : Maximum pins you could clear would be 0xFFFF (pin 0 to pin 15).
 */
void gpio_port_clear(GPIO_TypeDef *port, uint32_t pins)
{

	port->BSRR=pins<<16; //shift all the bits 16 places. e.g pin 0 is now 16, pin 1 is 17 and so on

}




//**********************************************************
// 					INTERRUPT FUNCTION



/**
 * @brief Allows a pin to be configured as an interrupt.
 * @param *port : Port of GPIO pin you want to set as an interrupt
 * @param pinNumber : The number of the pin you want to set as an interrupt
 * @param edge : Configure the interrupt to be triggered as either
 * 				 RISING_EDGE, FALLING_EDGE or RISING_FALLING_EDGE
 * @example : gpio_interrupt_configure(PORTC,13,FALLING_EDGE);
 * 			 This will configure PC13, which is also a push button B2.
 * @note : If for example, PC13 is connected to high, and when pressed B2
 * 		   connects the pin to ground, select FALLING_EDGE. (STM32F411RE)
 */
void gpio_interrupt_configure(GPIO_TypeDef *port, uint32_t pinNumber, edge_select edge)
{

	//Defined in stm32f411xe.h   Can write 1<<14 instead
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN; // Enabling the SYSCFGEN clock. Need this to use interrupts.


	if (port == PORTA)
	{
		switch(pinNumber)
		{
		//SYSCFGEN Register 1
		case 0:
			SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI0_PA;
		break;


		case 1:
			SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI1_PA;
		break;


		case 2:
			SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI2_PA;
		break;


		case 3:
			SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI3_PA;
		break;

		//SYSCFGEN Register 2
		case 4:
			SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI4_PA;
		break;


		case 5:
			SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI5_PA;
		break;


		case 6:
			SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI6_PA;
		break;

		case 7:
			SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI7_PA;
		break;

		//SYSCFGEN Register 3
		case 8:
			SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI8_PA;
		break;


		case 9:
			SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI9_PA;
		break;


		case 10:
			SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI10_PA;
		break;


		case 11:
			SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI11_PA;
		break;

		//SYSCFGEN Register 4
		case 12:
			SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI12_PA;
		break;


		case 13:
			SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI13_PA;
		break;


		case 14:
			SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI14_PA;
		break;


		case 15:
			SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI15_PA;
		break;
		} //End PORTA switch
	}	//end if for PORTA


	if (port == PORTB)
		{
			switch(pinNumber)
			{
			//SYSCFGEN Register 1
			case 0:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI0_PB;
			break;


			case 1:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI1_PB;
			break;


			case 2:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI2_PB;
			break;


			case 3:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI3_PB;
			break;

			//SYSCFGEN Register 2
			case 4:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI4_PB;
			break;


			case 5:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI5_PB;
			break;


			case 6:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI6_PB;
			break;

			case 7:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI7_PB;
			break;

			//SYSCFGEN Register 3
			case 8:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI8_PB;
			break;


			case 9:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI9_PB;
			break;


			case 10:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI10_PB;
			break;


			case 11:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI11_PB;
			break;

			//SYSCFGEN Register 4
			case 12:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI12_PB;
			break;


			case 13:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI13_PB;
			break;


			case 14:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI14_PB;
			break;


			case 15:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI15_PB;
			break;
			} //End PORTB switch
		}	//end if for PORTB


	if (port == PORTC)
		{
			switch(pinNumber)
			{
			//SYSCFGEN Register 1
			case 0:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI0_PC;
			break;


			case 1:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI1_PC;
			break;


			case 2:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI2_PC;
			break;


			case 3:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI3_PC;
			break;

			//SYSCFGEN Register 2
			case 4:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI4_PC;
			break;


			case 5:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI5_PC;
			break;


			case 6:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI6_PC;
			break;

			case 7:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI7_PC;
			break;

			//SYSCFGEN Register 3
			case 8:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI8_PC;
			break;


			case 9:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI9_PC;
			break;


			case 10:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI10_PC;
			break;


			case 11:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI11_PC;
			break;

			//SYSCFGEN Register 4
			case 12:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI12_PC;
			break;


			case 13:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI13_PC;
			break;


			case 14:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI14_PC;
			break;


			case 15:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI15_PC;
			break;
			} //End PORTC switch
		}	//end if for PORTC


	if (port == PORTD)
		{
			switch(pinNumber)
			{
			//SYSCFGEN Register 1
			case 0:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI0_PD;
			break;


			case 1:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI1_PD;
			break;


			case 2:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI2_PD;
			break;


			case 3:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI3_PD;
			break;

			//SYSCFGEN Register 2
			case 4:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI4_PD;
			break;


			case 5:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI5_PD;
			break;


			case 6:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI6_PD;
			break;

			case 7:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI7_PD;
			break;

			//SYSCFGEN Register 3
			case 8:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI8_PD;
			break;


			case 9:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI9_PD;
			break;


			case 10:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI10_PD;
			break;


			case 11:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI11_PD;
			break;

			//SYSCFGEN Register 4
			case 12:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI12_PD;
			break;


			case 13:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI13_PD;
			break;


			case 14:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI14_PD;
			break;


			case 15:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI15_PD;
			break;
			} //End PORTD switch
		}	//end if for PORTD



	if(edge == RISING_EDGE)
	{
		EXTI->RTSR |= 1<<pinNumber;
	}

	if (edge == FALLING_EDGE)
	{
		EXTI->FTSR |= 1<<pinNumber;
	}

	if (edge == RISING_FALLING_EDGE)
	{
		EXTI->FTSR |= 1<<pinNumber;
		EXTI->RTSR |= 1<<pinNumber;
	}

} //END Configure gpio interrupt void

/**
 * @brief Enable the interrupt on the EXTI register and NVIC
 * @param pinNumber : The number of the pin you set as an interrupt
 * @param irqNumber : The IRQ number of the EXTI line
 * @example : gpio_interrupt_enable(13,EXTI15_10_IRQn);
 * @note : The IRQ number for an EXTI line is found in stm32f411xe.h as well as the datasheet.
 * @note : The IRQ number for EXTI9 to EXTI5 is shared. This is also true for EXTI10 to EXTI15.
 * @note : EXTI0 is for pin 0 of every port, EXTI4 is for pin 4 of every port and so on.
 */
void gpio_interrupt_enable(uint32_t pinNumber, IRQn_Type irqNumber)
{
	//enable interrupt in EXTI
	EXTI->IMR |= 1<<pinNumber;
	//enable interrupt in NVIC
	NVIC_EnableIRQ(irqNumber);
}

/**
 * @brief Clears the interrupt in the pending register
 * @param pinNumber : The pin number of the interrupt
 * @note : After an interrupt is triggered, it needs to be cleared
 * 		   otherwise an infinite interrupt loop will occur.
 * @example : void EXTI15_10_IRQHandler(){
 * 				gpio_interrupt_clear(13);
 * 			 }
 */
void gpio_interrupt_clear(uint32_t pinNumber)
{
	EXTI->PR |= 1<<pinNumber;
}





















/*void gpio_configure_interrupt(uint16_t pinNumber, int_edge_sel_t edge_sel)
{
	if (edge_sel == INT_RISING_EDGE)
	{
		EXTI->RTSR |= (1<<pinNumber); //If you want pin 0 of ports, then you put pinNumber 1
	}
	else if (edge_sel == INT_FALLING_EDGE)
	{
		EXTI->FTSR |= (1<<pinNumber);
	}
	else if (edge_sel == INT_RISING_FALLING_EDGE)
	{
		EXTI->RTSR |= (1<<pinNumber);
		EXTI->FTSR |= (1<<pinNumber);
	}
	else
	{
		;//TODO
	}
}


void gpio_enable_interrupt(uint16_t pinNumber, IRQn_Type irq_no)
{
	EXTI->IMR |= (1<<pinNumber);
	NVIC_EnableIRQ(irq_no); // CMSIS-core
}

void gpio_clear_interrupt(uint16_t pin)
{
	if (EXTI->PR & (1<<pin)) //check whether the interrupt is really pended or not
	{
		EXTI->PR |=1>>pin;   //if it is write 1 to clear the interrupt.
	}
}




*/



//Write how to use each function. eg. gpio_write(PORTC,5,1). or gpio_write(PORTC,5,HIGH) etc


