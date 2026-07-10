#ifndef TIMER_DRIVER_H_
#define TIMER_DRIVER_H_

#include "stm32f4xx.h"

void Timer_Init(void);
void Timer_Start(void);
void Timer_Stop(void);
void Timer_PWM_Init(void);
void Timer_SetDutyCycle(uint8_t duty);

#endif /* TIMER_DRIVER_H_ */
