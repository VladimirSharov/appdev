//constant def
#define RATE 16000 //samp per sec
//data struct
struct WAVEHDR
{
	char ChunkID[4];//RIFF-fomat,4 symbols
	int ChunkSize;//4 byte number
	char Format[4];//it "WAVE"
	
	char Subchunk1D[4];//fmt
	int Subchunk1Size//PCM = 16
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
