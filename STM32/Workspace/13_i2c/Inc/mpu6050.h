/*
 * mpu6050.h
 *
 *  Created on: 5 de out. de 2026
 *      Author: Antonio Thomaz
 */

#ifndef MPU6050_H_
#define MPU6050_H_

#include "i2c.h"
#include <stdint.h>

#define WHO_AM_I_R				0x75
#define DEVICE_ADDR				0x68 // 0x68 if AD0 pin is low, 0x69 if AD0 is high
#define PWR_MGMT_1_R			0x6B
#define ACCEL_CONFIG_R			0x1C
#define ACCEL_DATA_START_ADDR   0x3B

#define WAKE_UP					0x00 // clears SLEEP bit, starts sampling
#define ACCEL_FS_2G				0x00 // full-scale range select: ±2g

void mpu6050_init(void);
void mpu6050_read_accel(uint8_t reg);

#endif /* MPU6050_H_ */
