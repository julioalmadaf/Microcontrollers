#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "GPIO.h"
#include "ADC.h"

unsigned char FMTIM;
unsigned char FLED;
unsigned int CounterLed;

//PTA3 PARA EL LCD
//PTA2 es el del switch , CAMBI” A LCD
//PTA1 led para cada segundo , CAMBI” A LCD
//PTA0 POT , cambi” a LCD
//PTB0 RX
//PTB1 TX
//PTB2 Y 3 RS Y E
//PTB4 A 7 MOTOR

interrupt 12 void MTIM_ISR (void) //INTERRUPCION MTIM
{
	(void) MTIMSC;  
	MTIMSC_TOF=0;  
	FMTIM=1;
}

void initGPIO (void){ //INICIALIZACION DE LOS PINES
	PTBDD = 0xFF; //pin salida
	PTADD= 0x0F; // pin salida
	MTIMSC=0b01100000; //MTIM interrupt, reset counter
	MTIMCLK=0b00001000; // prescaler 256 del bus clock (4Mhz)
	MTIMMOD=1; // Entra a la interrupcion cada 64us
	FLED=1; //flag para indicar que led comienza encendido
}

void ControlLED(void)		//TIENE OTRAS FUNCIONES PERO ERA PARA ENCENDER EL LED CADA SEGUNDO PERO SE DESCARTO POR FALTA DE PINES
{
		if(FLED==1)
		{
		FLED=0;
		}
		else
		{
			FLED=1;
		}
		CounterLed=0;
}

