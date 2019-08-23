/*
 * ss_delay.h
 *
 *  Created on: 4May,2019
 *      Author: Falcon
 */

#ifndef SS_DELAY_H_
#define SS_DELAY_H_


void config_clock_72MHz(void);
void TIM2_IRQHandler();
void delay_mS(uint32_t mS);

#endif /* SS_DELAY_H_ */
