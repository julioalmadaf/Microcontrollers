#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

unsigned char secuencia[]={0xEF,0xDF,0xBF,0x7F,0xBF, 0xDF}; //secuencia completa que seguiran los leds
unsigned char i; // para mover el arreglo de la secuencia de los LEDS
void delay(void)
{
	SRTISC=0b00000111; //iniciar timer 1 SEGUNDO
	do{__RESET_WATCHDOG();}
	while(SRTISC_RTIF==0);// bandera de interrupcion 
	SRTISC_RTIACK=1; //para bajar la bandera
	SRTISC=0; //se reinicia 
}

void main(void) {	
 //	EnableInterrupts;
	/* include your code here */
  PTBDD=0xF0; //SALIDA PTB7 A PTB4
  PTAPE_PTAPE2=1; //HABILITA PULLUP PARA PTA
  for(;;) {
	  if(PTAD_PTAD2 == 1){
		  PTBD=secuencia[(i++)%4];
		  delay();
		  }
	  else{
		  PTBD=secuencia[(i++)%6];
		  delay();
	  }
    __RESET_WATCHDOG();	/* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}



