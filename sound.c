#include <stdio.h>
#include <math.h> //for sqrt
#include "sound.h"
//this function takes samples:1sec, (1600 samples set)
//then calculate 80 pieces(look main structure) of RMS value(rout mean square)
//then put value in dB,for putting into barchart graph
void displayWAVDATA(short s[])
{
	double rms[80];//overall:16000samples (set)
			//bars:80, so for each bar 200samples
	int i, j;
	short *ptr = s;//pointer to the start of samples

	for(i=0; i<80;i++)
	{
		double sum = 0;
		for(j=0; j<200; j++)
		{
			sum += (*ptr)*(*ptr);//accumulate the sum
			ptr++;
		}
		rms[i] = sqrt(sum/200);
		printf("RMS[%d] = %f\n", i, rms[i]);
	}
}

void showID( char *name, char *value)
{
	printf("%s: ", name);
	for(int i=0; i<4; i++)
		printf("%c", value[i]);
	puts(""); //== \n
}
//function definition
void displayWAVHDR(struct WAVHDR h)
{
int a = h.ChunkSize;//for checking plan:text org->int 
	showID("Chunk ID", h.ChunkID);
	printf("Chunk size: %d\n", a);
	showID("Format",h.Format);
	showID("Subchunk1ID",h.Subchunk1ID);
	printf("Subchunk1ID size: %d\n", h.Subchunk1Size);
	printf("AudioFormat == wav: %d\n", h.AudioFormat);
	printf("Number of Channels: %d\n", h.NumChannels);
	printf("Samples Rate: %d\n", h.SampleRate);
	printf("Byte Rate: %d\n", h.ByteRate);
	printf("Block Align: %d\n", h.BlockAlign);
	printf("Bits Per/Sample: %d\n", h.BitsPerSample);
	showID("Subchunk 2 ID",h.Subchunk2ID);
	printf("Subchunk 2ID size : %d\n", h.Subchunk2Size);


}
