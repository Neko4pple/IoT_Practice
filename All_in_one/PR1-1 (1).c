#include <wiringPi.h>
#include <stdio.h>

#define PIN 6 // Touch sensor
#define CONTROL_PIN 7 // LED

int main(void) {
    if (wiringPiSetup() == -1) return 1;

    pinMode(PIN, INPUT);
    pinMode(CONTROL_PIN, OUTPUT);
    digitalWrite(CONTROL_PIN, LOW); //setting flat LED.

    int prevState = LOW;
    int currentState;

    while (1) {
        currentState = digitalRead(PIN); // Read current state of the pin

        if (currentState == HIGH && prevState == LOW) {
            printf("Pressed\n");
            digitalWrite(CONTROL_PIN, HIGH); // Turn on LED
            delay(1000); // Wait for 1 second
            digitalWrite(CONTROL_PIN, LOW); // Turn off LED
        }

        prevState = currentState;
        delay(100); // Polling delay
    }

    return 0;
}
