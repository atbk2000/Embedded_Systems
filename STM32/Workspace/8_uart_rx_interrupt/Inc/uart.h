/*
 * uart.h
 *
 *  Created on: 4 de set. de 2026
 *      Author: Antonio Thomaz
 */

#ifndef UART_H_
#define UART_H_
#include <stdint.h>

#include "stm32l4xx.h"

void uart2_rxtx_interrupt_rx_init();
char uart2_read();
void usart2_write(int ch);

#endif /* UART_H_ */
