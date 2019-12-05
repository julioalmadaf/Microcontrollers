#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "MotorDriver.h"
#include "GPIO.h"
#include "ADC.h"
#include "RXTX.h"
#include "Validation.h"


unsigned char done[]={"\n\rDONE\n\r"};
unsigned char OverTemp[]={"OVERTEMPERATURE DETECTED\n\r"};
unsigned char CounterStr=0;
unsigned char k=0;
unsigned char j=0;
unsigned char l=0;


void TX(void){
	(void) SCIS1;

	if(F5SEGS)
	{
		if(j<7) SCID=temperature[j++];
		else
		{
			j=0;
			CounterTemp=0;
			F5SEGS=0;
			SCIC2=0x2C;
		}
	}
	else if(FOVTEMP)
	{
		
		if(j<26) SCID=OverTemp[j++];
		else
		{
			j=0;
			SCIC2=0x2C;
			FOVREADY=1;
		}
	}
	else if(FDONE)
	{
		
		if(j<7) SCID=done[j++];
		else
		{
			j=0;
			SCIC2=0x2C;
			FDONE=0;
		}
	}
	else{
		SCIC2=0x2C;
	}
}

void RX(void){
	(void) SCIS1;
	if(SCID!=13)
	{
		str[k++]=SCID; 
		CounterStr++;
	}
	else 
	{
		str[k]=13;
		SCIC2=0xAC;
		Eval();
		k=0;
	}

}


interrupt 15 void ISR_rx (void)
{
	RX();
}


interrupt 16 void ISR_tx (void)
{ 
	TX();
}

void initRXTX(void){
	SCIBD=26;
	SCIC2=0x2C;
}




