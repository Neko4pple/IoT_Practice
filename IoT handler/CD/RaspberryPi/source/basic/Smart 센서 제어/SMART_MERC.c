#include <wiringPi.h>
#include <stdio.h>

#define PIN 11

int main(void){
	int merc, i;

        if(wiringPiSetup() == -1) return 1;
        pinMode(PIN,INPUT);

        for(i=0; i<20; i++){
        	merc = digitalRead(PIN);
		printf("%d\n",merc);
		delay(100);
	}
}
