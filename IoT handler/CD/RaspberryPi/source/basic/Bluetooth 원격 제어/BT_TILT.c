#include "bt_master.h"
#include <unistd.h>
#include <wiringPi.h>

#define PIN 10

int main()
{
        int client = init_server();
        int tilt;

        char *recv_message;

        if(wiringPiSetup() == -1) return 1;

        pinMode(PIN,INPUT);

        while(1){

        recv_message = read_server(client);
        if ( recv_message == NULL ){
            printf("client disconnected\n");
            break;
        }

        if(strcmp(recv_message,"TILT") == 0){
                tilt = digitalRead(PIN);

                if(tilt == LOW){
                        strcpy(recv_message, "Tilt - Detected!\n");
                }else if(tilt == HIGH){
                        strcpy(recv_message, "Tilt - Undetected..\n");
                }
        }

        write_server(client, recv_message);
    }
}
