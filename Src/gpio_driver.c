#include "gpio_driver.h"

#define GPIOAEN			(1U<<0)
#define GPIOCEN			(1U<<2)
#define BTN_PIN			(1U<<13)

static uint8_t previousButtonState = 0;

void GPIO_Init(void){
	//gpio clk
	RCC->AHB1ENR |= (GPIOAEN | GPIOCEN);

	//pa5 as alternate function
	GPIOA->MODER &=~(3U<<10);
	GPIOA->MODER |= (2U<<10);

	//pa5 to af1
	GPIOA->AFR[0] &= ~(0xF<<20);
	GPIOA->AFR[0] |= (0x1<<20);

	//pc13 as input
	GPIOC->MODER &=~(3U<<26);

}

uint8_t GPIO_ReadButton(void){
	return (GPIOC->IDR & BTN_PIN) ? 0 : 1;
}

uint8_t GPIO_ButtonPressed(void){
	uint8_t currentButtonState = GPIO_ReadButton();
	uint8_t event = (!previousButtonState && currentButtonState);
	previousButtonState = currentButtonState;
	return event;
}



