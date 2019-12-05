#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "MotorDriver.h"
#include "GPIO.h"
#include "ADC.h"
#include "Validation.h"

unsigned char i;
unsigned char secuencia[]={0x80, 0xC0, 0x40, 0x60, 0x20, 0x30, 0x10, 0x90}; //secuencia motor
unsigned int count_step;

void ControlMotor(void){
	if(direction==1)
	{
		PTBD = secuencia[(i++)%8];
		if(FGRAD==1){
			count_step++;
			if(count_step>=steps){
				FGRAD=0;
				count_step=0;				
			}
		}
	}
	else {			
		PTBD = secuencia[(i--)%8];
		if(FGRAD==1){
			count_step++;
			if(count_step>=steps){
				FGRAD=0;
				count_step=0;				
			}
		}
	}
}

//void ControlMotor(void){
//	if(direction==1)
//	{
//		if(FGRAD==0){
//			PTBD = secuencia[(i++)%8];
//		}
//		else{
//
//		}
//	}
//	else if(direction==0){
//		if(){
//			PTBD = secuencia[(i--)%8];
//		}
//		else{
//
//		}
//	}		
//}
