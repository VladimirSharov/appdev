//for operating with  screen
#include <stdio.h>
#include "screen.h"
void barChart(int a[])
{
	int i,j;//x,y space counters
	for(i=0; i<80; i++)
	{
		 for(j=0; j<a[i]/3; j++)
	        {
			//setColors( (a[i]%8+30) , ((a[i]+3)%8+40) );
			printf("\033[%d;%dH",-j+35, i+1);
			#ifdef UNICODE
				printf("%s", "\u2590");
			#else
				printf("%c", ' ');
			#endif
        	}

	}
}
void clearScreen(void)
{
	printf("\033[2J");
	fflush(stdout);//activate esc.seq. immediat.
}

void setColors(short fg, short bg)
{
	printf("\033[%d;%d;1m", fg, bg);
	fflush(stdout);//immediat.
}

void resetColors(void)
{
	printf("\033[0m");
	fflush(stdout);
}
