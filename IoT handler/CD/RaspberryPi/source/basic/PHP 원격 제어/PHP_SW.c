#include <wiringPi.h>
#include <stdio.h>

#define PIN 3

int main(void){
        if(wiringPiSetup() == -1) return 1;

        pinMode(PIN,INPUT);

        printf("%d",digitalRead(PIN));
}
