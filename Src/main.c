#include "gpio_driver.h"
#include "uart_driver.h"
#include "timer_driver.h"

#define DUTY_STEP    25U

int main(void){

	uint8_t duty=0;

	GPIO_Init();
	UART_Init();
	Timer_Init();
	Timer_PWM_Init();
	Timer_SetDutyCycle(duty);
	Timer_Start();

	while(1){
		if(GPIO_ButtonPressed()){
			duty += DUTY_STEP;
			if(duty>100){
				duty=0;
			}
			Timer_SetDutyCycle(duty);
			UART_WriteString("duty cycle: ");
			UART_WriteInt(duty);
			UART_WriteString("%\r\n");
		}

	}

}
