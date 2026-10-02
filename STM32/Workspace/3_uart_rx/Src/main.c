#include <stdint.h>
#include <stdio.h>
#include "stm32l4xx.h"
#include "uart.h"

#define PIN3					(1U << 3)
#define LED_PIN					PIN3

int main(void){

	// Enable clock access to GPIOB
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

	// Set PB3 as output pin
	GPIOB->MODER &= ~(1U << 7);
	GPIOB->MODER |= (1U << 6);

	usart2_rxtx_init();

	while(1){

		if(uart2_read() == '1'){
			GPIOB->ODR |= LED_PIN;
		}
		else{
			GPIOB->ODR &= ~LED_PIN;
		}
	}

}
