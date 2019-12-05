#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "ADC.h"
#include "GPIO.h"
#include "MotorDriver.h"
#include "RXTX.h"
#include "Validation.h"
#include "LCD.h"
#include "DELAYMS.h"

unsigned char ADC_INTERRUPTION;
unsigned char MOVER_MOTOR;
unsigned char flcd;
unsigned int g=0;
unsigned int adc=0;

////////Generador de temperatura ciclico
unsigned int ADC_val_em(void) 
{
	g++;
	adc = g*7;
	if(adc>999)
	{
		g=0;
		adc=0;
	}
	return adc;
}

void main(void) {

	initRXTX(); //inicializacion del RXTX
	initGPIO();//inicializacion de los puertos
	LCD_Init(); //inicializacion del LCD
	TEMP_LIMIT=5000;
	velocidad=6;
	EnableInterrupts; 
	for(;;) {	
		SOPT1 = 0x52; //deshabilitacion de watchdog
		//__RESET_WATCHDOG();
		
		//**************************AL HABER INTERRUPCION DE MTIM INCREMENTA CONTADOR Y ENCIENDE ADC*****************
		if(FMTIM==1)
		{
			counter++;
			CounterLed++;
		}

		//**************************** FUNCION PARA MOVER MOTOR IZQ DER *****************************************
		if(FRPS==1)
		{
			velocidad=3400/valor;// CONVERSION
			FRPS=0;
		}

		if(counter >= velocidad)
		{
			if(FMON==1)
			{
				ControlMotor();
			}
			else if(FMON==0 && FGRAD==1)
			{
				ControlMotor();
			}
			counter=0;
		}

		//*****************TOMA VALOR DE ADC CADA VEZ QUE SE GENERA LA INTERRUPCION Y SE GENERA LA CONVERSION PARA VELOCIDAD****************
		if(samples==1)
		{
			if(ADC_val_em()>999)
			{
				temp=999;
			}
			else
			{
				temp=ADC_val_em();
			}
			samples=0;
		}

		//***************************** Manda temperatura cada 5 segundos *********************************************
		if(CounterLed>=2500)
		{	
			ControlLED();
			CounterTemp++;
			samples=1;
			if(CounterTemp>=1) //***checar si puedo imprimir antes la tempe
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
//////////////////// Apaga el motor cuando se pasa la temperatura
		if((temp*10)>= TEMP_LIMIT)
		{
			MOTOR_OFF;
			FOVTEMP=1;
			if(FOVREADY!=1)
			{
				SCIC2=0xAC; 	
			}
		}
		else if(FMOFF==0)
		{
			FOVTEMP=0;
			FOVREADY=0;
			FMON=1;
		}
		
		CCWRPS(); //funcion que imprime en el LCD
	}
}
