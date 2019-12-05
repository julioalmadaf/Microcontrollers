#ifndef _LCD_H_
#define _LCD_H_

extern unsigned char samples;

void LCD_Init(void);

void LCD_Linea1(void);

void LCD_Linea2 (void);

void LCD_Write(unsigned char dato);

static void LCD_Escribe(unsigned char dato, unsigned char comandoDato);

void CCWRPS(void);

#endif
