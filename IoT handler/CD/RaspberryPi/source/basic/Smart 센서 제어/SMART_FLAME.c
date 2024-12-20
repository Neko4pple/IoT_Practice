#include <wiringPi.h>
#include <stdio.h>

#define PIN 16

int main(void){
	int flame, i;

        if(wiringPiSetup() == -1) return 1;
        pinMode(PIN,INPUT);

	for(i=0; i<20; i++){
        	flame = digitalRead(PIN);
		printf("%d\n",flame);
		delay(100);
	}
}
