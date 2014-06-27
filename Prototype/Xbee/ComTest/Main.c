#define F_CPU			32000000UL

#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include <libs/external/twi_master_driver.h>

#include <libs/calib32MClock.h>
#include <libs/rtc.h>
#include <libs/uart.h>
#include <libs/Mpu9150.h>

FILE uartStdOut = FDEV_SETUP_STREAM (putCharUartD0, NULL, _FDEV_SETUP_WRITE);

TWI_Master_t twiMaster;

int main(void)
{
	
	// Set clock to calibrated 32Mhz
	clock_init32MCalibrate();
	
	// Init uart D0 and set stdout
	initUartD0(F_CPU, 9600, 0);
	stdout = &uartStdOut;
	
	TWI_MasterInit(&twiMaster, &TWIC, TWI_MASTER_INTLVL_LO_gc, TWI_BAUD(F_CPU, MPU_TWI_RATE));
	initRTC();
	
	// Use internal indicate led
	PORTE.DIRSET = PIN0_bm;
	
	// enabled interrupts
	PMIC.CTRL = PMIC_LOLVLEN_bm;
	sei();
	
	//printf("\r\n_____PROGRAM STARTED_____\r\n");
	
	init9150();
	
	int16_t ax, ay, az, gx, gy, gz, mx, my, mz;
    while(1)
    {
		getAcceleration9150(&ax, &ay, &az);
		getRotation9150(&gx, &gy, &gz);
		getCompass9150(&mx, &my, &mz);
		
		printf("%d,%d,%d\r\n", ax, ay, az);
		
		PORTE.OUTTGL = PIN0_bm; // We are still alive indicator
        _delay_ms(20);
    }
}