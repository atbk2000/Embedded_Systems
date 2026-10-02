/*
 * tim.c
 *
 *  Created on: 10 de set. de 2026
 *      Author: Antonio Thomaz
 */

#include "stm32l4xx.h"
#include "tim.h"


void tim2_1hz_interrupt_init(){

	// Enable clock access to TIM2
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;

	// Set prescaler value
	// 4 000 000 / 400 = 10 000
	TIM2->PSC = 400 - 1;

	// Set auto-reload value
	// 10 000 / 10 000 = 1s
	TIM2->ARR = 10000 - 1;

	// Clear counter
	TIM2->CNT = 0;

	// Enable timer
	TIM2->CR1 |= TIM_CR1_CEN;

	// Enable TIM interrupt
	TIM2->DIER |= TIM_DIER_UIE;

	// Enable TIM interrupt in NVIC
	NVIC_EnableIRQ(TIM2_IRQn);
}


void tim2_pb3_output_compare(){

	// Enable clock access to GPIOB
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

	// Set PB3 mode to alternate function
	GPIOB->MODER &= ~GPIO_MODER_MODE3;
	GPIOB->MODER |= (2u << GPIO_MODER_MODE3_Pos);

	// Set PB3 alternate function type to TIM2_CH2 (AF01)
	GPIOB->AFR[0] &= ~(0xFU << GPIO_AFRL_AFSEL3_Pos);
	GPIOB->AFR[0] |= (1u << GPIO_AFRL_AFSEL3_Pos);

	// Enable clock access to TIM2
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;

	// Set prescaler value
	// 4 000 000 / 4000 = 1000
	TIM2->PSC = 4000 - 1;

	// Set auto-reload value
	// 1000 / 1000 = 1s
	TIM2->ARR = 1000 - 1;

	// Set output compare toggle mode
	TIM2->CCMR1 &= ~TIM_CCMR1_OC2M;
	TIM2->CCMR1 |= (3U << TIM_CCMR1_OC2M_Pos);

	// Enable TIM2 ch2 in compare mode
	TIM2->CCER |= TIM_CCER_CC2E;

	// Clear counter
	TIM2->CNT = 0;

	// Enable timer
	TIM2->CR1 |= TIM_CR1_CEN;
}


void tim1_pa9_input_capture(){

	// Enable clock access to GPIOA
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

	// Set PA0 mode to alternate function
	GPIOA->MODER &= ~GPIO_MODER_MODE9;
	GPIOA->MODER |= (2u << GPIO_MODER_MODE9_Pos);

	// Set PA9 alternate function type to TIM1_CH2 (AF01)
	GPIOA->AFR[1] &= ~(0xFU << GPIO_AFRH_AFSEL9_Pos);
	GPIOA->AFR[1] |= (1u << GPIO_AFRH_AFSEL9_Pos);

	// Enable clock access to TIM1
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

	// Set Prescaler
	// 4 000 000 / 4000 = 1000
	TIM1->PSC = 4000 - 1;

	// Set ch2 to input capture
	TIM1->CCMR1 &= ~TIM_CCMR1_CC2S;
	TIM1->CCMR1 |= (1u << TIM_CCMR1_CC2S_Pos);

	// Enable Channel 2 Capture
	TIM1->CCER |= TIM_CCER_CC2E;

	// Enable TIM1
	TIM1->CR1 |= TIM_CR1_CEN;
}
