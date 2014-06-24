/*
 * uart.c
 *
 * Created: 6/20/2014 9:45:18 PM
 *  Author: Sander
 */

#include "uart.h"

void initUartD0(uint32_t f_cpu, uint32_t baud, uint8_t clk2x) {
	
	PORTD.DIRSET      = PIN3_bm;
	PORTD.DIRCLR      = PIN2_bm;
	
	int8_t bscale = calc_bscale(f_cpu, baud, clk2x);
	uint16_t bsel = calc_bsel(f_cpu, baud, bscale, clk2x);

	USART_InterruptDriver_Initialize(&uartD0, &USARTD0, USART_DREINTLVL_LO_gc);
	USART_Format_Set(&USARTD0, USART_CHSIZE_8BIT_gc, USART_PMODE_DISABLED_gc, !USART_SBMODE_bm);
	USART_Rx_Enable(&USARTD0);
	USART_Tx_Enable(&USARTD0);
	USART_RxdInterruptLevel_Set(&USARTD0, USART_RXCINTLVL_LO_gc);
	USART_Baudrate_Set(&USARTD0, bsel, bscale);

}

int putCharUartD0(char data, FILE *stream) {
	
	if(USART_TXBuffer_FreeSpace(&uartD0)) {
		return USART_TXBuffer_PutByte(&uartD0, data);
	}
	
	return 0;
	
}

int8_t calc_bscale(uint32_t f_cpu, uint32_t baud, uint8_t clk2x)
{
	int8_t   bscale;
	uint16_t bsel;

	for (bscale = -7; bscale<8; bscale++) {
		if ( (bsel = calc_bsel(f_cpu, baud, bscale, clk2x)) < 4096 ) return bscale;
	}

	return bscale;
}

uint16_t calc_bsel(uint32_t f_cpu, uint32_t baud, int8_t scale, uint8_t clk2x)
{
	uint8_t factor = 16;

	factor = factor >> (clk2x & 0x01);
	if ( scale < 0 ) {
		return round(  (((double)(f_cpu)/(factor*(double)(baud))) - 1) * (1<<-(scale))  );
		} else {
		return round(  ((double)(f_cpu)/(factor*(double)(baud))/(1<<(scale))) - 1);
	}
}

ISR(USARTD0_RXC_vect)
{
  USART_RXComplete((USART_data_t *) &uartD0.usart);
}

ISR(USARTD0_DRE_vect)
{
  USART_DataRegEmpty((USART_data_t *) &uartD0.usart);
}