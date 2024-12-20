#include "bt_master.h"
#include <unistd.h>
#include <wiringPi.h>

#define PIN 4

int main()
{
        int client = init_server();
        int pd;

        char *recv_message;

        if(wiringPiSetup() == -1) return 1;

        pinMode(PIN,INPUT);

        while(1){

        recv_message = read_server(client);
        if ( recv_message == NULL ){
            printf("client disconnected\n");
            break;
        }

        if(strcmp(recv_message,"PD") == 0){
                pd = digitalRead(PIN);

                if(pd == HIGH){
                        strcpy(recv_message, "Photo Diode - Detected!\n");
                }else if(pd == LOW){
                        strcpy(recv_message, "Photo Diode - Undetected..\n");
                }
        }

        write_server(client, recv_message);
    }
}
