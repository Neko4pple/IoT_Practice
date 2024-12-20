#include <wiringPi.h>
#include <stdio.h>

#define PIN 5

int main(void){
        int bump, i;

        if(wiringPiSetup() == -1) return 1;
        pinMode(PIN,INPUT);

        for(i=0; i<20; i++){
        	bump = digitalRead(PIN);
		printf("%d\n",bump);
		delay(100);
	}
}
