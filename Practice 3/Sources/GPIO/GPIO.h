#ifndef _GPIO_H_
#define _GPIO_H_

extern unsigned char FMTIM;

void initGPIO (void);

void WriteMotor( unsigned char i);

unsigned char SwitchGPIO(void);

#endif
