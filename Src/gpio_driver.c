#include "gpio_driver.h"

#define GPIOAEN			(1U<<0)

void GPIO_Init(void){
	RCC->AHB1ENR |= GPIOAEN;

	GPIOA->MODER &=~(3U<<10);
	GPIOA->MODER |= (2U<<10);

	GPIOA->AFR[0] &= ~(0xF<<16);
	GPIOA->AFR[0] |= (0x1<<16);
}




