#include <hidef.h>
#include "derivative.h"
#include "retardos.h"

unsigned int p;
unsigned int o;

void delayUs(unsigned int delay)
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

void delayMs(unsigned int delay)
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
