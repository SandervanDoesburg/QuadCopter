/*
 * rtc.c
 *
 * Created: 6/22/2014 2:43:18 PM
 *  Author: Sander
 */ 
#include "rtc.h"
#include <avr/io.h>

void initRTC(void) {
	OSC.CTRL |= OSC_RC32KEN_bm; //RTC clock aanzetten
	do {} while ( ( OSC.STATUS & OSC_RC32KRDY_bm ) == 0); //wachten totdat hij gestabilizeerd is
	RTC.PER = 0xFFFF; 
	RTC.CTRL = RTC_PRESCALER_OFF_gc; //prescaler van 1
	CLK.RTCCTRL = CLK_RTCSRC_RCOSC_gc | CLK_RTCEN_bm; // interne 32 kHz precale van 1024
	while( ( RTC.STATUS &= 0x01 ) ); // wachten totdat deze klaar is
}