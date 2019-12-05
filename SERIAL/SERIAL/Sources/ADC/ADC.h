#ifndef _ADC_H_
#define _ADC_H_
#define ADC_ON		ADCSC1= 0b011000000
#define ADC_OFF		ADCSC1= 0b00011111

extern unsigned char FADC;

unsigned int ADC_samples(void);

#endif
