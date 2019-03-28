//this is main.c
#include <stdio.h>
#include <time.h>
#include "screen.h" //for user difine header used double quotes
#include <stdlib.h>
int main()
{
	int arr[80]; //for making bar chart
	srand(time(NULL));
	for(int i=0; i<80; i++)
		arr[i] = rand()%70 + 30;
	clearScreen();
	//setColors(33, 45);
	setColors(WHITE,bg(CYAN));
	//printf("Printed from main.c\n");
	barChart(arr);
	resetColors();
	printf("test message\n");
	getchar();
}
