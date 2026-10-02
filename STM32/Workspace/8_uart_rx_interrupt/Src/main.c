#include <stdint.h>
#include <stdio.h>
#include "stm32l4xx.h"
#include "uart.h"

#define PIN3					(1U << 3)
#define LED_PIN					PIN3

char key = '0';

static void usart_callback();

int main(void){

	// Enable clock access to GPIOB
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

	// Set PB3 as output pin
	GPIOB->MODER &= ~(1U << 7);
	GPIOB->MODER |= (1U << 6);

	uart2_rxtx_interrupt_rx_init();

	while(1){


	}

}

static void usart_callback(){

	key = uart2_read();
	if(key == '1'){
		GPIOB->ODR |= LED_PIN;
	}
	else{
		GPIOB->ODR &= ~LED_PIN;
	}
}

void USART2_IRQHandler(){

	// Check if RXNE is set
	if(USART2->ISR & USART_ISR_RXNE){
		usart_callback();
	}

}
