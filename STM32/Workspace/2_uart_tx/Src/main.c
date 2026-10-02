#include <stdint.h>
#include <stdio.h>
#include "stm32l4xx.h"
#include "uart.h"


int main(){

	usart2_rxtx_init();

	while(1){
		printf("Hello from STM32L4\n\r");
	}

}

