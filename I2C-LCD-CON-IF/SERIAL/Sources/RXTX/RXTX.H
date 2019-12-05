#ifndef _RXTX_H_
#define _RXTX_H_
#define MaxLength 15 //el string mas grande que utilizamos es de 15 caracteres


extern unsigned char CounterTemp;
extern unsigned char F5SEGS;
extern unsigned char FOVTEMP;
extern unsigned char FOVREADY;
extern unsigned int temp;
extern unsigned int TEMP_LIMIT;
extern unsigned char str[MaxLength];
extern unsigned char temperature[7];

void initRXTX(void);

void TEMP5(unsigned char temp);

#endif
