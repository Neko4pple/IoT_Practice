#include <stdio.h>
#include <wiringPi.h>

#define TRIG 28
#define OUT 29

#define PIN_1A 27
#define PIN_1B 0
#define PIN_2A 1
#define PIN_2B 24

// Function to control the step motor
void stepD() {
    digitalWrite(PIN_1A, HIGH);
    digitalWrite(PIN_1B, LOW);
    digitalWrite(PIN_2A, LOW);
    digitalWrite(PIN_2B, LOW);
    delay(1000);
    digitalWrite(PIN_1A, LOW);
    digitalWrite(PIN_1B, HIGH);
    digitalWrite(PIN_2A, LOW);
    digitalWrite(PIN_2B, LOW);
    delay(1000);
    digitalWrite(PIN_1A, LOW);
    digitalWrite(PIN_1B, LOW);
    digitalWrite(PIN_2A, HIGH);
    digitalWrite(PIN_2B, LOW);
    delay(1000);
    digitalWrite(PIN_1A, LOW);
    digitalWrite(PIN_1B, LOW);
    digitalWrite(PIN_2A, LOW);
    digitalWrite(PIN_2B, HIGH);
    delay(1000);
}

int main(void) {
    int dis = 0;
    long start, travel;
    int motorRunning = 1;

    if (wiringPiSetup() == -1) return 1;

    pinMode(TRIG, OUTPUT);
    pinMode(OUT, INPUT);

    pinMode(PIN_1A, OUTPUT);
    pinMode(PIN_1B, OUTPUT);
    pinMode(PIN_2A, OUTPUT);
    pinMode(PIN_2B, OUTPUT);

    while (1) {
        // Trigger the ultrasonic sensor
        digitalWrite(TRIG, 0);
        usleep(2);
        digitalWrite(TRIG, 1);
        usleep(20);
        digitalWrite(TRIG, 0);

        while (digitalRead(OUT) == 0);
        start = micros();

        while (digitalRead(OUT) == 1);
        travel = micros() - start;

        dis = travel / 58;

        // Check distance and control the motor accordingly
        if (dis < 30) {
            if (motorRunning) {
                printf("%dcm < 30cm, Step Motor Stopped.\n", dis);
                motorRunning = 0;
            }
        } else {
            if (!motorRunning) {
                printf("%dcm >= 30cm, Step Motor Resumed.\n", dis);
                motorRunning = 1;
            }
        }

        // Run the motor if it is supposed to be running
        if (motorRunning) {
            stepD();
        } else {
            // Ensure motor stops
            digitalWrite(PIN_1A, LOW);
            digitalWrite(PIN_1B, LOW);
            digitalWrite(PIN_2A, LOW);
            digitalWrite(PIN_2B, LOW);
        }

        delay(100); // adjust for sensor read frequency
    }
    return 0;
}

