#include "timer_driver.h"

#define TIM2EN			(1U<<1)
#define PRESCALER		(15)
#define LOAD_VAL		(999)

#define CR1_CEN			(1U<<0)

void Timer_Init(void){
	RCC->APB1ENR |= TIM2EN;

	TIM2->PSC = PRESCALER;

	TIM2->ARR = LOAD_VAL;

	TIM2->CNT = 0;
}


void Timer_Start(void){
	TIM2->CR1 |= CR1_CEN;
}

void Timer_Stop(void){
	TIM2->CR1 &= ~CR1_CEN;

}



