#include "bt_master.h"
#include <unistd.h>
#include <wiringPi.h>

#define PIN 21

int main()
{
        int client = init_server();
        int limit;

        char *recv_message;

        if(wiringPiSetup() == -1) return 1;

        pinMode(PIN,INPUT);

        while(1){

        recv_message = read_server(client);
        if ( recv_message == NULL ){
            printf("client disconnected\n");
            break;
        }

        if(strcmp(recv_message,"LIMIT") == 0){
                limit = digitalRead(PIN);

                if(limit == LOW){
                        strcpy(recv_message, "Limit Switch - Detected!\n");
                }else if(limit == HIGH){
                        strcpy(recv_message, "Limit Switch - Undetected..\n");
                }
        }

        write_server(client, recv_message);
    }
}
