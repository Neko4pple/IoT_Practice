#include <wiringPi.h>
#include <stdio.h>

#define PIN 10

int main(void){
	int tilt, i;

        if(wiringPiSetup() == -1) return 1;
        pinMode(PIN,INPUT);

	for(i=0; i<20; i++){
        	tilt = digitalRead(PIN);
		printf("%d\n",tilt);
		delay(100);
	}
}
