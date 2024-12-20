#include "bt_master.h"
#include <unistd.h>
#include <wiringPi.h>

#define PIN_1A 27
#define PIN_1B 0
#define PIN_2A 1
#define PIN_2B 24

int main()
{
        int client = init_server();
	int i;

        char *recv_message;

        if(wiringPiSetup() == -1) return 1;

	pinMode(PIN_1A,OUTPUT);
        pinMode(PIN_1B,OUTPUT);
        pinMode(PIN_2A,OUTPUT);
        pinMode(PIN_2B,OUTPUT);

        while(1){

        recv_message = read_server(client);
        if ( recv_message == NULL ){
            printf("client disconnected\n");
            break;
        }

        if(strcmp(recv_message,"STMON") == 0){
                strcpy(recv_message, "Step Motor Activated!\n");

		for(i=0; i<500; i++){
                	digitalWrite(PIN_1A,HIGH);
                	digitalWrite(PIN_1B,LOW);
                	digitalWrite(PIN_2A,LOW);
                	digitalWrite(PIN_2B,LOW);
                	usleep(2000);
                	digitalWrite(PIN_1A,LOW);
                	digitalWrite(PIN_1B,HIGH);
                	digitalWrite(PIN_2A,LOW);
                	digitalWrite(PIN_2B,LOW);
                	usleep(2000);
                	digitalWrite(PIN_1A,LOW);
                	digitalWrite(PIN_1B,LOW);
                	digitalWrite(PIN_2A,HIGH);
                	digitalWrite(PIN_2B,LOW);
                	usleep(2000);
                	digitalWrite(PIN_1A,LOW);
                	digitalWrite(PIN_1B,LOW);
                	digitalWrite(PIN_2A,LOW);
        	        digitalWrite(PIN_2B,HIGH);
	                usleep(2000);
        	}
        }

        write_server(client, recv_message);
    }
}
