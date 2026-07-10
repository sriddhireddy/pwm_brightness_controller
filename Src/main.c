#include "gpio_driver.h"
#include "uart_driver.h"
#include "timer_driver.h"

int main(void){

	GPIO_Init();
	UART_Init();
	Timer_Init();
	Timer_PWM_Init();
	Timer_Start();

	Timer_SetDutyCycle(10);

	while(1){}
}
