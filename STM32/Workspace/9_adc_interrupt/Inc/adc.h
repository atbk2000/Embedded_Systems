/*
 * adc.h
 *
 *  Created on: 8 de set. de 2026
 *      Author: Antonio Thomaz
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

void pa1_adc_interrupt_init();
void start_conversion();
uint32_t adc_read();

#endif /* ADC_H_ */
