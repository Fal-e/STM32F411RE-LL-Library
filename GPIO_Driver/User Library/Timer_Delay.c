/*
 * Timer_Delay.c
 *
 *  Created on: 22Dec.,2018
 *      Author: Falcon
 */
 // This library configures the clock frequency to 50MHz,
 // and enables the use of a delay_mS function
 // HOW TO USE: Must call config_clock_50MHz(); in the main before you start using the delay_mS.




#include <stdint.h>
#include <Timer_Delay.h>


int Ticks=0;

void config_clock_50MHz(void)
{
	/* Enable HSI */
	RCC->CR |= ((uint32_t)RCC_CR_HSION);

	/* Wait for HSI to be ready */
	while ((RCC->CR & RCC_CR_HSIRDY) == 0){
	  // Nop
	}

	/* Set HSI as the System Clock */
	RCC->CFGR = RCC_CFGR_SW_HSI;

	/* Wait for HSI to be used for the system clock */
	while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI){
	 // Nop
	}

	// some shit here //
	FLASH->ACR |= FLASH_ACR_PRFTEN;                          // Enable Prefetch Buffer
	FLASH->ACR |= FLASH_ACR_LATENCY;                         // Flash 1 wait state
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;                       // Enable the PWR APB1 Clock
	PWR->CR = PWR_CR_VOS_0;                                  // Select the Voltage Range 1 (1.8V)
	while((PWR->CSR & PWR_CSR_VOSRDY ) != 0);

	/* PLLCLK = (HSI * 4)/2 = 32 MHz */ //NAH
	RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLSRC| RCC_PLLCFGR_PLLM |  RCC_PLLCFGR_PLLN);
	RCC->PLLCFGR |= (RCC_PLLCFGR_PLLSRC_HSI|RCC_PLLCFGR_PLLM_4 | (200<<6));

	/* Peripheral Clock divisors */
	RCC->CFGR &= ~(0xF<<4); // Cleared 4 bits. HPRE[3:0] which are bits 4,5,6,7. This means  that the system clock is not divided
	RCC->CFGR |= (0b1000<<4); // AHB system clock now divided by 2.

	// HCLK is now 50 MHz



	// HCLK = SYSCLK
	RCC->CFGR &= ~(0x7<<10); // cleared 3 bits. PPRE1[2:0] which are bits 10,11,12
	//RCC->CFGR |= (0b100<<10); // Set as 101, which means the AHB clock is divided by 2. APB1. 50mhz


	RCC->CFGR &= ~(0x7<<13); // Cleared 3 bits. PPRE2[2:0] which are bits 13,14,15
	//RCC->CFGR |= (0b100<<13); // Set as 100, which means the AHB clock is divided by 2. APB2 therefore 100 mhz


	// the commented out apb1 apb2 means not divided.

	/* Enable PLL */
	 RCC->CR &= ~RCC_CR_PLLON;       /* Disable PLL */
	 RCC->CR |= RCC_CR_PLLON;        /* Enable PLL     */

	   /* Wait until the PLL is ready */
	 while((RCC->CR & RCC_CR_PLLRDY) == 0){
	       //Nop
	   }

	   /* Select PLL as system Clock */
	 RCC->CFGR &= ~RCC_CFGR_SW;            /* Clear */
	 RCC->CFGR |=  RCC_CFGR_SW_PLL;    /* Set   */

	   /* Wait for PLL to become system core clock */
	 while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL){
	       //Nop
	   }





	//************************* configuring for milisecond delay
	 RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	 TIM4->PSC = 50;
	 TIM4->ARR = 1000;
	 TIM4->CR1 &= ~TIM_CR1_DIR; //Up counter. By default, but still good practice
	 //TIM4->CR1 |= TIM_CR1_URS; // Only up/down counter generates an update interrupt // good practice
	 TIM4->DIER = TIM_DIER_UIE; // Update interrupt enabled
	 NVIC_EnableIRQ(TIM4_IRQn);

}


void TIM4_IRQHandler()
{

	Ticks++;
	TIM4->SR &= ~TIM_SR_UIF; // cleared update interrupt

}


void delay_mS(uint32_t mS)
{
		TIM4->CR1 |= TIM_CR1_CEN;
		Ticks = 0;

		while(Ticks<mS);

		TIM4->CR1 &= ~TIM_CR1_CEN;

}





