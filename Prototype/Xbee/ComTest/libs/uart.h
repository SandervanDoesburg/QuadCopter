/*
 * uart.h
 *
 * Created: 6/20/2014 9:45:05 PM
 *  Author: Sander
 */ 


#ifndef UART_H_
#define UART_H_

#include <stdio.h>
#include <libs/external/usart_driver.h>


void initUartD0(uint32_t f_cpu, uint32_t baud, uint8_t clk2x);
int8_t calc_bscale(uint32_t f_cpu, uint32_t baud, uint8_t clk2x);
uint16_t calc_bsel(uint32_t f_cpu, uint32_t baud, int8_t scale, uint8_t clk2x);
int putCharUartD0(char c, FILE *stream);

USART_data_t uartD0;

#endif /* UART_H_ */