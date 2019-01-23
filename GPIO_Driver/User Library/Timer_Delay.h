/*
 * Timer_Delay.h
 *
 *  Created on: 22Dec.,2018
 *      Author: Falcon
 */

#ifndef TIMER_DELAY_H_
#define TIMER_DELAY_H_
#include "stm32f4xx.h"

void config_clock_50MHz(void);
void TIM4_IRQHandler();
void delay_mS(uint32_t mS);


#endif /* TIMER_DELAY_H_ */
