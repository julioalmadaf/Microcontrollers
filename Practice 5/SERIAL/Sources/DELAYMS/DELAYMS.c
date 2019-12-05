#include <hidef.h>
#include "derivative.h"
#include "DELAYMS.h"

unsigned int p;
unsigned int o;
//DELAY DE MICRO SEGUNDOS
void Us(unsigned int delay)
{
	delay = (int)(delay / 4);
	if(p<delay)
	{
		p++;
	}
	else
	{
		p=0;
	}
}
//DELAY MILI SEGUNDOS
void Ms(unsigned int delay)
{
	delay = (int)(delay * 250);
		if(o<delay)
		{
			o++;
		}
		else
		{
			o=0;
		}
		
}
