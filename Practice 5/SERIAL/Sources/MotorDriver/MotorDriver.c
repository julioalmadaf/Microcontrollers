#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "MotorDriver.h"
#include "GPIO.h"
#include "ADC.h"
#include "Validation.h"

unsigned char i;
unsigned char secuencia[]={0x80, 0xC0, 0x40, 0x60, 0x20, 0x30, 0x10, 0x90}; //secuencia motor
unsigned int count_step;
unsigned char direction;
unsigned int velocidad;

void ControlMotor(void) //PARA CONTROLAR EL MOTOR
{
	if(direction==1)		//CHECA LA DIRECCION EN LA QUE VA EL MOTOR
	{
		PTBD = secuencia[(i++)%8];
		if(FGRAD==1)		//PARA QUE SE MUEVA POR GRADOS
		{
			count_step++;
			if(count_step>=steps)
			{
				FGRAD=0;
				count_step=0;				
			}
		}
	}
	else {			
		PTBD = secuencia[(i--)%8];
		if(FGRAD==1)				//PARA QUE SE MUEVA POR GRADOS
		{
			count_step++;
			if(count_step>=steps)
			{
				FGRAD=0;
				count_step=0;				
			}
		}
	}
}


