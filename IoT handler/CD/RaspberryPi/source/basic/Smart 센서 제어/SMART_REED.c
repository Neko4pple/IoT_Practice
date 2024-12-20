#include <wiringPi.h>
#include <stdio.h>

#define PIN 9

int main(void){
	int reed, i;

        if(wiringPiSetup() == -1) return 1;
        pinMode(PIN,INPUT);

	for(i=0; i<20; i++){
        	reed = digitalRead(PIN);
		printf("%d\n",reed);
		delay(100);
	}
}
