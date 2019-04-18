//this is main.c
#include <stdio.h>
#include <signal.h>//to use commands like ctrl+c(fro break)
#include <time.h>
#include "screen.h" //for user difine header used double quotes
#include <stdlib.h>
#include "comm.h"
#include "sound.h" //every additional used in should be
int main(int argc, char **argv)
{
	if(argc == 2)
	{
		int ch;
		printf("how many channels? (1:mano; 2:stereo):");
		scanf("%d", &ch);
		float duration;
		printf("set length of test tone.(1-10sec):");
		scanf("%f", &duration);
		testTone(ch, atoi(argv[1]), duration);
		return 0;
	}
	int arr[80]; //for making bar chart
	srand(time(NULL));
	for(int i=0; i<80; i++)
		arr[i] = rand()%70 + 30;
/**/
	FILE *f;
	short sd[RATE];//fro all samles in 1 sec
	while(1)
	{
		int ret = system(CMD);
		if(ret == SIGINT) break;//command equal signal interrupt then
		f = fopen("test.wav","r");//open reda only
		clearScreen();
		//setColors(33, 45);
		setColors(WHITE,bg(CYAN));
		//printf("Printed from main.c\n");
		//barChart(arr);
		if(f == NULL) //not exist
		{
			printf("cannot open wav file\n");
			return 1; //error return:no such file
		}
		struct WAVHDR h;//instance of header
		fread(&h, sizeof(h), 1, f);//read wac header to h, 1 time
		displayWAVHDR(h);//show header information
		fread(&sd, sizeof(sd), 1, f);//read wac header to h, 1 time
        	displayWAVDATA(sd);//show header information
		fclose(f);//close opened file
		sendDATA(sd);
	}
	resetColors();
//	printf("test message\n");
//	getchar();
}
