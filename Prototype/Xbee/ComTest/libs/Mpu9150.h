/*
 * _9150.h
 *
 * Created: 6/21/2014 10:08:19 PM
 *  Author: Sander
 */ 


#ifndef Mpu9150_H_
#define Mpu9150_H_

#include <stdio.h> // Use printf
#include <libs/twi.h>

uint8_t init9150(void);
void getAcceleration9150(int16_t *x, int16_t *y, int16_t *z);
void getRotation9150(int16_t *x, int16_t *y, int16_t *z);
void getCompass9150(int16_t *x, int16_t *y, int16_t *z);

uint8_t buffer[16];

#define MPU9150_ID						0x68
#define AK8975_ID						0x0C
#define MPU_TWI_RATE					400000

/* REGISTER ADDRESSES */
#define AK8975_CNTL						0x0A
#define AK8975_STATUS1					0x02
#define AK8975_MAG_XOUT_H				0x03

#define MPU9150_WHO_AM_I				0x75
#define MPU9150_CONFIG					0x1A
#define MPU9150_PWR_MGMT_1				0X6B
#define MPU9150_GYRO_CONFIG				0x1B
#define MPU9150_ACCEL_CONFIG			0x1C
#define MPU9150_ACCEL_XOUT_H			0x3B
#define MPU9150_GYRO_XOUT_H				0x43
#define MPU9150_INT_PIN_CFG				0x37

/* REGISTER GROUPS */
#define AK8975_CONTROL_MODE_gm			0x15
#define AK8975_CONTROL_MODE_gp			0

#define MPU9150_CLKSEL_gm				0x07
#define MPU9150_CLKSEL_gp				0

#define MPU9150_PWR1_SLEEP_gm			0x40
#define MPU9150_PWR1_SLEEP_gp			6

#define MPU9150_GCONFIG_FS_SEL_gm		0x18
#define MPU9150_GCONFIG_FS_SEL_gp		3

#define MPU9150_ACONFIG_FS_SEL_gm		0x18
#define MPU9150_ACONFIG_FS_SEL_gp		3

#define MPU9150_I2C_BYPASS_EN_gm		0x02
#define MPU9150_I2C_BYPASS_EN_gp		1


/* REGISTER VALUES */
#define MPU9150_CLOCK_INTERNAL			0x00
#define MPU9150_CLOCK_PLL_XGYRO			0x01
#define MPU9150_CLOCK_PLL_YGYRO			0x02
#define MPU9150_CLOCK_PLL_ZGYRO			0x03

#define MPU9150_GYRO_FS_250				0x00
#define MPU9150_GYRO_FS_500				0x01
#define MPU9150_GYRO_FS_1000			0x02
#define MPU9150_GYRO_FS_2000			0x03

#define MPU9150_ACCEL_FS_2				0x00
#define MPU9150_ACCEL_FS_4				0x01
#define MPU9150_ACCEL_FS_8				0x02
#define MPU9150_ACCEL_FS_16				0x03

#endif /* Mpu9150_H_ */