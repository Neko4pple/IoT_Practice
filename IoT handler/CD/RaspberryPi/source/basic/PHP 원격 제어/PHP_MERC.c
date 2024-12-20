#include <wiringPi.h>
#include <stdio.h>

#define PIN 11

int main(void){
        if(wiringPiSetup() == -1) return 1;

        pinMode(PIN,INPUT);

        printf("%d",digitalRead(PIN));
}
