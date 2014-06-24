/*
 * _9150.c
 *
 * Created: 6/21/2014 10:08:04 PM
 *  Author: Sander
 */ 
#include "Mpu9150.h"

uint8_t init9150() {
	
	//printf("[Mpu9150] Starting with initializing\r\n");
	
	uint8_t id;
	twiReadBytes(MPU9150_ID, MPU9150_WHO_AM_I, 1, &id);
	//printf("[Mpu9150] I2C Id: 0x%x\r\n", id);
	
	twiSetGroup(MPU9150_ID, MPU9150_PWR_MGMT_1, MPU9150_CLKSEL_gm, MPU9150_CLKSEL_gp, MPU9150_CLOCK_PLL_XGYRO); // Set clock source to XGYRO
	//printf("[Mpu9150] Clock source set to XGYRO\r\n");
	
	twiSetGroup(MPU9150_ID, MPU9150_GYRO_CONFIG, MPU9150_GCONFIG_FS_SEL_gm, MPU9150_GCONFIG_FS_SEL_gp, MPU9150_GYRO_FS_250); // Set gyro scale
	//printf("[Mpu9150] Gyro set to 250 degrees/sec scale\r\n");
	
	twiSetGroup(MPU9150_ID, MPU9150_ACCEL_CONFIG, MPU9150_ACONFIG_FS_SEL_gm, MPU9150_ACONFIG_FS_SEL_gp, MPU9150_ACCEL_FS_2); // Set accel scale
	//printf("[Mpu9150] Accel set to 2g scale\r\n");
	
	twiSetGroup(MPU9150_ID, MPU9150_PWR_MGMT_1, MPU9150_PWR1_SLEEP_gm, MPU9150_PWR1_SLEEP_gp, 0); // Disable sleep
	//printf("[Mpu9150] Sleep disabled\r\n");
	
	twiSetGroup(MPU9150_ID, MPU9150_INT_PIN_CFG, MPU9150_I2C_BYPASS_EN_gm, MPU9150_I2C_BYPASS_EN_gp, 1); // Enable i2c bypass mode for use with magnetometer
	//printf("[Mpu9150] I2C bypass mode enabled\r\n");
	
	twiSetGroup(AK8975_ID, AK8975_CNTL, AK8975_CONTROL_MODE_gm, AK8975_CONTROL_MODE_gp, 1); // Start first magneto measurement (no free running mode...)

	return 1;
}

void getAcceleration9150(int16_t *x, int16_t *y, int16_t *z) {
	
	twiReadBytes(MPU9150_ID, MPU9150_ACCEL_XOUT_H, 6, buffer);
	*x = (((int16_t)buffer[0]) << 8) | buffer[1];
	*y = (((int16_t)buffer[2]) << 8) | buffer[3];
	*z = (((int16_t)buffer[4]) << 8) | buffer[5];
	
}

void getRotation9150(int16_t *x, int16_t *y, int16_t *z) {
	
	twiReadBytes(MPU9150_ID, MPU9150_GYRO_XOUT_H, 6, buffer);
	*x = (((int16_t)buffer[0]) << 8) | buffer[1];
	*y = (((int16_t)buffer[2]) << 8) | buffer[3];
	*z = (((int16_t)buffer[4]) << 8) | buffer[5];
	
}

void getCompass9150(int16_t *x, int16_t *y, int16_t *z) {
	
	twiReadBytes(AK8975_ID, AK8975_STATUS1, 1, buffer); // Check for new data
	
	if(buffer[0]) { // We got new data, awesome!
		
		twiReadBytes(AK8975_ID, AK8975_MAG_XOUT_H, 6, buffer);
	
	
		*x = (((int16_t)buffer[0]) << 8) | buffer[1];
		*y = (((int16_t)buffer[2]) << 8) | buffer[3];
		*z = (((int16_t)buffer[4]) << 8) | buffer[5];
	
	}
	
	twiSetGroup(AK8975_ID, AK8975_CNTL, AK8975_CONTROL_MODE_gm, AK8975_CONTROL_MODE_gp, 1); // Start next measurement
}