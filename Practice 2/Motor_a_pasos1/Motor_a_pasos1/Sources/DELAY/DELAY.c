#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "DELAY.h"


void delay( unsigned char DELAY_ITERATIONS)
{
	unsigned char j;
	
	SRTISC= 0b00000001;  //inicializas timer cada 64 ms
	for(j=0; j<DELAY_ITERATIONS;  j++){
		do{
			__RESET_WATCHDOG();
		}while (SRTISC_RTIF==0); //mientras  es 0 el tiempo no ha acabado
		SRTISC_RTIACK=1;
	}
	SRTISC = 0x00;			//reinicia todo, deshabilita interrupciones
}
