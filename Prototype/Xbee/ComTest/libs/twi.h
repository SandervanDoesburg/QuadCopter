/*
 * twi.h
 *
 * Created: 6/21/2014 10:10:56 PM
 *  Author: Sander
 */ 


#ifndef TWI_H_
#define TWI_H_

#include <stdlib.h>
#include <string.h>

#include <libs/external/twi_master_driver.h>

extern TWI_Master_t twiMaster;

uint8_t twiReadBytes(uint8_t address, uint8_t regAddress, uint8_t bytesToRead, uint8_t *writeTo);
uint8_t twiWriteBytesReg(uint8_t address, uint8_t regAddress, uint8_t *writeData, uint8_t bytesToWrite);
uint8_t twiWriteBytes(uint8_t address, uint8_t *writeData, uint8_t bytesToWrite);
uint8_t twiSetGroup(uint8_t address, uint8_t regAddress, uint8_t group_mask, uint8_t group_position, uint8_t value);


#endif /* TWI_H_ */