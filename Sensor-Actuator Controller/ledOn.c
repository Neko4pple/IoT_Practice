#include <stdio.h>
#include <wiringPi.h>

#define PIN 7

int main(void) {
	in(wiringPiSetup() == -1) return -1;
	pinMod(PIN, OUTPUT);
	digitalWrite(PIN, HIGH);
	printf("1")
}