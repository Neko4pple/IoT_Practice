#include "bt_master.h"
#include <unistd.h>
#include <wiringPi.h>

#define TRIG 28
#define OUT 29

int main()
{
        int client = init_server();
        int dis;
	long startTime, travelTime;

        char *recv_message;

        if(wiringPiSetup() == -1) return 1;

	pinMode(TRIG,OUTPUT);
        pinMode(OUT,INPUT);

        while(1){

        recv_message = read_server(client);
        if ( recv_message == NULL ){
            printf("client disconnected\n");
            break;
        }

        if(strcmp(recv_message,"US") == 0){
		digitalWrite(TRIG, LOW);
		usleep(2);
		digitalWrite(TRIG, HIGH);
		usleep(20);
		digitalWrite(TRIG, LOW);

		while(digitalRead(OUT) == LOW);

		startTime = micros();

		while(digitalRead(OUT) == HIGH);

		travelTime = micros() - startTime;

		dis = travelTime / 58;
		sprintf(recv_message, "%d\n", dis);
        }

        write_server(client, recv_message);
    }
}
