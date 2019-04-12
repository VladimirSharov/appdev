//constant def
//#define DEBUG
#define PI 3.1415926
#define RATE 16000 //samp per sec
#define CMD "arecord -r16000 -c1 -f S16_LE -d1 -q test.wav"//16000rate channel*1 duratation 1sec 
//data struct
struct WAVHDR
{
	char ChunkID[4];//RIFF-fomat,4 symbols
	int ChunkSize;//4 byte number
	char Format[4];//it "WAVE"
	
	char Subchunk1ID[4];//fmt
	int Subchunk1Size;//PCM = 16
	short AudioFormat;//shd = 1
	short NumChannels;//shd = 1
	int SampleRate;// 16000
	int ByteRate;//16000*NCha*BPS/8
	short BlockAlign;//NCh*BPR/8
	short BitsPerSample;//

	char Subchunk2ID[4];//data
	int Subchunk2Size;
};
//function declar
void displayWAVHDR(struct WAVHDR h);
void displayWAVDATA(short []);
void testTone(int, int, float);
