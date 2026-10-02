#include <stdio.h>
#include "stm32l4xx.h"
#include "tim.h"

#define PIN3					(1U << 3)
#define LED						PIN3

static void tim2_callback();

int main(){


	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

	GPIOB->MODER &= ~(1U << 7);
	GPIOB->MODER |= (1U << 6);

	tim2_1hz_interrupt_init();

	while(1){


	}

}

static void tim2_callback(){
	GPIOB->ODR ^= LED;
}

void TIM2_IRQHandler(){

	// Clear update interrupt flag
	TIM2->SR &= ~TIM_SR_UIF;

	tim2_callback();
}
