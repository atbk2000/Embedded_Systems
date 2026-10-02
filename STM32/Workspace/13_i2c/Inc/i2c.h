/*
 * i2c.h
 *
 *  Created on: 24 de set. de 2026
 *      Author: Antonio Thomaz
 */

#ifndef I2C_H_
#define I2C_H_

void i2c_init(void);
void I2C1_byteRead(char saddr, char maddr, char* data);
void I2C1_burstRead(char saddr, char maddr, int n, char* data);
void I2C1_burstWrite(char saddr, char maddr, int n, char* data);


#endif /* I2C_H_ */
