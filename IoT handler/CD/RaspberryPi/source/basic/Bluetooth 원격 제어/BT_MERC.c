#include "bt_master.h"
#include <unistd.h>
#include <wiringPi.h>

#define PIN 11

int main()
{
        int client = init_server();
        int merc;

        char *recv_message;

        if(wiringPiSetup() == -1) return 1;

        pinMode(PIN,INPUT);

        while(1){

        recv_message = read_server(client);
        if ( recv_message == NULL ){
            printf("client disconnected\n");
            break;
        }

        if(strcmp(recv_message,"MERC") == 0){
                merc = digitalRead(PIN);

                if(merc == HIGH){
                        strcpy(recv_message, "Mercury - Detected!\n");
                }else if(merc == LOW){
                        strcpy(recv_message, "Mercury - Undetected..\n");
                }
        }

        write_server(client, recv_message);
    }
}
