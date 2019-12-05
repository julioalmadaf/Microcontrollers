#ifndef _GPIO_H_
#define _GPIO_H_

extern unsigned char FMTIM;
extern unsigned char FLED;
extern unsigned int CounterLed;

void initGPIO (void);

void ControlLED(void);

#endif
