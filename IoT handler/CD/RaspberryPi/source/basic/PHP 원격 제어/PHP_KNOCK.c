#include <wiringPi.h>
#include <stdio.h>

#define PIN 11

int main(void){
	int i;

        if(wiringPiSetup() == -1) return 1;

        pinMode(PIN,INPUT);

	for( i=0; i<100000; i++ )
		if( digitalRead(PIN) == 0) break;

	if( i == 100000)
		printf("1");
	else
		printf("0");
}
