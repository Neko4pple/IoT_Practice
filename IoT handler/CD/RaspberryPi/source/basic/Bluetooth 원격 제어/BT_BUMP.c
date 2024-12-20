#include "bt_master.h"
#include <unistd.h>
#include <wiringPi.h>

#define PIN 5

int main()
{
        int client = init_server();
        int bump;

        char *recv_message;

        if(wiringPiSetup() == -1) return 1;

        pinMode(PIN,INPUT);

        while(1){

        recv_message = read_server(client);
        if ( recv_message == NULL ){
            printf("client disconnected\n");
            break;
        }

        if(strcmp(recv_message,"BUMP") == 0){
                bump = digitalRead(PIN);

                if(bump == HIGH){
                        strcpy(recv_message, "BUMP - Detected!\n");
                }else if(bump == LOW){
                        strcpy(recv_message, "BUMP - Undetected..\n");
                }
        }

        write_server(client, recv_message);
    }
}
