#include "bt_master.h"
#include <unistd.h>
#include <wiringPi.h>

#define PIN 6

int main()
{
        int client = init_server();
        int touch;

        char *recv_message;

        if(wiringPiSetup() == -1) return 1;

        pinMode(PIN,INPUT);

        while(1){

        recv_message = read_server(client);
        if ( recv_message == NULL ){
            printf("client disconnected\n");
            break;
        }

        if(strcmp(recv_message,"TOUCH") == 0){
                touch = digitalRead(PIN);

                if(touch == HIGH){
                        strcpy(recv_message, "Touch - Detected!\n");
                }else if(touch == LOW){
                        strcpy(recv_message, "Touch - Undetected..\n");
                }
        }

        write_server(client, recv_message);
    }
}
