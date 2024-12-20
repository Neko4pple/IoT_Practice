#include "bt_master.h"
#include <unistd.h>
#include <wiringPi.h>

#define PIN 26

int main()
{
        int client = init_server();

        char *recv_message;

        if(wiringPiSetup() == -1) return 1;

        pinMode(PIN,OUTPUT);

        while(1){

        recv_message = read_server(client);
        if ( recv_message == NULL ){
            printf("client disconnected\n");
            break;
        }

        if(strcmp(recv_message,"DCMON") == 0){
                digitalWrite(PIN,HIGH);
                strcpy(recv_message, "DC Motor ON!\n");
        }else if(strcmp(recv_message, "DCMOFF") == 0){
                digitalWrite(PIN,LOW);
                strcpy(recv_message, "DC Motor OFF!\n");
        }

        write_server(client, recv_message);
    }
}
