#include <wiringPi.h>

#define R 27
#define G 0
#define B 1

int main(void){
        if(wiringPiSetup() == -1) return 1;
        pinMode(R,OUTPUT);
        pinMode(G,OUTPUT);
        pinMode(B,OUTPUT);

        digitalWrite(R,HIGH);
	delay(1000);
	digitalWrite(R,LOW);
	digitalWrite(G,HIGH);
	delay(1000);
	digitalWrite(G,LOW);
	digitalWrite(B,HIGH);
	delay(1000);
	digitalWrite(B,LOW);
}
