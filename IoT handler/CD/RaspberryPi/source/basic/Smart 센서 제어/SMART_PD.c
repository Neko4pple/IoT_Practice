#include <wiringPi.h>
#include <stdio.h>

#define PIN 4

int main(void){
        int pd, i;

        if(wiringPiSetup() == -1) return 1;
        pinMode(PIN,INPUT);

        for(i=0; i<20; i++){
        	pd = digitalRead(PIN);
		printf("%d\n",pd);
		delay(100);
	}
}
