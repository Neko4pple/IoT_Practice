#include "bt_master.h"
#include <unistd.h>
#include <wiringPi.h>

#define R 27
#define G 0
#define B 1

int main()
{
        int client = init_server();

        char *recv_message;

        if(wiringPiSetup() == -1) return 1;

        pinMode(R,OUTPUT);
	pinMode(G,OUTPUT);
	pinMode(B,OUTPUT);

        while(1){

        recv_message = read_server(client);
        if ( recv_message == NULL ){
            printf("client disconnected\n");
            break;
        }

        if(strcmp(recv_message,"REDON") == 0){
                digitalWrite(R,HIGH);
                strcpy(recv_message, "Red LED ON!\n");
        }else if(strcmp(recv_message, "REDOFF") == 0){
                digitalWrite(R,LOW);
                strcpy(recv_message, "Red LED OFF!\n");
        }else if(strcmp(recv_message,"GREENON") == 0){
                digitalWrite(G,HIGH);
                strcpy(recv_message, "Green LED ON!\n");
        }else if(strcmp(recv_message, "GREENOFF") == 0){
                digitalWrite(G,LOW);
                strcpy(recv_message, "Green LED OFF!\n");
        }else if(strcmp(recv_message,"BLUEON") == 0){
                digitalWrite(B,HIGH);
                strcpy(recv_message, "Blue LED ON!\n");
        }else if(strcmp(recv_message, "BLUEOFF") == 0){
                digitalWrite(B,LOW);
                strcpy(recv_message, "Blue LED OFF!\n");
        }

        write_server(client, recv_message);
    }
}
