#include <stdio.h>
#include "stm32l4xx.h"
#include "uart.h"
#include "systick.h"

#define GPIOBEN					(1U << 1)
#define PIN3					(1U << 3)
#define LED						PIN3


int main(){

	RCC->AHB2ENR |= GPIOBEN;

	GPIOB->MODER &= ~(1U << 7);
	GPIOB->MODER |= (1U << 6);

	usart2_rxtx_init();

	while(1){

		// Toogle LED for specific time
		GPIOB->ODR ^= LED;
		systickDelayMs(1000);
	}

}
