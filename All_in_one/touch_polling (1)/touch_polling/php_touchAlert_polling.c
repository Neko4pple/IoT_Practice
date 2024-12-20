#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

#define PIN 6

int main(void) {
    if (wiringPiSetup() == -1) return 1;

    pinMode(PIN, INPUT);

    int currentState;
    int prevState = LOW;

	while (1) {
    currentState = digitalRead(PIN); // Read current state of the pin

    if (currentState == HIGH && prevState == LOW) {
        printf("1\n");
        exit(0);
    }
        prevState = currentState;
        delay(100); // Polling delay
    }

    return 0;
}