#include <stdio.h>
#include <curl/curl.h>
#include <math.h>
#include "comm.h"
#include "sound.h"
//this function will calc 1 sec of sound samples into 8-pieces of 
//slow dB (ISO standard), this data is calc as 125ms of samples
//first part: calc, second part:for perform libcurl communic
void sendDATA(short s[])
{
	double rms[8], db[8];
	int i,j;

	for(i = 0; i < 8; i++)
	{
		double sum = 0.0;
		for(j = 0; j < 2000; j++)
		{
			sum += s[i*2000+j] * s[i*2000+j];
		}
		rms[i] = sqrt(sum/2000);
		db[i] = 20*log10(rms[i]);
	}
	//use libcurl funct to send data
	CURL *c;
	CURLcode res;
	char poststr[128];
	//post str should be in "dB=num1;num2; .. ;num8" format
	sprintf(poststr, "db=%.2f;%%20%.2f;%%20%.2f;%%20%.2f;%%20%.2f;%%20%.2f;%%20%.2f;%%20%.2f",
			db[0],db[1],db[2],db[3],db[4],db[5],db[6],db[7]);
#ifdef DEBUG
	printf("poststr =%s\n", poststr);
#endif
	curl_global_init(CURL_GLOBAL_ALL);
	c = curl_easy_init();
	if(c)
	{
		curl_easy_setopt(c, CURLOPT_URL,URL);
		curl_easy_setopt(c, CURLOPT_POSTFIELDS,poststr);
		res =curl_easy_perform(c);
		if(res != CURLE_OK) printf("communication failed!");

		curl_easy_cleanup(c);
	}
	curl_global_cleanup();
}
