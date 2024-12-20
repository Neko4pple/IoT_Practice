#include <wiringPi.h>
#include <stdio.h>

#define PIN 6 // Touch sensor
#define CONTROL_PIN 7 // LED

int touchflag = 0;
int flag;
void edge_rise(void);
void blinkLED(void);

int main(void) {
    if (wiringPiSetup() == -1) return 1;

    pinMode(PIN, INPUT);
    pinMode(CONTROL_PIN, OUTPUT);

    digitalWrite(CONTROL_PIN, LOW); //setting LED flat.
    flag = 0;

    // Setup ISR for rising edge
    if (wiringPiISR(PIN, INT_EDGE_RISING, &edge_rise) < 0) {
        printf("Unable to setup ISR: %s\n");
        fflush(0);
        return 1;
    }

    while (1) {
        delay(100); // Main loop does nothing, just sleeps
    }

    return 0;
}

void edge_rise(void) {
    // Print message and blink LED when edge rises
    printf("Pressed\n");
    fflush(0);
    blinkLED();
}

void blinkLED(void) {
    // Blink the LED in vice versa
    if (flag == 1) {
        digitalWrite(CONTROL_PIN, LOW); // LED OFF
        flag = 0;
    }
    else if (flag == 0) {
        digitalWrite(CONTROL_PIN, HIGH); // LED ON
        flag = 1;
    }
}
