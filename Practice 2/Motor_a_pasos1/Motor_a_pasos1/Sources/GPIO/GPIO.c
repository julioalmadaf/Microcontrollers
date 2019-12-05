#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "GPIO.h"



void initGPIO (void){
		PTBDD = 0xF0; //pin salida
		PTAPE_PTAPE2=1; // Enable pull up resistor
		APCTL1_ADPC0=1; // configura canal 0 como entrada analogica
}

unsigned char SwitchGPIO(void){ // funcion que nomas toma el valor del switch pero no se como hacerlo
	return PTAD_PTAD2;	
}

void WriteMotor( unsigned char i){
	PTBD=i;//secuencia[i%8]; aqui devolvere la secuencia a PTBD
}
