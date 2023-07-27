/*
 * timer_lib.c
 *
 *  Created on: Jul 25, 2023
 *      Author: maciej
 */

#include <stdint.h>
#include <TIMER_lib.h>

void Timer_Clock_update(Timer_RegDef* timer){
	//Turn on TIM clock
	if(timer == TIMER2){
		RCC->APB1ENR |= (1<<0);
	}else if(timer == TIMER3){
		RCC->APB1ENR |= (1<<1);
	}else if(timer == TIMER4){
		RCC->APB1ENR |= (1<<2);
	}
}


void Timer_Init(Timer_Handle_t* TIMER_handler){

	Timer_Clock_update(TIMER_handler->TIMER);

	//set ARR and PRESCALER
	TIMER_handler->TIMER->TIMx_ARR = TIMER_handler->TIM_ARR;
	TIMER_handler->TIMER->TIMx_PSC |= TIMER_handler->TIM_prescaler;

	//allow to generate update
	TIMER_handler->TIMER->TIMx_DIER |= (1<<0);

	//turn on TIMER
	TIMER_handler->TIMER->TIMx_CR1 |= (1<<0);

	//update shadow values
	TIMER_handler->TIMER->TIMx_EGR |= (1<<0);
}

void Timer2_Init(Timer_Handle_t* TIMER_handler){

	//Turn on TIM2 clock
	Timer_Clock_update(TIMER_handler->TIMER);

	//counter mode up == DEFAULT

	//no prescaler == DEFAULT

	//RISING EDGE == DEFAULT

	//no filter == DEFAULT

	//TI1 input
	TIMER_handler->TIMER->TIMx_CCMR1 |= (1<<0);

	//set prescaler to 1 ms precision
	TIMER_handler->TIMER->TIMx_PSC = (64000);

	//ARR max value
	TIMER_handler->TIMER->TIMx_ARR = 0xFFFFFFFFUL;

	//allow to generate update
	TIMER_handler->TIMER->TIMx_DIER |= (1<<0);

	//enable CCR1 interupt
	TIMER_handler->TIMER->TIMx_DIER |= (1<<1);

	//turn on TIM2
	TIMER_handler->TIMER->TIMx_CR1 |= (1<<0);

	//update shadow values
	TIMER_handler->TIMER->TIMx_EGR |= (1<<0);

	// enable C/C interrupt
	TIMER_handler->TIMER->TIMx_CCER |= (1<<0);


}
