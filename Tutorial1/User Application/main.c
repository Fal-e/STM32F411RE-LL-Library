
/* Includes */
#include "stm32f4xx.h"

/**
**===========================================================================
**
**  		Tutorial 1: Learning about GPIO
**
**===========================================================================
*/
//STM32F4 Reference Manual is needed and STM32F4 Schematic

int main(void)
{
 // initialize the clock for GPIO A
	RCC->AHB1ENR |= (1<<0); //Shifted a 1 into bit 0 of this register to enable GPIOA

// Configuring Pin5 as general purpose output mode
	GPIOA->MODER |= (1<<10); //Port Mode Register. Shifted a 1 into bit 10 of MODER
	GPIOA->MODER &= ~(1<<11); // Shifted a 0 into bit 11 of MODER

//Configuring  Pin 5. Using the below, we configured the I/O (OUTPUT in this case) as pull-up.
	GPIOA->PUPDR |= (1<<10); //Shifted a 1 into bit 10
	GPIOA->PUPDR &= ~(1<11); //Shifted a 0 into bit 11
//actually don't need the above, as it as it is by default push-pull
	while (1)
	{
		GPIOA->BSRR = 1<<5; // Bit Set/Reset Register. Shifted a 1 into bit 5 of BSRR to set Pin 5 of GPIOA
		//GPIOA->BSRR = 0b100000;   can also use this.

		for(int i=0; i<500000; i++); // wait some time. Basically a delay
		GPIOA->BSRR = 1<<21; //Shifted a 1 into bit 21 of BSRR to reset (clear) pin 5 of GPIOA
		for(int i=0; i<500000; i++); //

	}
//To summarize: We initialized the clock for GPIOA, set pin 5 of GPIOA as general purpose output mode, made output pull-up
//Then we toggled the switch on and off using Bit Set/Reset Register.




}
