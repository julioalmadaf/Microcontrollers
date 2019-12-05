#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "ADC.h"


interrupt 19 void ADC_ISR (void)
{
	FADC=1;
	ADC_OFF; 
}

unsigned int ADC_samples(void){
	return ADCR; //Guarda el valor del adc (temperatura)
}


