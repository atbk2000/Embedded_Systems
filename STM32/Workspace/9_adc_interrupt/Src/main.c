#include <stdint.h>
#include <stdio.h>
#include "stm32l4xx.h"
#include "adc.h"
#include "uart.h"

uint32_t sensor_value = 0;

static void adc_callback();

// PA1: A1 (Arduino)

int main(){

	usart2_rxtx_init();
	pa1_adc_interrupt_init();
	start_conversion();

	while(1){

	}

}

static void adc_callback(){

	sensor_value = ADC1->DR;

	printf("Sensor value: %d \n\r", (int)sensor_value);
}

void ADC1_IRQHandler(){

	// Check for EOC in SR
	if((ADC1->ISR & ADC_ISR_EOC) != 0){

		// Clear EOC
		ADC1->ISR &= ~ADC_ISR_EOC;

		adc_callback();
	}
}
