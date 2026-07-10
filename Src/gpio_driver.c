#include "gpio_driver.h"

#define GPIOAEN			(1U<<0)

void GPIO_Init(void){
	//gpio clk
	RCC->AHB1ENR |= GPIOAEN;

	//pa5 as alternate function
	GPIOA->MODER &=~(3U<<10);
	GPIOA->MODER |= (2U<<10);

	//pa5 to af1
	GPIOA->AFR[0] &= ~(0xF<<20);
	GPIOA->AFR[0] |= (0x1<<20);
}




