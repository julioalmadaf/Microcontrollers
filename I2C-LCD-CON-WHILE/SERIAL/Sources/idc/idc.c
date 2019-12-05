#include <hidef.h>
#include "derivative.h"
#include "lcd.h"
#include "DELAYMS.h"
#include "idc.h"
#define IICPorts	SOPT2_IICPS

//inicializacion IIC
void init_IIC_STRUCT(I2C_t p){
	IICF = p.baudrate;
	IICC = p.control;
	IICPorts = p.ports;
}

void clear_flag_IIC(void){
	// Apagamos la flag asociada a la interrupción 
	(void)IICS;			// Leemos el registro 
	IICS_IICIF = 1;		// Escribimos uno para limpiar el bit
}

void IIC_send_byte(unsigned char data) {
	// Manda un byte por el bus de datos
	IIC_start_condition();
	IICD = data; 		// Mandamos el byte
	do
		asm nop;
	while(IICS_IICIF == 0); //Esperar a que se complete la transmision
	clear_flag_IIC();
}

void IIC_start_condition(void) {
	IICC_MST=1;	// Mandamos el startbit
}

void IIC_stop_condition(void) {
    IICC_MST = 0; 	// Mandamos el stopbit
}

void start_communication(unsigned char salve){
	IIC_start_condition();
	IIC_send_byte(salve);
	clear_flag_IIC();
	
}

interrupt 17 void IIC_INTERRUPT(void){
	clear_flag_IIC();	
}
