#include <stdint.h>
#include <stdio.h>
#include "stm32l4xx.h"
#include "adc.h"
#include "uart.h"

uint32_t sensor_value;

int main(){

	usart2_rxtx_init();
	pa1_adc_interrupt_init();
	start_conversion();

	while(1){

		sensor_value = adc_read();

		printf("Sensor value: %d \n\r", (int)sensor_value);
	}

}
