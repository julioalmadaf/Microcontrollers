#include <hidef.h>
#include "derivative.h"
#include "lcd.h"
#include "retardos.h"
#include "idc.h"
/*#define DB7 PTBD_PTBD7
#define DB6 PTBD_PTBD6
#define DB5 PTBD_PTBD5
#define DB4 PTBD_PTBD4
#define E PTBD_PTBD3
#define RS PTBD_PTBD2
*/
static unsigned char modo4or8 = 1;

void LCD_Init(void)
{
	//Datos
	/*PTBDD_PTBDD7 = 1;
	PTBDD_PTBDD6 = 1;
	PTBDD_PTBDD5 = 1;
	PTBDD_PTBDD4 = 1;
	DB7 = 0;
	DB6 = 0;
	DB5 = 0;
	DB4 = 0;
	//Control
	PTBDD_PTBDD3 = 1;
	PTBDD_PTBDD2 = 1;
	E = 0; //Pin E
	RS = 0; //Pin RS*/
	delayMs(20);
	
	//Secuencia de inicializacion
	//LCD_Escribe(0b00110000,0);
	IIC_send_byte(0b00111000);
	IIC_send_byte(0b00111100);
	IIC_send_byte(0b00111000);
	delayMs(2);
	IIC_send_byte(0b00001000);
	IIC_send_byte(0b00001100);
	IIC_send_byte(0b00001000);
	delayMs(2);
	//*************
	delayMs(5);
	
	//LCD_Escribe(0b00110000,0);
	IIC_send_byte(0b00111000);
	IIC_send_byte(0b00111100);
	IIC_send_byte(0b00111000);
	delayMs(2);
	IIC_send_byte(0b00001000);
	IIC_send_byte(0b00001100);
	IIC_send_byte(0b00001000);
	delayMs(2);
	//**********************
	
	delayUs(200);
	
	//LCD_Escribe(0b00110000,0);
	IIC_send_byte(0b00111000);
	IIC_send_byte(0b00111100);
	IIC_send_byte(0b00111000);
	delayMs(2);
	IIC_send_byte(0b00001000);
	IIC_send_byte(0b00001100);
	IIC_send_byte(0b00001000);
	delayMs(2);
	//****************
	

	//Configuraciones principales
	LCD_4Bits();
	LCD_IncrementarCursor();
	LCD_CursorON();
	LCD_Clear();
}
//Borra toda la pantalla, memoria DDRAM y pone el cursor al comienzo de la linea 1
void LCD_Clear(void)
{
	//LCD_Escribe(0b00000001,0);
	IIC_send_byte(0b00001000);
	IIC_send_byte(0b00001100);
	IIC_send_byte(0b00001000);
	delayMs(2);
	
	IIC_send_byte(0b00011000);
	IIC_send_byte(0b00011100);
	IIC_send_byte(0b00011000);
	delayMs(2);
	
	
}

void LCD_ControlDisplay(void)
{
	//LCD_Escribe(0b00001000 | displayONOFF | cursorONOFF | blinkingONOFF,0);
	IIC_send_byte(0b00001000);//|displayONOFF | cursorONOFF | blinkingONOFF);
	IIC_send_byte(0b00001100);
	IIC_send_byte(0b00001000);
	delayMs(2);
	IIC_send_byte(0b11111000);//|displayONOFF | cursorONOFF | blinkingONOFF);
	IIC_send_byte(0b11111100);
	IIC_send_byte(0b11111000);
	delayMs(2);
}

//Interfaz de 4Bits
void LCD_4Bits(void)
{
	//LCD_Escribe(0b00101000,0);
	IIC_send_byte(0b00101000);
	IIC_send_byte(0b00101100);
	IIC_send_byte(0b00101000);
	delayMs(2);
	IIC_send_byte(0b10001000);
	IIC_send_byte(0b10001100);
	IIC_send_byte(0b10001000);
	delayMs(2);
	modo4or8 = 0;
}

void LCD_IncrementarCursor(void)
{
	//LCD_Escribe(0b00000110,0);
	IIC_send_byte(0b00001000);
	IIC_send_byte(0b00001100);
	IIC_send_byte(0b00001000);
	delayMs(2);
	IIC_send_byte(0b01101000);
	IIC_send_byte(0b01101100);
	IIC_send_byte(0b01101000);
	delayMs(2);	
}

//Cursor al principio de la linea 1
void LCD_Linea1(void)
{
	//LCD_Escribe(0b10000000,0); //Direccion 00h de la DDRAM
	IIC_send_byte(0b10001000);
	IIC_send_byte(0b10001100);
	IIC_send_byte(0b10001000);
	delayMs(2);	
	IIC_send_byte(0b00001000);
	IIC_send_byte(0b00001100);
	IIC_send_byte(0b00001000);
	delayMs(2);	
		
}

//Cursor al principio de la linea 2
void LCD_Linea2 (void)
{
	//LCD_Escribe(0b11000000,0); //Direccion 40h de la DDRAM
	IIC_send_byte(0b11001000);
	IIC_send_byte(0b11001100);
	IIC_send_byte(0b11001000);
	delayMs(2);	
	IIC_send_byte(0b00001000);
	IIC_send_byte(0b00001100);
	IIC_send_byte(0b00001000);
	delayMs(2);	
		
}

//Pantalla encendida y cursor encendido
void LCD_CursorON(void)
{
	//LCD_Escribe(0b00001110,0);
	IIC_send_byte(0b00001000);
	IIC_send_byte(0b00001100);
	IIC_send_byte(0b00001000);
	delayMs(2);	
	IIC_send_byte(0b11101000);
	IIC_send_byte(0b11101100);
	IIC_send_byte(0b11101000);
	delayMs(2);	
}
/*
//Escritura de datos
void LCD_Write(unsigned char dato)
{
	LCD_Escribe(dato,1);
}

static void LCD_Escribe(unsigned char dato, unsigned char tipo)
{
	if(tipo == 0 )
		RS = 0; //Comando
	else
		RS = 1; //Dato

	E = 0; //Garantizar que la linea E comienza en cero
	E = 1; //Flanco de subida para comenzar a escribir

	if (dato & 0x80)
		DB7 = 1;
	else
		DB7 = 0;
	
	if (dato & 0x40)
		DB6 = 1;
	else
		DB6 = 0;
	
	if (dato & 0x20)
		DB5 = 1;
	else
		DB5 = 0;
	
	if (dato & 0x10)
		DB4 = 1;
	else
		DB4 = 0;
	
	E=0; //Capturar dato en el LCD
	
	if(tipo == 0)
		delayMs(2); //Para un comando, el tiempo de delay correspondiente
	else
		delayUs(50);
	
	if (modo4or8 == 0) //Revisar si son datos de 4 o 8 bits
	{
		E=1; //Flanco de subida nuevamente para capturar la parte restante en modo 4 bits
		
		if (dato & 0x08)
			DB7 = 1;
		else
			DB7 = 0;
		
		if (dato & 0x04)
			DB6 = 1;
		else
			DB6 = 0;
		
		if (dato & 0x02)
			DB5 = 1;
		else
			DB5 = 0;
		
		if (dato & 0x01)
			DB4 = 1;
		else
			DB4 = 0;

		E=0; //Capturar dato
		
		if(tipo == 0)
			delayMs(2); //Para un comando, el tiempo de delay correspondiente
		else
			delayUs(50);
	}
}
*/
