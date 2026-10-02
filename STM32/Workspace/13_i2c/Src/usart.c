/*
 * usart.c
 *
 *  Created on: 20 de set. de 2026
 *      Author: Antonio Thomaz
 */

#include "usart.h"

// USART2_TX connected in PA2 with alternate function mapping AF7

// DMA1 channel 7 selection for USART2_TX: C7S[3:0] = 0010
#define DMA1_CSELR_C7S_USART2_TX	0x2

#define SYS_FREQ					4000000U
#define APB1_CLK					SYS_FREQ
#define USART_BAUDRATE				115200

static void usart2_set_baudrate(USART_TypeDef* USARTx, uint32_t PeriphClk, uint32_t BaudRate);
static uint16_t compute_usart_bd(uint32_t PeriphClk, uint32_t BaudRate);

int __io_putchar(int ch){

	for(int i = 0; i < 20000; i++){}

	usart2_write(ch);

	return ch;
}

void dma1_usart2_tx_init(uint32_t src, uint32_t dst, uint16_t len){

	// Enable clock access to DMA1
	RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;

	// Disable DMA1 channel 7
	DMA1_Channel7->CCR &= ~DMA_CCR_EN;

	// Wait until DMA1 channel 7 is disabled
	while(DMA1_Channel7->CCR & DMA_CCR_EN){}

	// Clear all interrupt flags of channel 7
	DMA1->IFCR |= DMA_IFCR_CGIF7;
	DMA1->IFCR |= DMA_IFCR_CTCIF7;
	DMA1->IFCR |= DMA_IFCR_CHTIF7;
	DMA1->IFCR |= DMA_IFCR_CTEIF7;

	// Set the destination buffer
	DMA1_Channel7->CPAR = dst;

	// Set the source buffer
	DMA1_Channel7->CMAR = src;

	// Set length
	DMA1_Channel7->CNDTR = len;

	// Enable memory increment
	DMA1_Channel7->CCR |= DMA_CCR_MINC;

	// Configure transfer direction
	// Direction: memory to peripheral
	DMA1_Channel7->CCR |= DMA_CCR_DIR;

	// Enable DMA transfer complete interrupt
	DMA1_Channel7->CCR |= DMA_CCR_TCIE;

	// Enable USART2_TX in channel 7
	DMA1_CSELR->CSELR &= ~DMA_CSELR_C7S_Msk;
	DMA1_CSELR->CSELR |= (DMA1_CSELR_C7S_USART2_TX << DMA_CSELR_C7S_Pos);

	// Enable USART2 transmitter DMA
	USART2->CR3 |= USART_CR3_DMAT;

	// Enable DMA1 channel 7
	DMA1_Channel7->CCR |= DMA_CCR_EN;

	// DMA Interrupt enable in NVIC
	NVIC_EnableIRQ(DMA1_Channel7_IRQn);
}

void usart2_rxtx_init(){

	/*************** Configure uart gpio pin **************/

	// Enable clock access to gpioa
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

	// Set PA2 mode to alternate function mode
	GPIOA->MODER &= ~(1U << 4);
	GPIOA->MODER |= (1U << 5);

	// Set PA2 alternate function type to UART_TX
	GPIOA->AFR[0] |= (7U << 8);
	GPIOA->AFR[0] &= ~(1U << 11);

	/*************** Configure uart module *****************/

	// Enable clock access to uart2
	RCC->APB1ENR1 |= RCC_APB1ENR1_USART2EN;

	// Configure baudrate
	usart2_set_baudrate(USART2, APB1_CLK, USART_BAUDRATE);

	// Configure the transfer direction
	USART2->CR1 = USART_CR1_TE;

	// Enable uart module
	USART2->CR1 |= USART_CR1_UE;
}

void usart2_write(int ch){

	// Make sure the transmit data register is empty
	while(!(USART2->ISR & USART_ISR_TXE)){}

	USART2->TDR = (ch & 0xFF);
}

static void usart2_set_baudrate(USART_TypeDef* USARTx, uint32_t PeriphClk, uint32_t BaudRate){
	USARTx->BRR = compute_usart_bd(PeriphClk, BaudRate);
}

static uint16_t compute_usart_bd(uint32_t PeriphClk, uint32_t BaudRate){
	return ((PeriphClk + (BaudRate/2U)) / BaudRate);
}
