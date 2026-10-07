/*
 * mpu6050.c
 *
 *  Created on: 5 de out. de 2026
 *      Author: Antonio Thomaz
 */

#include "mpu6050.h"

char data;
uint8_t data_rec[6];

void mpu6050_read_address(uint8_t reg){
	I2C1_byteRead(DEVICE_ADDR, reg, &data);
}

void mpu6050_write(uint8_t reg, char value){

	char data[1];
	data[0] = value;

	I2C1_burstWrite(DEVICE_ADDR, reg, 1, data);
}

void mpu6050_read_accel(uint8_t reg){
	I2C1_burstRead(DEVICE_ADDR, reg, 6, (char*)data_rec);
}

void mpu6050_init(void){

	// Enable I2C
	I2C1_init();

	// Read WHO_AM_I_R, this should return 0x68
	mpu6050_read_address(WHO_AM_I_R);

	// Wake the sensor up (MPU6050 boots into sleep mode)
	mpu6050_write(PWR_MGMT_1_R, WAKE_UP);

	// Set accelerometer full-scale range to +-2g
	mpu6050_write(ACCEL_CONFIG_R, ACCEL_FS_2G);
}
