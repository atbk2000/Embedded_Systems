/*
 * adc.c
 *
 *  Created on: 8 de set. de 2026
 *      Author: Antonio Thomaz
 */

#include "stm32l4xx.h"
#include "adc.h"


void pa1_adc_interrupt_init(){

	// Enable GPIOA clock
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

	// Set PA1 to analog mode
	GPIOA->MODER |= (3U << 2);

	// Enable ADC clock
	RCC->AHB2ENR |= RCC_AHB2ENR_ADCEN;

	// Select ADC clock source: synchronous HCLK/1
	ADC1_COMMON->CCR |= ADC_CCR_CKMODE_0;   // 01 = HCLK/1

	// Exit ADC deep-power-down mode
	ADC1->CR &= ~ADC_CR_DEEPPWD;

	// Enable ADC voltage regulator
	ADC1->CR |= ADC_CR_ADVREGEN;

	// Small delay for regulator startup
	for(volatile int i = 0; i < 1000; i++);

	// Calibrate ADC
	ADC1->CR |= ADC_CR_ADCAL;
	while(ADC1->CR & ADC_CR_ADCAL);

	// Select ADC channel 6
	ADC1->SQR1 &= ~(0x1FU << 6);
	ADC1->SQR1 |= (6U << 6);

	// Sequence length = 1 conversion
	ADC1->SQR1 &= ~(0xFU << 0);

	// Enable ADC
	ADC1->CR |= ADC_CR_ADEN;

	// Wait until ADC is ready
	while(!(ADC1->ISR & ADC_ISR_ADRDY));
}


void start_conversion(){

	// Continuous mode
	ADC1->CFGR |= ADC_CFGR_CONT;

	// Overwrite DR with latest data even if old data wasn't read
	ADC1->CFGR |= ADC_CFGR_OVRMOD;

	// Start ADC conversion
	ADC1->CR |= ADC_CR_ADSTART;
}

uint32_t adc_read(){

	// Wait for conversion to be complete
	while(!(ADC1->ISR & ADC_ISR_EOC)){}

	// Read converted result
	return ADC1->DR;

}

