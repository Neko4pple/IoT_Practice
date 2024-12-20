#include "bt_master.h"
#include <unistd.h>
#include <wiringPi.h>

#define PIN 11

int main()
{
        int client = init_server();
        int knock, i;

        char *recv_message;

        if(wiringPiSetup() == -1) return 1;

        pinMode(PIN,INPUT);

        while(1){

        recv_message = read_server(client);
        if ( recv_message == NULL ){
            printf("client disconnected\n");
            break;
        }

        if(strcmp(recv_message,"KNOCK") == 0){

		for( i=0; i<100000; i++)
			if( digitalRead(PIN) == 0 ) break;

		if( i == 100000)
                	knock = HIGH;
		else
			knock = LOW;

                if(knock == LOW){
                        strcpy(recv_message, "Knock - Detected!\n");
                }else if(knock == HIGH){
                        strcpy(recv_message, "Knock - Undetected..\n");
                }
        }

        write_server(client, recv_message);
    }
}
