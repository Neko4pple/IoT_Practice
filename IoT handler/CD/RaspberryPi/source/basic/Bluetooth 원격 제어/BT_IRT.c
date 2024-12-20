#include "bt_master.h"
#include <unistd.h>
#include <wiringPi.h>

#define PIN 6

int main()
{
        int client = init_server();
        int reed;

        char *recv_message;

        if(wiringPiSetup() == -1) return 1;

        pinMode(PIN,INPUT);

        while(1){

        recv_message = read_server(client);
        if ( recv_message == NULL ){
            printf("client disconnected\n");
            break;
        }

        if(strcmp(recv_message,"IRT") == 0){
                reed = digitalRead(PIN);

                if(reed == HIGH){
                        strcpy(recv_message, "IR Tracking - Detected!\n");
                }else if(reed == LOW){
                        strcpy(recv_message, "IR Tracking - Undetected..\n");
                }
        }

        write_server(client, recv_message);
    }
}
