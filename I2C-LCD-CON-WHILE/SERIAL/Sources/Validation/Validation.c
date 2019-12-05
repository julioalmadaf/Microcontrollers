#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "MotorDriver.h"
#include "GPIO.h"
#include "ADC.h"
#include "RXTX.h"
#include "Validation.h"

unsigned int grados;

unsigned char FRPS;
unsigned char FMON;
unsigned char FDONE;
unsigned char FMOFF;
unsigned char FGRAD;
unsigned int counter;
unsigned int valor;
unsigned int steps;
unsigned char rps1='5';
unsigned char rps2='0';
unsigned char rps3='0';
unsigned char frps=1;


void Eval(void){
	switch(str[0]) //CHECA LA PRIMER LETRA DEL STRING PARA HACER LO QUE ENTRE POR EL SERIAL
	{ 
	case 'R':  //CHECA COMANDO DE RPS
		if(str[1]=='P' && str[2]=='S' && str[3]==':' && str[6]=='.')
		{
			if((str[4] > '/') && (str[4] < ':'))
			{
				if((str[5] > '/') && (str[5] < ':'))
				{
					if((str[7] > '/') && (str[7] < ':') && str[8]==13)
					{
						FRPS=1;
						valor=((str[4]-'0')*100 + (str[5]-'0')*10 + (str[7]-'0')); //GUARDA EL VALOR
						rps1=str[4]; //PARA IMPRIMIR EN LA LCD
						rps2=str[5];
						rps3=str[7];
						FDONE=1;
						frps=0; //PARA DECIRLE AL LCD QUE YA SE USO EL COMANDO RPS
					}
					else
					{
						FDONE=0;
						SCIC2=0x2C;
					}
				}
				else
				{
					FDONE=0;
					SCIC2=0x2C;
				}
			}
			else
			{
				FDONE=0;
				SCIC2=0x2C;
			}
		}
		else
		{
			FDONE=0;
			SCIC2=0x2C;
		}
		break;

	case 'D':  //COMANDO DIR
		if(str[1]=='I' && str[2]=='R' && str[3]==':' && str[4]=='C')
		{
			if(str[5]=='W' && str[6]==13) //CW
			{
				direction=0;
				FDONE=1;
			}
			else if(str[5]=='C' && str[6]=='W' && str[7]==13) //CCW
			{
				direction=1;
				FDONE=1;
			}
			else
			{
				FDONE=0;
				SCIC2=0x2C;
			}
		}
		else
		{
			FDONE=0;
			SCIC2=0x2C;
		}
		break;

	case 'M':  //COMANDO DEL MOTOR
		if(str[1]=='O' && str[2]=='T' && str[3]=='O' && str[4]=='R' && str[5]==':' && str[6]=='O')
		{
			if(str[7]=='N' && str[8]==13) //MOTOR ON
			{
				FMON=1;
				FDONE=1;
				FMOFF=0;
				ControlMotor();
				counter = 0;
				frps=0;
			}
			else if(str[7]=='F' && str[8]=='F' && str[9]==13) //MOTOR OFF
			{
				MOTOR_OFF;
				FMON=0;
				FDONE=1;
				FMOFF=1;
				frps=1;
			}
			else
			{
				FDONE=0;
				SCIC2=0x2C;
			}
		}
		else
		{
			FDONE=0;
			SCIC2=0x2C;
		}
		break;

	case 'S':  //COMANDO DE GRADOS
		if(str[1]=='T' && str[2]=='E' && str[3]=='P' && str[4]=='C')
		{
			if( str[5]=='W' && str[6]==':')												//CW
			{
				if((str[7] > '/') && (str[7] < ':'))
				{
					if((str[8] > '/') && (str[8] < ':'))
					{
						if((str[9] > '/') && (str[9] < ':') && str[10]==13)
						{
							grados=((str[7]-'0')*100 + (str[8]-'0')*10 + (str[9]-'0'));
							steps=grados*12/45;
							FGRAD=1;
							direction=1; //***
							FDONE=1;
						}
						else
						{
							FDONE=0;
							SCIC2=0x2C;
						}
					}
					else
					{
						FDONE=0;
						SCIC2=0x2C;
					}
				}
				else
				{
					FDONE=0;
					SCIC2=0x2C;
				}
			}
			else if( str[5]=='C' && str[6]=='W'&& str[7]==':')					//CCW
			{
				if((str[8] > '/') && (str[8] < ':'))
				{
					if((str[9] > '/') && (str[9] < ':'))
					{
						if((str[10] > '/') && (str[10] < ':') && str[11]==13)
						{
							grados=((str[8]-'0')*100 + (str[9]-'0')*10 + (str[10]-'0'));
							steps=grados*12/45;
							FGRAD=1;
							direction=0;///*
							FDONE=1;
						}
						else
						{
							FDONE=0;
							SCIC2=0x2C;
						}
					}
					else
					{
						FDONE=0;
						SCIC2=0x2C;
					}
				}
				else
				{
					FDONE=0;
					SCIC2=0x2C;
				}
			}
			else
			{
				FDONE=0;
				SCIC2=0x2C;
			}
		}
		else
		{
			FDONE=0;
			SCIC2=0x2C;
		}

		break;

	case 'T': //COMANDO TEMPLIMIT
		if(str[1]=='E' && str[2]=='M' && str[3]=='P' && str[4]=='L' && str[5]=='I' && str[6]=='M' && str[7]=='I' && str[8]=='T' && str[9]==':' && str[13]=='.')
		{
			if((str[10] > '/') && (str[10] < ':'))
			{
				if((str[11] > '/') && (str[11] < ':'))
				{
					if((str[12] > '/') && (str[12] < ':'))
					{
						if((str[14] > '/') && (str[14] < ':') && str[15]==13)
						{
							TEMP_LIMIT=(str[10]-'0')*1000 + (str[11]-'0')*100 + (str[12]-'0')*10 + (str[14]-'0');
							FDONE=1;
						}
						else
						{
							FDONE=0;
							SCIC2=0x2C;
						}
					}
					else
					{
						FDONE=0;
						SCIC2=0x2C;
					}
				}
				else
				{
					FDONE=0;
					SCIC2=0x2C;
				}
			}
			else
			{
				FDONE=0;
				SCIC2=0x2C;
			}
		}
		else
		{
			FDONE=0;
			SCIC2=0x2C;
		}
		break;

	default:
		FDONE=0;
		SCIC2=0x2C;
	}
}

