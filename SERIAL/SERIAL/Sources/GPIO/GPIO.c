#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "GPIO.h"
#include "ADC.h"

interrupt 12 void MTIM_ISR (void)
{
	(void) MTIMSC;  //1er paso borrado /llamas al valor del canal 1
	MTIMSC_TOF=0;  //2o paso borrado /borras la bandera
	FMTIM=1;
	//CounterLed++;
}

void initGPIO (void){
	PTBDD = 0xF0; //pin salida
	PTADD_PTADD1 = 1; // LED PARA CADA SEGUNDO
	//PTADD_PTADD1 = 1; //LED DE PRUEBA DE ENTER PRESIONADO
	PTAPE_PTAPE2=1; // Enable pull up resistor
	ADCCFG= 0x08;
	ADC_ON; //Para encender ADC
	MTIMSC=0b01100000; //MTIM interrupt, reset counter
	MTIMCLK=0b00001000; // prescaler 256 del bus clock (4Mhz)
	MTIMMOD=1; // Entra a la interrupcion cada 64us
	FLED=1; //flag para indicar que led comienza encendido
}

unsigned char SwitchGPIO(void){ // funcion que nomas toma el valor del switch pero no se como hacerlo
	return PTAD_PTAD2;	
}

void ControlLED(void) //para encender led cada segundo
{
		if(FLED==1){
		LED_OFF;
		FLED=0;
		}else{
			LED_ON;
			FLED=1;
		}
		CounterLed=0;
}

