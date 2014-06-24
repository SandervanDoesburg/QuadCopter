/*
#define THROTTLE_MIN 35762
#define THROTTLE_MAX 62097
#define THROTTLE_FACTOR ((THROTTLE_MAX - THROTTLE_MIN) / 255)

	// Timer for pulse width measurement
	TCC0.CTRLB = TC_WGMODE_NORMAL_gc;
	TCC0.CTRLA = TC_CLKSEL_DIV1_gc;
	TCC0.PER = 0xFFFF;
	
	// Trigger pwm port on bothedges
	PORTE.DIRCLR = PIN3_bm;
	PORTB.INT0MASK = PIN3_bm;
	PORTB.PIN3CTRL = PORT_ISC_BOTHEDGES_gc;
	PORTB.INTCTRL = PORT_INT0LVL_LO_gc;

ISR(PORTB_INT0_vect)
{
	if(PORTB.IN & PIN3_bm) { // rising edge
		
		sTime = TCC0.CNT;
		
		} else { // falling edge
		
		if(TCC0.CNT < sTime) { // Overflow correction
			dTime = 0xFFFF - sTime + TCC0.CNT;
			} else {
			dTime = TCC0.CNT - sTime;
		}
		if(dTime < THROTTLE_MIN) {
			dTime = THROTTLE_MIN;
			} else if(dTime > THROTTLE_MAX) {
			dTime = THROTTLE_MAX;
		}
		
		throttle = (dTime - THROTTLE_MIN) / THROTTLE_FACTOR;
	}
}
*/