/*
 * ss_gpio.h
 *
 *  Created on: 3May,2019
 *      Author: Falcon
 */

#ifndef SS_GPIO_H_
#define SS_GPIO_H_

#include "stm32f10x.h"

					/* PORT NAMES */

#define PORTA 	GPIOA
#define PORTB 	GPIOB
#define PORTC 	GPIOC
#define PORTD 	GPIOD
#define PORTE 	GPIOE
#define PORTF 	GPIOF
#define PORTG 	GPIOG

					/* PIN MODES */

// Mode of pin. Either input or Output
#define INPUT				((uint32_t) 0x00)
#define OUTPUT_10MHz		((uint32_t) 0x01)
#define OUTPUT_2MHz			((uint32_t) 0x02)
#define OUTPUT_50MHz		((uint32_t) 0x03)

					/* INPUT TYPE */

// If INPUT is selected, the input types available are:
#define ANALOG		((uint32_t) 0x00)
#define FLOATING	((uint32_t) 0x01)
#define PULL_DOWN	((uint32_t) 0x02) // ODR register needs to be 0 for Pull-down. The value 0x02 is used in an if statement, not used to directly set the mode
#define PULL_UP		((uint32_t) 0x03)


					/* OUTPUT TYPE */

// if OUTPUT is selected, the output types available are:
#define PUSH_PULL	((uint32_t) 0x04)
#define OPEN_DRAIN	((uint32_t) 0x05)
// Alternate functions are also available in OUTPUT mode
#define ALTERNATE_PUSH_PULL ((uint32_t) 0x06)
#define ALTERNATE_OPEN_DRAIN ((uint32_t) 0x07)



					/* ALTERNATE FUNCTION */



/* GPIO Clock Enable Macros, Blue-pill only has 3 ports */
#define GPIO_CLOCK_ENABLE_PORTA (RCC->APB2ENR |= RCC_APB2ENR_IOPAEN)
#define GPIO_CLOCK_ENABLE_PORTB (RCC->APB2ENR |= RCC_APB2ENR_IOPBEN)
#define GPIO_CLOCK_ENABLE_PORTC (RCC->APB2ENR |= RCC_APB2ENR_IOPCEN)







				/* GPIO FUNCTIONS */

void gpio_init(GPIO_TypeDef *port);
void config_pin(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t mode, uint32_t type);


#endif /* SS_GPIO_H_ */
