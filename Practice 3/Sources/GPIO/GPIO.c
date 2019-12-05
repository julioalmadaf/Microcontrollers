#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "GPIO.h"



interrupt 12 void MTIM_ISR (void)
{
	(void) MTIMSC;  //1er paso borrado /llamas al valor del canal 1
	MTIMSC_TOF=0;  //2o paso borrado /borras la bandera
	FMTIM=1;
}


void initGPIO (void){
	PTBDD = 0xF0; //pin salida
	PTAPE_PTAPE2=1; // Enable pull up resistor
	APCTL1_ADPC0=1; // configura canal 0 como entrada analogica
	ADCSC1= 0b011000000; //inicializa el ADC con interrupciones y conversiones continuas
	MTIMSC=0b01100000; //MTIM interrupt, reset counter
	MTIMCLK=0b00001000; // prescaler 256 del bus clock (4Mhz)
	MTIMMOD=1; // Entra a la interrupcion cada 64us
}

unsigned char SwitchGPIO(void){ // funcion que nomas toma el valor del switch pero no se como hacerlo
	return PTAD_PTAD2;	
}



void WriteMotor( unsigned char i){
	PTBD=i;//secuencia[i%8]; aqui devolvere la secuencia a PTBD
}
