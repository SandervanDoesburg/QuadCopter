#include "calib32MClock.h"

void clock_init32MCalibrate(void) {
	
	// Select 32 kHz crystal and low power mode
	OSC.XOSCCTRL = ( OSC.XOSCCTRL & ~OSC_XOSCSEL_gm) | OSC_XOSCSEL_32KHz_gc;

	// Switch to calibrated 32MHz oscillator and disable 2 MHz RC oscillator
	CLKSYS_Enable( OSC_XOSCEN_bm );
	CLKSYS_Enable( OSC_RC32MEN_bm );
	do {} while ( CLKSYS_IsReady( OSC_XOSCRDY_bm ) == 0 );
	do {} while ( CLKSYS_IsReady( OSC_RC32MRDY_bm ) == 0 );
	CLKSYS_Main_ClockSource_Select( CLK_SCLKSEL_RC32M_gc );
	CLKSYS_Disable( OSC_RC2MEN_bm );
	OSC.DFLLCTRL = (OSC.DFLLCTRL & ~OSC_RC32MCREF_gm) | OSC_RC32MCREF_XOSC32K_gc;
	DFLLRC32M.CTRL |= DFLL_ENABLE_bm;
}