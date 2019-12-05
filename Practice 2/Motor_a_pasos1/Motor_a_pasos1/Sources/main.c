#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "ADC.h"
#include "DELAY.h"
#include "GPIO.h"

unsigned char i;
unsigned char secuencia[]={0x80, 0xC0, 0x40, 0x60, 0x20, 0x30, 0x10, 0x90};
unsigned char DELAY_ITERATIONS;

void main(void) {
	initGPIO();
	for(;;) {
		//__RESET_WATCHDOG();	/* feeds the dog */
	
		DELAY_ITERATIONS= (ADC_samples()*6) / 255;
			if(DELAY_ITERATIONS<1) DELAY_ITERATIONS=1;
			if(SwitchGPIO()==1)
				{
					WriteMotor(secuencia[(i++)%8]);
					delay(DELAY_ITERATIONS);
				}
				else {			
					WriteMotor(secuencia[(i--)%8]);
					delay(DELAY_ITERATIONS);	
				}
	}
}

