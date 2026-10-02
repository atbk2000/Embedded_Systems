/*
 * exti.c
 *
 *  Created on: 14 de set. de 2026
 *      Author: Antonio Thomaz
 */

#include "exti.h"

// External interrupt/event GPIO mapping
// PA0 -> EXTI0
// PA0: Arduino pin A0
// Configure PA0 with an internal pull-down resistor

void pa0_exti_init(){

	// Disable global interrupts
	__disable_irq();

	// Enable clock access to GPIOA
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

	// Set PA0 as input
	GPIOA->MODER &= ~(GPIO_MODER_MODE0);

	// Enable internal pull-down on PA0
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD0;
	GPIOA->PUPDR |= (2u << GPIO_PUPDR_PUPD0_Pos); // 10: Pull-down

	// Enable clock access to SYSCFG
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	// Select PORTA for EXTI0
	SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI0_Msk;

	// Unmask EXTI0
	EXTI->IMR1 |= EXTI_IMR1_IM0;

	// Select rising edge trigger on line 0
	EXTI->RTSR1 |= EXTI_RTSR1_RT0;

	// Enable EXTI0 line in NVIC
	NVIC_EnableIRQ(EXTI0_IRQn);

	// Enable global interrupts
	__enable_irq();
}
