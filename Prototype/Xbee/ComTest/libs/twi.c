/*
 * twi.c
 *
 * Created: 6/21/2014 10:11:07 PM
 *  Author: Sander
 */ 
#include "twi.h"

uint8_t twiReadBytes(uint8_t address, uint8_t regAddress, uint8_t bytesToRead, uint8_t *writeTo) {
	
	TWI_MasterWriteRead(&twiMaster, address, &regAddress, 1, bytesToRead);
	while(twiMaster.status != TWIM_STATUS_READY);
	
	memcpy(writeTo, twiMaster.readData, bytesToRead);
	return 1;
	
}

/*
WARNING: THIS FUNCTION IS SLOW BECAUSE OF MEMORY ALLOCATIONS AND COPIES, TRY TO USE IT ONLY AT INITIALISATIONS
If you plan to write a lot of data use the other twiWriteBytes function.
*/
uint8_t twiWriteBytesReg(uint8_t address, uint8_t regAddress, uint8_t *writeData, uint8_t bytesToWrite) {
	
	uint8_t *tmp = malloc(bytesToWrite + 1); // Allocate memory
	*tmp = regAddress; // Set first byte to register address
	memcpy(tmp + 1, writeData, bytesToWrite); // Move writeData to temp memory
	
	TWI_MasterWrite(&twiMaster, address, tmp, bytesToWrite);
	while(twiMaster.status != TWIM_STATUS_READY);
	
	free(tmp); // Free temporarily memory block
	
	return 1;
	
}

uint8_t twiWriteBytes(uint8_t address, uint8_t *writeData, uint8_t bytesToWrite) {
	
	TWI_MasterWrite(&twiMaster, address, writeData, bytesToWrite);
	while(twiMaster.status != TWIM_STATUS_READY);
	
	return 1;
	
}

uint8_t twiSetGroup(uint8_t address, uint8_t regAddress, uint8_t group_mask, uint8_t group_position, uint8_t value) {
	
	uint8_t buffer[2]; // Allocate buffer for register address and its value
	
	twiReadBytes(address, regAddress, 1, &buffer[1]); // Retrieve current register byte
	
	buffer[0] = regAddress; // Put register address in twi write buffer
	buffer[1] = (~group_mask & buffer[1]) | (value << group_position); // Add bits to register byte
	
	twiWriteBytes(address, buffer, 2); // Write new register byte
	
	return buffer[1]; // Return new register byte
	
}

/*! TWIC Master Interrupt vector. */
ISR(TWIC_TWIM_vect)
{
	TWI_MasterInterruptHandler(&twiMaster);
}