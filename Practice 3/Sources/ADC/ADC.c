#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "ADC.h"

interrupt 19 void ADC_ISR (void)
{
	FADC=1;
	ADC_OFF();
}

unsigned char ADC_samples(void){
	return ADCRL; //Guarda el valor del adc
}

void ADC_ON(void){
	ADCSC1= 0b011000000;
}

void ADC_OFF(void){
	ADCSC1= 0b00011111;
}
