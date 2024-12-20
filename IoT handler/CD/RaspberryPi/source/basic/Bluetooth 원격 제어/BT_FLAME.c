#include "bt_master.h"
#include <unistd.h>
#include <wiringPi.h>

#define PIN 16

int main()
{
        int client = init_server();
        int flame;

        char *recv_message;

        if(wiringPiSetup() == -1) return 1;

        pinMode(PIN,INPUT);

        while(1){

        recv_message = read_server(client);
        if ( recv_message == NULL ){
            printf("client disconnected\n");
            break;
        }

        if(strcmp(recv_message,"FLAME") == 0){
                flame = digitalRead(PIN);

                if(flame == HIGH){
                        strcpy(recv_message, "Flame - Detected!\n");
                }else if(flame == LOW){
                        strcpy(recv_message, "Flame - Undetected..\n");
                }
        }

        write_server(client, recv_message);
    }
}
