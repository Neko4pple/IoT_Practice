#include <wiringPi.h>
#include <stdio.h>

#define PIN 22

int main(void){
        if(wiringPiSetup() == -1) return 1;

        pinMode(PIN,OUTPUT);

        digitalWrite(PIN,HIGH);

	printf("1");
}
