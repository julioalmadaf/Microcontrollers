#ifndef LCD_H_
#define LCD_H_
extern unsigned char samples; //BANDERA PARA TOMAR MUESTRA DE TEMPERATURA DEL ADC EMULADO

void LCD_Init(void);
void LCD_Clear(void);
void LCD_ControlDisplay(void);
void LCD_4Bits(void);
void LCD_IncrementarCursor(void);
void LCD_Linea1(void);
void LCD_Linea2 (void);
void LCD_CursorON(void);
void LCD_Write(unsigned char character);
static void LCD_Escribe(unsigned char dato, unsigned char tipo_dato);
void CCWRPS(void);

#endif
