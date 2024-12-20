#include "bt_master.h"
#include <unistd.h>
#include <wiringPi.h>

#define MAX_TIME 100
#define PIN 25

int dht11_val[5]={0,0,0,0,0};

int main()
{
        int client = init_server();

	uint8_t lststate=HIGH;  
	uint8_t counter=0;  
  	uint8_t j=0,i;  
  	float farenheit;

        char *recv_message;

        if(wiringPiSetup() == -1) return 1;

	pinMode(PIN,INPUT);

        while(1){

        recv_message = read_server(client);
        if ( recv_message == NULL ){
            printf("client disconnected\n");
            break;
        }

        if(strcmp(recv_message,"DHT") == 0){
		pinMode(PIN,OUTPUT);  
  		digitalWrite(PIN,LOW);  
  		delay(18);  
  		digitalWrite(PIN,HIGH);  
  		delayMicroseconds(40);  
  		pinMode(PIN,INPUT);

		for(i=0;i<MAX_TIME;i++) {  
    			counter=0;  
    			while(digitalRead(PIN)==lststate){  
      				counter++;  
      				delayMicroseconds(1);  
      				if(counter==255)  
        				break;  
    			}  
    			lststate=digitalRead(PIN);  
    			if(counter==255)  
       				break;  
    			if((i>=4)&&(i%2==0)){  
				dht11_val[j/8]<<=1;  
				if(counter>16)  
					dht11_val[j/8]|=1;  
				j++;  
    			}  
  		}  
  		if((j>=40)&&(dht11_val[4]==((dht11_val[0]+dht11_val[1]+dht11_val[2]+dht11_val[3])& 0xFF))){  
    			farenheit=dht11_val[2]*9./5.+32;
			sprintf(recv_message, "Humi. = %d.%d %% Temp. = %d.%d *C (%.1f *F)\n", dht11_val[0],dht11_val[1],dht11_val[2],dht11_val[3],farenheit);
  		}else{
			sprintf(recv_message, "-1\n");
		}
        }

        write_server(client, recv_message);
    }
}
