#include <stdio.h>
#include "stm32l4xx.h"
#include "tim.h"

int timestamp = 0;

// Set up: connect a jumper wire from PB3 to PA0
// PA9: D1 (Arduino), PB3: D13 (Arduino)
int main(){


  	tim2_pb3_output_compare();
	tim1_pa9_input_capture();

	while(1){

		// wait until edge is captured
		while(!(TIM1->SR & TIM_SR_CC2IF)){}

		// read captured value
		timestamp = TIM1->CCR2;

	}

}
