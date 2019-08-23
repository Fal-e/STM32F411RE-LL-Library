/*
 * ss_gpio.c
 *
 *  Created on: 3May,2019
 *      Author: Falcon
 */
#include "ss_gpio.h"
#include <stdint.h>

// Pin positions in the CRL/CRH register
uint32_t PINPOS[16]={
		(0), // Pin 0
		(4), // Pin 1
		(8),
		(12),
		(16),
		(20),
		(24),
		(28),
		(0),
		(4),
		(8),
		(12),
		(16),
		(20), // Pin 13
		(24),
		(28),
};

void config_pin(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t mode, uint32_t type)
{

	/* Lower pins are configured in CRL register */
	if (pinNumber < 8)
	{
		/* INPUT MODE */
		if (mode == INPUT)
		{
			/* For INPUT mode, MODE[1:0] of that pin must be cleared  */
			port->CRL &= ~(1<<PINPOS[pinNumber]);
			port->CRL &= ~(1<<(PINPOS[pinNumber]+1));

			if (type == ANALOG)
			{
				/* Analog Mode requires CNF[1:0] to be cleared */
				port->CRL &= ~(1<<(PINPOS[pinNumber]+2));
				port->CRL &= ~(1<<(PINPOS[pinNumber]+3));
			}

			else if (type == FLOATING)
			{
				/* Floating Mode requires CNF[1:0] to be 01 */
				port->CRL |= (1<<(PINPOS[pinNumber]+2));
				port->CRL &= ~(1<<(PINPOS[pinNumber]+3));
			}

			else if (type == PULL_DOWN)
			{
				/*Set as pull-up/pull down*/
				port->CRL &= ~(1<<(PINPOS[pinNumber]+2));
				port->CRL |= (1<<(PINPOS[pinNumber]+3));

				/* Clear pins corresponding ODR bit for pull-down */
				port->ODR &= ~(1<<pinNumber);
			}

			else if (type == PULL_UP)
			{
				/*Set as pull-up/pull down*/
				port->CRL &= ~(1<<(PINPOS[pinNumber]+2));
				port->CRL |= (1<<(PINPOS[pinNumber]+3));

				/* Set pins corresponding ODR bit for pull-up */
				port->ODR |= (1<<pinNumber);
			}

		}

		/* OUTPUT MODE */
		if (mode == OUTPUT_10MHz | OUTPUT_2MHz | OUTPUT_50MHz)
		{
			if (mode == OUTPUT_10MHz)
			{
				/* For OUTPUT 10MHz mode, MODE[1:0]=01  */
				port->CRL |= (1<<PINPOS[pinNumber]);
				port->CRL &= ~(1<<(PINPOS[pinNumber]+1));
			}

			else if (mode == OUTPUT_2MHz)
			{
				/* For OUTPUT 2MHz mode, MODE[1:0]=10  */
				port->CRL &= ~(1<<PINPOS[pinNumber]);
				port->CRL |= (1<<(PINPOS[pinNumber]+1));
			}

			else if (mode == OUTPUT_50MHz)
			{
				/* For OUTPUT 10MHz mode, MODE[1:0]=11  */
				port->CRL |= (1<<PINPOS[pinNumber]);
				port->CRL |= (1<<(PINPOS[pinNumber]+1));
			}


			if (type == PUSH_PULL)
			{
				/* General purpose Push-pull Mode requires CNF[1:0] to be 00 */
				port->CRL &= ~(1<<(PINPOS[pinNumber]+2));
				port->CRL &= ~(1<<(PINPOS[pinNumber]+3));
			}

			else if (type == OPEN_DRAIN)
			{
				/* Open-drain requires CNF[1:0] to be 01 */
				port->CRL |= (1<<(PINPOS[pinNumber]+2));
				port->CRL &= ~(1<<(PINPOS[pinNumber]+3));
			}

			else if (type == ALTERNATE_PUSH_PULL)
			{
				/* Alternate push-pull requires CNF[1:0] to be 10 */
				port->CRL &= ~(1<<(PINPOS[pinNumber]+2));
				port->CRL |= (1<<(PINPOS[pinNumber]+3));
			}

			else if (type == ALTERNATE_OPEN_DRAIN)
			{
				/* Alternate push-pull requires CNF[1:0] to be 11 */
				port->CRL |= (1<<(PINPOS[pinNumber]+2));
				port->CRL |= (1<<(PINPOS[pinNumber]+3));
			}

		}
	}
	/*Higher pins are configured in CRH register */
	if (pinNumber > 7)
		{
			/* INPUT MODE */
			if (mode == INPUT)
			{
				/* For INPUT mode, MODE[1:0] of that pin must be cleared  */
				port->CRH &= ~(1<<PINPOS[pinNumber]);
				port->CRH &= ~(1<<(PINPOS[pinNumber]+1));

				if (type == ANALOG)
				{
					/* Analog Mode requires CNF[1:0] to be cleared */
					port->CRH &= ~(1<<(PINPOS[pinNumber]+2));
					port->CRH &= ~(1<<(PINPOS[pinNumber]+3));
				}

				else if (type == FLOATING)
				{
					/* Floating Mode requires CNF[1:0] to be 01 */
					port->CRH |= (1<<(PINPOS[pinNumber]+2));
					port->CRH &= ~(1<<(PINPOS[pinNumber]+3));
				}

				else if (type == PULL_DOWN)
				{
					/*Set as pull-up/pull down*/
					port->CRH &= ~(1<<(PINPOS[pinNumber]+2));
					port->CRH |= (1<<(PINPOS[pinNumber]+3));

					/* Clear pins corresponding ODR bit for pull-down */
					port->ODR &= ~(1<<pinNumber);
				}

				else if (type == PULL_UP)
				{
					/*Set as pull-up/pull down*/
					port->CRH &= ~(1<<(PINPOS[pinNumber]+2));
					port->CRH |= (1<<(PINPOS[pinNumber]+3));

					/* Set pins corresponding ODR bit for pull-up */
					port->ODR |= (1<<pinNumber);
				}

			}

			/* OUTPUT MODE */
			if (mode == OUTPUT_10MHz | OUTPUT_2MHz | OUTPUT_50MHz)
			{
				if (mode == OUTPUT_10MHz)
				{
					/* For OUTPUT 10MHz mode, MODE[1:0]=01  */
					port->CRH |= (1<<PINPOS[pinNumber]);
					port->CRH &= ~(1<<(PINPOS[pinNumber]+1));
				}

				else if (mode == OUTPUT_2MHz)
				{
					/* For OUTPUT 2MHz mode, MODE[1:0]=10  */
					port->CRH &= ~((1<<PINPOS[pinNumber]));
					port->CRH |= (1<<(PINPOS[pinNumber]+1));
				}

				else if (mode == OUTPUT_50MHz)
				{
					/* For OUTPUT 50MHz mode, MODE[1:0]=11  */
					port->CRH |= (1<<PINPOS[pinNumber]);
					port->CRH |= (1<<(PINPOS[pinNumber]+1));
				}


				if (type == PUSH_PULL)
				{
					/* General purpose Push-pull Mode requires CNF[1:0] to be 00 */
					port->CRH &= ~(1<<(PINPOS[pinNumber]+2));
					port->CRH &= ~(1<<(PINPOS[pinNumber]+3));
				}

				else if (type == OPEN_DRAIN)
				{
					/* Open-drain requires CNF[1:0] to be 01 */
					port->CRH |= (1<<(PINPOS[pinNumber]+2));
					port->CRH &= ~(1<<(PINPOS[pinNumber]+3));
				}

				else if (type == ALTERNATE_PUSH_PULL)
				{
					/* Alternate push-pull requires CNF[1:0] to be 10 */
					port->CRH &= ~(1<<(PINPOS[pinNumber]+2));
					port->CRH |= (1<<(PINPOS[pinNumber]+3));
				}

				else if (type == ALTERNATE_OPEN_DRAIN)
				{
					/* Alternate push-pull requires CNF[1:0] to be 11 */
					port->CRH |= (1<<(PINPOS[pinNumber]+2));
					port->CRH |= (1<<(PINPOS[pinNumber]+3));
				}

			}
		}
}



void gpio_init(GPIO_TypeDef *port)
{
	if (port == PORTA)
		GPIO_CLOCK_ENABLE_PORTA;

	if (port == PORTB)
			GPIO_CLOCK_ENABLE_PORTB;

	if (port == PORTC)
			GPIO_CLOCK_ENABLE_PORTC;

}
