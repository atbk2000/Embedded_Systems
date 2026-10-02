/*
 * uart.c
 *
 *  Created on: 4 de set. de 2026
 *      Author: Antonio Thomaz
 */

#include "uart.h"

// USART2_TX connected in PA2 with alternate function mapping AF7
// USART2_RX connected in PA15 with alternate function mapping AF3

#define SYS_FREQ					4000000U
#define APB1_CLK					SYS_FREQ

#define USART_BAUDRATE				115200

static void uart2_set_baudrate(USART_TypeDef* USARTx, uint32_t PeriphClk, uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);

int __io_putchar(int ch){

	for(int i = 0; i < 20000; i++){}

	usart2_write(ch);

	return ch;
}

void uart2_rxtx_interrupt_rx_init(){

	/*************** Configure uart gpio pin **************/

	// Enable clock access to gpioa
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

	// Set PA2 mode to alternate function mode
	GPIOA->MODER &= ~(1U << 4);
	GPIOA->MODER |= (1U << 5);

	// Set PA2 alternate function type to UART_TX
	GPIOA->AFR[0] |= (7U << 8);
	GPIOA->AFR[0] &= ~(1U << 11);

	// Set PA15 mode to alternate function mode
	GPIOA->MODER &= ~(3U << 30);
	GPIOA->MODER |=  (2U << 30);

	// Set PA15 alternate function type to UART_RX
	GPIOA->AFR[1] &= ~(0xFU << 28);
	GPIOA->AFR[1] |=  (3U << 28);

	/*************** Configure uart module *****************/

	// Enable clock access to uart2
	RCC->APB1ENR1 |= RCC_APB1ENR1_USART2EN;

	// Configure baudrate
	uart2_set_baudrate(USART2, APB1_CLK, USART_BAUDRATE);

	// Configure the transfer direction
	USART2->CR1 = (USART_CR1_TE | USART_CR1_RE);

	// RXNE interrupt enable
	USART2->CR1 |= USART_CR1_RXNEIE;

	// Enable UART2 interrupt in NVIC
	NVIC_EnableIRQ(USART2_IRQn);

	// Enable uart module
	USART2->CR1 |= USART_CR1_UE;
}

char uart2_read(){

	// Make sure the receive data register is not empty
	while(!(USART2->ISR & USART_ISR_RXNE)){}

	// Read data
	return USART2->RDR;
}

void usart2_write(int ch){

	// Make sure the transmit data register is empty
	while(!(USART2->ISR & USART_ISR_TXE)){}

	USART2->TDR = (ch & 0xFF);
}

static void uart2_set_baudrate(USART_TypeDef* USARTx, uint32_t PeriphClk, uint32_t BaudRate){
	USARTx->BRR = compute_uart_bd(PeriphClk, BaudRate);
}

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate){
	return ((PeriphClk + (BaudRate/2U)) / BaudRate);
}
