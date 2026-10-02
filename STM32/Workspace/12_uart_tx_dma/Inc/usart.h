/*
 * usart.h
 *
 *  Created on: 20 de set. de 2026
 *      Author: Antonio Thomaz
 */

#ifndef USART_H_
#define USART_H_
#include <stdint.h>

#include "stm32l4xx.h"

void dma1_usart2_tx_init(uint32_t src, uint32_t dst, uint16_t len);
void usart2_rxtx_init();
void usart2_write(int ch);

#endif /* USART_H_ */
