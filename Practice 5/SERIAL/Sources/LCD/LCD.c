#include <hidef.h>
#include "derivative.h"
#include "ADC.h"
#include "GPIO.h"
#include "MotorDriver.h"
#include "RXTX.h"
#include "Validation.h"
#include "LCD.h"
#include "DELAYMS.h"

#define DB7 PTAD_PTAD3 
#define DB6 PTAD_PTAD2
#define DB5 PTAD_PTAD1
#define DB4 PTAD_PTAD0
#define E PTBD_PTBD3
#define RS PTBD_PTBD2

static unsigned char modo4or8 = 1; //ES PARA METER SOLO 4 O 8 BITS
unsigned char samples=1; //BANDERA PARA TOMAR MUESTRA DE TEMPERATURA DEL ADC EMULADO

void LCD_Init(void) //INICIALIZACION DEL LCD
{
	DB7 = 0;
	DB6 = 0;
	DB5 = 0;
	DB4 = 0;
	E = 0; 
	RS = 0; 
	Ms(20);
	LCD_Escribe(0x30,0);
	Ms(5);
	LCD_Escribe(0x30,0);
	Us(200);
	LCD_Escribe(0x30,0);
	LCD_Escribe(0x28,0);
	modo4or8 = 0; 				
	LCD_Escribe(0x06,0);
	LCD_Escribe(0x01,0);
}

void Linea1(void) //PARA QUE ESCRIBA EN LA PRIMER LINEA
{
	LCD_Escribe(0x80,0); 
}

void Linea2 (void) //PARA QUE ESCRIBA EN LA SEGUNDA LINEA
{
	LCD_Escribe(0xC0,0);
}

void LCD_Write(unsigned char dato) //FUNCION QUE SIMPLIFICA LA ESCRITURA DE DATOS
{
	LCD_Escribe(dato,1);
}

static void LCD_Escribe(unsigned char dato, unsigned char tipo) //FUNCION PARA ESCRIBIR COMANDOS Y DATOS
{

	if(tipo == 0 )	RS = 0; 
	else 			RS = 1; 

	E = 0; 

	E = 1; 

	if (dato & 0x80)	DB7 = 1;
	else 				DB7 = 0;

	if (dato & 0x40)	DB6 = 1;
	else				DB6 = 0;

	if (dato & 0x20)	DB5 = 1;
	else				DB5 = 0;

	if (dato & 0x10)	DB4 = 1;
	else				DB4 = 0;

	E=0; 

	if(tipo == 0)		Ms(2); 
	else				Us(50);

	if (modo4or8 == 0) 
	{
		E=1; 
		if (dato & 0x08)DB7 = 1;
		else			DB7 = 0;

		if (dato & 0x04)DB6 = 1;
		else			DB6 = 0;

		if (dato & 0x02)DB5 = 1;
		else			DB5 = 0;

		if (dato & 0x01)DB4 = 1;
		else			DB4 = 0;

		E=0; 

		if(tipo == 0)	Ms(2); 
		else			Us(50);
	}
}

void CCWRPS(void) //FUNCION QUE IMPRIME EN LA LCD LO QUE SE NOS PIDIO EN LA PRACTICA 5
{
	Linea1();
	
	if(direction==1) //CHECA LAS DIRECCION DEL MOTOR
	{
		LCD_Write('C');
		LCD_Write('C');
		LCD_Write('W');
	}
	else
	{
		LCD_Write('C');
		LCD_Write('W');
		LCD_Write(' ');
	}
	LCD_Write(' ');
	LCD_Write('-');
	LCD_Write(' ');
	LCD_Write(temperature[0]); //IMPRIME TEMPERATURA
	LCD_Write(temperature[1]);
	LCD_Write(temperature[2]);
	LCD_Write(temperature[3]);
	LCD_Write(temperature[4]);
	LCD_Write('°');
	LCD_Write('C');

	Linea2();
	if(frps==0)					//ENTRA EN ESTA FLAG SOLO CUANDO SE MANDA EL COMANDO DE RPS
	{
		LCD_Write(rps1);
		LCD_Write(rps2);
		LCD_Write('.');
		LCD_Write(rps3);
	}
	else
	{
		if(FMOFF | (FOVTEMP==1)) //IMPRIME 00.0 CUANDO SE APAGA EL MOTOR O SE PASA DE TEMPERATURA
		{
			LCD_Write('0');
			LCD_Write('0');
			LCD_Write('.');
			LCD_Write('0');
		}
		else 					// VELOCIDAD CON LA QUE INICIA 
		{
			LCD_Write('5');
			LCD_Write('0');
			LCD_Write('.');
			LCD_Write('0');
		}

	}
	LCD_Write(' ');	
	LCD_Write('R');
	LCD_Write('P');
	LCD_Write('S');	
}
