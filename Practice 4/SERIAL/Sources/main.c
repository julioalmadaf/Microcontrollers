#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "ADC.h"
#include "GPIO.h"
#include "MotorDriver.h"
#include "RXTX.h"
#include "Validation.h"

unsigned char ADC_INTERRUPTION;
unsigned char MOVER_MOTOR;

void main(void) {
	initRXTX();
	initGPIO();
	TEMP_LIMIT=500;
	velocidad=1350;

	EnableInterrupts;
	for(;;) {	
		__RESET_WATCHDOG();



		//**************************AL HABER INTERRUPCION DE MTIM INCREMENTA CONTADOR Y ENCIENDE ADC*****************
		if(FMTIM==1){
			counter++;
			CounterLed++;
			ADC_ON;
		}

		//**************************** FUNCION PARA MOVER MOTOR IZQ DER *****************************************
		if(FRPS==1){
			velocidad=39000/valor;// CONVERSION
			FRPS=0;
		}

		if(counter >= velocidad){
			if(FMON==1)
			{
				ControlMotor();
			}else if(FMON==0 && FGRAD==1){
				ControlMotor();
			}

			counter=0;
		}

		//*****************TOMA VALOR DE ADC CADA VEZ QUE SE GENERA LA INTERRUPCION Y SE GENERA LA CONVERSION PARA VELOCIDAD****************
		if(FADC==1){		
			if(ADC_samples()>999){
				temp=999;
			}else{
				temp=ADC_samples();
			}
			FADC=0;
		}


		//***************************** ENCENDER Y APAGAR LED CADA SEGUNDO *********************************************
		if(CounterLed>=6800)
		{	
			ControlLED();
			CounterTemp++;

			if(CounterTemp>=3) //SE ESTA TARDANDO MUCHO
			{ 
				temperature[6]= '\r';
				temperature[5]= '\n';
				temperature[4]= (temp*10)%10+48;
				temperature[3]= '.';
				temperature[2]= (temp%10)+48;
				temp/=10;
				temperature[1]= (temp%10)+48;
				temp/=10;
				temperature[0]= (temp%10)+48;

				F5SEGS=1;
				SCIC2=0xAC;
			}

		}
		FMTIM=0;

		if((temp*10)>= TEMP_LIMIT){
			MOTOR_OFF;
			FOVTEMP=1;
			if(FOVREADY!=1){
				SCIC2=0xAC; //COMO MANDARLO SOLO UNA VEZ	
			}
		}
		else if(FMOFF==0)
		{
			FOVTEMP=0;
			FOVREADY=0;
			FMON=1;
		}
	}
}
