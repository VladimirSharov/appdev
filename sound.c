#include <stdio.h>
#include <math.h> //for sqrt
#include "sound.h"
#include "screen.h"

//this function takes samples:1sec, (1600 samples set)
//then calculate 80 pieces(look main structure) of RMS value(rout mean square)
//then put value in dB,for putting into barchart graph

int findPeaks(int d[])
{
	int i, c = 0;
	for(i=1;i<80;i++)
		if(d[i]>=75 && d[i-1]<75) c++;
	if(d[0]>=75) c++;
	return c;
}

void displayWAVDATA(short s[])
{
	double rms[80];//overall:16000samples (set)
			//bars:80, so for each bar 200samples
	int i, j;
	short *ptr = s;//pointer to the start of samples
	int db[80];
	for(i=0; i<80;i++)
	{
		double sum = 0;
		for(j=0; j<200; j++)
		{
			sum += (*ptr)*(*ptr);//accumulate the sum
			ptr++;
		}
		rms[i] = sqrt(sum/200);
		db[i]=20*log10(rms[i]);
#ifdef DEBUG
		printf("RMS[%d] = %f\n", i, rms[i]);
#endif
	//end of for
	}
#ifndef DEBUG
	barChart(db);
	int peaks = findPeaks(db);//get the number of peaks
	setColors(WHITE, bg(BLACK));
	printf("\033[1;61H");
	printf("Peaks: %d            \n",peaks);
#endif

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
#ifdef DEBUG
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
#else
	setColors(RED,bg(BLUE));
	printf("\033[1;1H");
	printf("test.wav            \n");
	setColors(YELLOW,bg(GREEN));
	printf("\033[1;21H");
	printf("samples rate=%d      \n",h.SampleRate);
	setColors(WHITE,bg(MAGENTA));
	printf("\033[1;41H");
	printf("duration=%.2f        \n",(float)h.Subchunk2Size/h.ByteRate);
	setColors(BLACK,bg(GREEN));
	resetColors();
#endif
}
void fillID(char *dst, const char *m)
{
	for(int i=0; i<4; i++)
		*dst++ = *m++;//ptdest bring value of m,then next dest and m
}
void testTone(int c,int f,float d)
{
	if(f<30 || f>16000)
	{
		printf("freq is out of range\n");
		return;
	}
	if(c<1 || c>2)
	{
	printf("num of channels is out of range\n");
		return;
	}
	if(d<1 || d>10)
	{
		printf("durat is out of range\n");
		return;
	}
	struct WAVHDR h; //to prepare wav header
	fillID(h.ChunkID,"RIFF");
	fillID(h.Format,"WAVE");
	fillID(h.Subchunk1ID,"fmt ");
	fillID(h.Subchunk2ID,"data");
	h.Subchunk1Size=16;
	h.AudioFormat=1;
	h.NumChannels=c;
	h.SampleRate=44100;
	h.BitsPerSample=16;
//h.=;
	h.ByteRate=h.SampleRate * c * h.BitsPerSample / 8;
	h.BlockAlign=c * h.BitsPerSample / 8;
	h.Subchunk2Size= d * h.SampleRate * h.BlockAlign;
	h.ChunkSize= h.Subchunk2Size + 36;
	//prepare sound data
	FILE *fp = fopen("testTone.wav","w");//f just name, changed fp-file pointer
	if(fp == NULL) //check if exist
	{
	printf("could not open\n");
	return;
	}	
	fwrite(&h, sizeof(h),1,fp); //write the header
	for(int i=0; i<d*h.SampleRate; i++)//up to amount of samples
	{
		short data = 32767.0*sin(2*PI*i*f/44100);
		fwrite(&data,sizeof(short), 1, fp);
		if(c==2)
		{
			short dR = 32767.0*sin(2*PI*i*f/2/44100);
			fwrite(&dR,sizeof(short), 1, fp);
		}
	}
	fclose(fp);
	printf("Test tone is generated\n");
}
