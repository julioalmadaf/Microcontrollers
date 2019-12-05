#ifndef _GPIO_H_
#define _GPIO_H_
#define LED_ON			PTAD_PTAD1=1
#define LED_OFF			PTAD_PTAD1=0

//#define LED1_ON			PTAD_PTAD1=1 //

extern unsigned char FMTIM;
extern unsigned char FLED;
extern unsigned int CounterLed;


void initGPIO (void);

void ControlLED(void);

unsigned char SwitchGPIO(void);

#endif
