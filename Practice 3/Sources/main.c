#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "ADC.h"
#include "DELAY.h"
#include "GPIO.h"

unsigned char i;
unsigned char secuencia[]={0x80, 0xC0, 0x40, 0x60, 0x20, 0x30, 0x10, 0x90}; //invertir

unsigned char ADC_INTERRUPTION;
unsigned char MOVER_MOTOR;
unsigned int velocidad;

unsigned char adc_val;
unsigned int counter;

void main(void) {
	initGPIO();
	EnableInterrupts;

	for(;;) {	
		__RESET_WATCHDOG();

		if(FMTIM==1){
			counter++;
			ADC_ON();

		}
		FMTIM=0;
		if(FADC==1){
			adc_val=ADC_samples();
		}
		FADC=0;

		velocidad=350-((adc_val));
		if(counter == velocidad){
			if(SwitchGPIO()==1)
			{
				WriteMotor(secuencia[(i++)%8]);
			}
			else {			
				WriteMotor(secuencia[(i--)%8]);	
			}
			counter=0;
		}
	}
}
