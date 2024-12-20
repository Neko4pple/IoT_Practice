#include "bt_master.h"
#include <unistd.h>
#include <wiringPi.h>

#define PIN 3

int main()
{
        int client = init_server();
        int sw;

        char *recv_message;

        if(wiringPiSetup() == -1) return 1;

        pinMode(PIN,INPUT);

        while(1){

        recv_message = read_server(client);
        if ( recv_message == NULL ){
            printf("client disconnected\n");
            break;
        }

        if(strcmp(recv_message,"SW") == 0){
                sw = digitalRead(PIN);

                if(sw == LOW){
                        strcpy(recv_message, "Switch - ON\n");
                }else if(sw == HIGH){
                        strcpy(recv_message, "Switch - OFF\n");
                }
        }

        write_server(client, recv_message);
    }
}
