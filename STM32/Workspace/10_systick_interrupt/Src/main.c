#include <stdio.h>
#include "stm32l4xx.h"
#include "systick.h"

#define PIN3					(1U << 3)
#define LED						PIN3

static void systick_callback();

int main(){

	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

	GPIOB->MODER &= ~(1U << 7);
	GPIOB->MODER |= (1U << 6);

	systick_1hz_interrupt();

	while(1){

	}

}

static void systick_callback(){
	GPIOB->ODR ^= LED;
}

void SysTick_Handler(){
	systick_callback();
}
