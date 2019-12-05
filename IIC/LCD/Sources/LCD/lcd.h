#ifndef LCD_H_
#define LCD_H_

#define _Incrementos 0b00000010
#define _Decrementos 0b00000000
#define _DisplayON 0b00000100
#define _DisplayOFF 0b00000000
#define _CursorON 0b00000010
#define _CursorOFF 0b00000000
#define _CursorBlinkingON 0b00000001
#define _CursorBlinkingOFF 0b00000000
#define _DisplayShift 0b00001000
#define _CursorMove 0b00000000
#define _ShiftRigth 0b00000100
#define _ShiftLeft 0b00000000
#define _8Bits 0b00010000
#define _4Bits 0b00000000
#define _2Lines 0b00001000
#define _1Line 0b00000000
#define _5x10Dots 0b00000100
#define _5x8Dots 0b00000000

void LCD_Init(void);

void LCD_Clear(void);
//void LCD_Home(void);
//void LCD_EntryMode(unsigned char incrementDecrement);
void LCD_ControlDisplay(void);
//void LCD_CursorDisplayShift(unsigned char cursorDisplayShift, unsigned char direction);
//void LCD_FunctionSet(unsigned char dataLength, unsigned char displayLines, unsigned char characterFont);
//void LCD_SetDDRAM(unsigned char posicion, unsigned char lineNumber);

void LCD_4Bits(void);
void LCD_IncrementarCursor(void);
void LCD_Linea1(void);
void LCD_Linea2 (void);
//void LCD_PosicionLinea1(unsigned char posicion);
//void LCD_PosicionLinea2(unsigned char posicion);
//void LCD_OFF(void);
void LCD_CursorON(void);
//void LCD_CursorOFF(void);
//void LCD_2Lineas5x7(void);

//void LCD_Write(unsigned char dato);

//static void LCD_Escribe(unsigned char dato, unsigned char comandoDato);

#endif
