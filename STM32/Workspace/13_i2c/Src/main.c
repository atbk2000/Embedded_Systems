#include <stdint.h>
#include <stdio.h>
#include "stm32l4xx.h"
#include "mpu6050.h"

/*
  	Connecting stm32l432 nucleo-32 board with MPU6050

  	MPU6050 pin		Connects to		STM32 pin		Nucleo-32 header label
	VCC				Power			3V3				—
	GND				Ground			GND				—
	SCL				Clock			PA9				D1
	SDA				Data			PA10			D0
	AD0				Address select	GND				—
	INT				(unused)		— floating		—
	XDA				(unused)		— floating		—
	XCL				(unused)		— floating		—
*/

int16_t x, y, z;
double xg, yg, zg;

extern uint8_t data_rec[6];

int main(void){

	mpu6050_init();

	while(1){

		mpu6050_read_accel(ACCEL_DATA_START_ADDR);

		x = ((data_rec[0] << 8) | data_rec[1]);
		y = ((data_rec[2] << 8) | data_rec[3]);
		z = ((data_rec[4] << 8) | data_rec[5]);

		xg = (x / 16384.0);
		yg = (y / 16384.0);
		zg = (z / 16384.0);
	}

}

