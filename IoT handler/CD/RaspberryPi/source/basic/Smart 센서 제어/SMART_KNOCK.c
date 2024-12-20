#include <wiringPi.h>
#include <stdio.h>

#define PIN 11

int main(void){
        int knock, i, j;

        if(wiringPiSetup() == -1) return 1;
        pinMode(PIN,INPUT);

        for(i=0; i<20; i++){
		for (j=0; j<100000; j++)
			if(digitalRead(PIN)==0) break;

		if(j==100000)
                	knock = 1;		else
			knock = 0;

                printf("%d\n",knock);
                delay(100);
        }
}
