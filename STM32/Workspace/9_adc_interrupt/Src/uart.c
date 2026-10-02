/*
 * uart.c
 *
 *  Created on: 4 de set. de 2026
 *      Author: Antonio Thomaz
 */

#include "uart.h"

// USART2_TX connected in PA2 with alternate function mapping AF7

#define GPIOA_EN					(1U << 0)
#define USART2_EN					(1U << 17)

#define SYS_FREQ					4000000U
#define APB1_CLK					SYS_FREQ

#define USART_BAUDRATE				115200

#define CR1_UE						(1U << 0)
#define CR1_TE						(1U << 3)
#define CR1_RE						(1U << 2)

#define SR_TXE						(1U << 7)
#define SR_RXNE						(1U << 5)

static void uart2_set_baudrate(USART_TypeDef* USARTx, uint32_t PeriphClk, uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);

int __io_putchar(int ch){

	for(int i = 0; i < 20000; i++){}

	usart2_write(ch);

	return ch;
}

void usart2_rxtx_init(){

	/*************** Configure uart gpio pin **************/

	// Enable clock access to gpioa
	RCC->AHB2ENR |= GPIOA_EN;

	// Set PA2 mode to alternate function mode
	GPIOA->MODER &= ~(1U << 4);
	GPIOA->MODER |= (1U << 5);

	// Set PA2 alternate function type to UART_TX
	GPIOA->AFR[0] |= (7U << 8);
	GPIOA->AFR[0] &= ~(1U << 11);

	GPIOA->MODER &= ~(3U << 6);  // clear PA3 mode
	GPIOA->MODER |=  (2U << 6);  // alternate-function mode

	GPIOA->AFR[0] &= ~(0xFU << 12);
	GPIOA->AFR[0] |=  (7U << 12); // AF7 = USART2 on PA3

	/*************** Configure uart module *****************/

	// Enable clock access to uart2
	RCC->APB1ENR1 |= USART2_EN;

	// Configure baudrate
	uart2_set_baudrate(USART2, APB1_CLK, USART_BAUDRATE);

	// Configure the transfer direction
	USART2->CR1 = (CR1_TE | CR1_RE);

	// Enable uart module
	USART2->CR1 |= CR1_UE;
}

char uart2_read(){

	// Make sure the receive data register is not empty
	while(!(USART2->ISR & SR_RXNE)){}

	// Read data
	return USART2->RDR;
}

void usart2_write(int ch){

	// Make sure the transmit data register is empty
	while(!(USART2->ISR & SR_TXE)){}

	USART2->TDR = (ch & 0xFF);
}

static void uart2_set_baudrate(USART_TypeDef* USARTx, uint32_t PeriphClk, uint32_t BaudRate){
	USARTx->BRR = compute_uart_bd(PeriphClk, BaudRate);
}

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate){
	return ((PeriphClk + (BaudRate/2U)) / BaudRate);
}
