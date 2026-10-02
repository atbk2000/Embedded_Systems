#include <stdint.h>
#include <stdio.h>
#include "usart.h"
#include "stm32l4xx.h"

#define PIN3					(1U << 3)
#define LED_PIN					PIN3

static void dma_callback(void);

int main(void){

	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

	GPIOB->MODER &= ~(1U << 7);
	GPIOB->MODER |= (1U << 6);

	char message[16] = "USART2_TX DMA!\n\r";

	usart2_rxtx_init();

	dma1_usart2_tx_init((uint32_t) message, (uint32_t) &USART2->TDR, 16);

	while(1){

	}

}

static void dma_callback(void){
	GPIOB->ODR |= LED_PIN;
}

void DMA1_CH7_IRQHandler(void){

	// Check for transfer complete interrupt
	if(DMA1->ISR & DMA_ISR_TCIF7){

		// Clear flag
		DMA1->IFCR |= DMA_IFCR_CTCIF7;

		dma_callback();
	}
}

