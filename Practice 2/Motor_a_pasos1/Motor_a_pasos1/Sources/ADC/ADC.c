#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "ADC.h"

unsigned char ADC_samples(void){
	ADCSC1= 0x00; // para tomar lectura del puerto ADC0
	return ADCRL; //Guarda el valor del adc
}
