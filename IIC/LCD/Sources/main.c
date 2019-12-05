#include <hidef.h>
#include "derivative.h"
#include "lcd.h"
#include "retardos.h"
#include "idc.h"

//***********************************************************
void main(void)
{
	SOPT1 = 0x52; //Desactivar watchdog
	init_IIC();
	start_communication(0x7E);
	LCD_Init();
	
	
	/*
	LCD_Init();
	LCD_Write('A');
	LCD_Write('V');
	LCD_Write('L');
	LCD_Linea2();
	LCD_PosicionLinea2(4);
	LCD_Write('B');
	LCD_Write('i');
	LCD_Write('t');
	LCD_Write('r');
	LCD_Write('i');
	LCD_ControlDisplay(_DisplayON, _CursorON, _CursorBlinkingON);
*/
	for (;;)
	{
		//asm nop;
	}
}
