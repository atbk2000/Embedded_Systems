#include <stdio.h>
#include "stm32l4xx.h"
#include "exti.h"

#define PIN3					(1U << 3)
#define LED						PIN3

static void exti_callback();

int main(){

	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

	GPIOB->MODER &= ~(1U << 7);
	GPIOB->MODER |= (1U << 6);

	pa0_exti_init();

	while(1){


	}

}

static void exti_callback()
{
	GPIOB->ODR ^= LED;
}

void EXTI0_IRQHandler(){

	// Clear PR flag
	EXTI->PR1 |= EXTI_PR1_PIF0;

	exti_callback();

}
