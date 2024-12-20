#include <wiringPi.h>
#include <stdio.h>

#define PIN 21

int main(void){
        int irt, i;

        if(wiringPiSetup() == -1) return 1;
        pinMode(PIN,INPUT);

        for(i=0; i<20; i++){
        	irt = digitalRead(PIN);
		printf("%d\n",irt);
		delay(100);
	}
}
