#include <hidef.h>
#include "derivative.h"
#include "ADC.h"
#include "GPIO.h"
#include "MotorDriver.h"
#include "RXTX.h"
#include "Validation.h"
#include "LCD.h"
#include "DELAYMS.h"
#include "idc.h"

unsigned char samples=1; //BANDERA PARA TOMAR MUESTRA DE TEMPERATURA DEL ADC EMULADO

static unsigned char modo4Bits = 0;
unsigned char direccion=0x7E;
unsigned char t_comando;
unsigned char t_dato;
unsigned char tipo;
unsigned char capture_byte;
unsigned char MSB;
unsigned char LSB;
unsigned char enable;
unsigned char upper;
unsigned char lower;
unsigned char capture;

static void LCD_Escribe(unsigned char dato, unsigned char tipo_dato){
	t_comando = 0x08; //0000 10000
	t_dato= 0x09; //0000 1001
	//capture= 0b11111001 & MSB; //enable off
	MSB= dato & 0xF0;
	LSB = dato& 0x0F;
	IIC_send_byte(direccion);
	
	if(tipo_dato == 0)
		tipo = t_comando;
	else
	{
		tipo = t_dato;
	}
	
	IIC_send_byte(tipo); //Comando o dato

	enable= tipo | 0b00000100;  //mascara para subir bit enable
	IIC_send_byte(enable);

	upper=enable | MSB; //Mantiene enable y manda byte (parte alta)
	IIC_send_byte(upper);

	capture_byte= 0b11111001 & upper;
	IIC_send_byte(capture_byte); //Captura byte bajando bit de enable
	IIC_stop_condition();
	
	if(tipo_dato == 0)
		delayMs(2);
	else
		delayUs(50);

	if(modo4Bits == 1)
	{
		IIC_send_byte(direccion);
		IIC_send_byte(enable); //Mandar enable con el tipo de dato (producto de la mascara aplicada anteriormente

		lower = enable | (dato << 4); //Mandar dato parte baja
		IIC_send_byte(lower);
		
		capture_byte= 0b11111001 & lower; //Capturar byte bajando enable
		IIC_send_byte(capture_byte);

		IIC_stop_condition();
		if(tipo_dato == 0)
			delayMs(2);
		else
			delayUs(50);
	}
}

void LCD_Init(void)
{
	//secuencia de inicializacion
	delayMs(20);
	LCD_Escribe(0b00110000,0);
	delayMs(5);
	LCD_Escribe(0b00110000,0);
	delayUs(200);
	LCD_Escribe(0b00110000,0);
	
	LCD_4Bits();
	LCD_IncrementarCursor();
	LCD_CursorON();
	LCD_Clear();
	LCD_Linea1();
}

//Borra toda la pantalla, memoria DDRAM y pone el cursor al comienzo de la linea 1
void LCD_Clear(void)
{
	LCD_Escribe(0b00000001,0);
}

void LCD_ControlDisplay(void)
{
	LCD_Escribe(0b00001111,0);
}

//Interfaz de 4Bits
void LCD_4Bits(void)
{
	LCD_Escribe(0b00101000,0);
	modo4Bits = 1;
}

void LCD_IncrementarCursor(void)
{
	LCD_Escribe(0b00000110,0);
}

//Cursor al principio de la linea 1
void LCD_Linea1(void)
{
	LCD_Escribe(0b10000000,0); //Direccion 00h de la DDRAM
}

//Cursor al principio de la linea 2
void LCD_Linea2 (void)
{
	LCD_Escribe(0b11000000,0); //Direccion 40h de la DDRAM
}

//Pantalla encendida y cursor encendido
void LCD_CursorON(void)
{
	LCD_Escribe(0b00001110,0);	
}

void LCD_Write(unsigned char character)
{
	LCD_Escribe(character,1);
}

void CCWRPS(void) //FUNCION QUE IMPRIME EN LA LCD LO QUE SE NOS PIDIO EN LA PRACTICA 5
{
	LCD_Linea1();
	
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

	LCD_Linea2();
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
