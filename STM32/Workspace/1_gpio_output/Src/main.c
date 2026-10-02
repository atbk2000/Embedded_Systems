#include "stm32l4xx.h"

#define PIN3					(1U << 3)
#define LED_PIN					PIN3

int main(){

	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

	GPIOB->MODER &= ~(1U << 7);
	GPIOB->MODER |= (1U << 6);

	while(1){

		GPIOB->BSRR = LED_PIN;
		for(int i = 0; i < 100000; i++){}

		GPIOB->BSRR = (1U << 19);
		for(int i = 0; i < 100000; i++){}
	}

	return 0;
}
