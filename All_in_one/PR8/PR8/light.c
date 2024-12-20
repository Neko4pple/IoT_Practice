#include <stdio.h>
#include <wiringPi.h>

#define PIN 7

int main(void) {
	if (wiringPiSetup() == -1) return -1;
	pinMode(PIN, INPUT);
	printf("%d", digitalRead(PIN));
}