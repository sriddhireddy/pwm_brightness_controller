#include "timer_driver.h"

#define TIM2EN			(1U<<0)
#define PRESCALER		(15) //rm: psc: fCK_PSC / (PSC[15:0] + 1) [16 MHz / 15+1] = 1MHz
#define LOAD_VAL		(999) //1000counts, 1MHz --> 1kHz PWM

#define CR1_CEN			(1U<<0)

#define CCMR1_CC1S		(3U<<0)
#define CCMR1_OC1M		(6U<<4)
#define CCMR1_OC1PE		(1U<<3)
#define CCER_CC1E		(1U<<0)


void Timer_Init(void){
	//timer clk
	RCC->APB1ENR |= TIM2EN;

	//initialise prescaler
	TIM2->PSC = PRESCALER;

	//timer max value initialized
	TIM2->ARR = LOAD_VAL;

	//
	TIM2->CNT = 0;
}


void Timer_Start(void){
	TIM2->CR1 |= CR1_CEN;
}

void Timer_Stop(void){
	TIM2->CR1 &= ~CR1_CEN;

}

void Timer_PWM_Init(void){
	//configure ch1 as output
	TIM2->CCMR1 &= ~CCMR1_CC1S;

	//enable pwm mode1 and preload
	TIM2->CCMR1 |= (CCMR1_OC1M | CCMR1_OC1PE);

	//set initial duty cycle to 50%
//	TIM2->CCR1 = 0;

	//enable ch1 as output
	TIM2->CCER |= CCER_CC1E;

}

void Timer_SetDutyCycle(uint8_t duty){
	TIM2->CCR1 = (LOAD_VAL * duty) /100;
}






