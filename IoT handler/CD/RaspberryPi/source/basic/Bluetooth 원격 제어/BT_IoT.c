#include "bt_master.h"
#include <wiringPi.h>
#include <unistd.h>
#include <math.h>

int dht();
int us(void);
int adc(int pin);
int dust(int pin, int out);
void stmactive(int pin_1A, int pin_1B, int pin_2A, int pin_2B);

int main(){
	int client = init_server();
	if(wiringPiSetup() == -1) return 1;
	char *recv_message;

    while(1)
    {
	recv_message = read_server(client);
        if ( recv_message == NULL ){
            printf("client disconnected\n");
            break;
        }

	if(strcmp(recv_message, "LEDON") == 0){
		pinMode(7,OUTPUT);
		digitalWrite(7,1);
		strcpy(recv_message,"LED ON\r");

	}else if(strcmp(recv_message, "LEDOFF") == 0){
                pinMode(7,OUTPUT);
                digitalWrite(7,0);
		strcpy(recv_message,"LED OFF\r");

	}else if(strcmp(recv_message, "DCMON") == 0){
                pinMode(26,OUTPUT);
                digitalWrite(26,1);
		strcpy(recv_message,"DC Motor ON\r");

	}else if(strcmp(recv_message, "DCMOFF") == 0){
                pinMode(26,OUTPUT);
                digitalWrite(26,0);
		strcpy(recv_message,"DC Motor OFF\r");

        }else if(strcmp(recv_message, "LASERON") == 0){
                pinMode(22,OUTPUT);
                digitalWrite(22,1);
                strcpy(recv_message,"Laser ON\r");

        }else if(strcmp(recv_message, "LASEROFF") == 0){
                pinMode(22,OUTPUT);
                digitalWrite(22,0);
                strcpy(recv_message,"Laser OFF\r");

        }else if(strcmp(recv_message, "BUZZERON") == 0){
                pinMode(15,OUTPUT);
                digitalWrite(15,1);
                strcpy(recv_message,"Buzzer ON\r");

        }else if(strcmp(recv_message, "BUZZEROFF") == 0){
                pinMode(15,OUTPUT);
                digitalWrite(15,0);
                strcpy(recv_message,"Buzzer OFF\r");

	}else if(strcmp(recv_message, "REDON") == 0){
                pinMode(27,OUTPUT);
                digitalWrite(27,1);
                strcpy(recv_message,"Red ON\r");
        }else if(strcmp(recv_message, "REDOFF") == 0){
                pinMode(27,OUTPUT);
                digitalWrite(27,0);
                strcpy(recv_message,"Red OFF\r");
        }else if(strcmp(recv_message, "GREENON") == 0){
                pinMode(0,OUTPUT);
                digitalWrite(0,1);
                strcpy(recv_message,"Green ON\r");
        }else if(strcmp(recv_message, "GREENOFF") == 0){
                pinMode(0,OUTPUT);
                digitalWrite(0,0);
                strcpy(recv_message,"Green OFF\r");
        }else if(strcmp(recv_message, "BLUEON") == 0){
                pinMode(1,OUTPUT);
                digitalWrite(1,1);
                strcpy(recv_message,"Blue ON\r");
        }else if(strcmp(recv_message, "BLUEOFF") == 0){
                pinMode(1,OUTPUT);
                digitalWrite(1,0);
                strcpy(recv_message,"Blue OFF\r");
        }else if(strcmp(recv_message, "RELAYON") == 0){
                pinMode(16,OUTPUT);
                digitalWrite(16,1);
                strcpy(recv_message,"Relay ON\r");
        }else if(strcmp(recv_message, "RELAYOFF") == 0){
                pinMode(16,OUTPUT);
                digitalWrite(16,0);
                strcpy(recv_message,"Relay OFF\r");
        }else if(strcmp(recv_message, "STMON") == 0){
				stmactive(27,0,1,24);
				strcpy(recv_message,"STEP Motor ACTIVATED\r");
	}else if(strcmp(recv_message,"PIR") == 0){
		pinMode(2,INPUT);
		if(digitalRead(2))
			strcpy(recv_message,"Y\r");
		else
			strcpy(recv_message,"N\r");

	}else if(strcmp(recv_message,"SW") == 0){
                pinMode(3,INPUT);
                if(digitalRead(3)==0)
                        strcpy(recv_message,"Y\r");
                else
                        strcpy(recv_message,"N\r");

        }else if(strcmp(recv_message,"TOUCH") == 0){
                pinMode(6,INPUT);
                if(digitalRead(6))
                        strcpy(recv_message,"Y\r");
                else
                        strcpy(recv_message,"N\r");

        }else if(strcmp(recv_message,"BUMP") == 0){
                pinMode(5,INPUT);
                if(digitalRead(5))
                        strcpy(recv_message,"Y\r");
                else
                        strcpy(recv_message,"N\r");

        }else if(strcmp(recv_message,"PD") == 0){
                pinMode(4,INPUT);
                if(digitalRead(4))
                        strcpy(recv_message,"Y\r");
                else
                        strcpy(recv_message,"N\r");

        }else if(strcmp(recv_message,"MERC") == 0){
                pinMode(11,INPUT);
                if(digitalRead(11))
                        strcpy(recv_message,"Y\r");
                else
                        strcpy(recv_message,"N\r");

        }else if(strcmp(recv_message,"TILT") == 0){
                pinMode(10,INPUT);
                if(digitalRead(10)==0)
                        strcpy(recv_message,"Y\r");
                else
                        strcpy(recv_message,"N\r");

        }else if(strcmp(recv_message,"FLAME") == 0){
                pinMode(16,INPUT);
                if(digitalRead(16))
                        strcpy(recv_message,"Y\r");
                else
                        strcpy(recv_message,"N\r");

        }else if(strcmp(recv_message,"REED") == 0){
                pinMode(9,INPUT);
                if(digitalRead(9))
                        strcpy(recv_message,"Y\r");
                else
                        strcpy(recv_message,"N\r");

        }else if(strcmp(recv_message,"IRT") == 0){
                pinMode(6,INPUT);
                if(digitalRead(6))
                        strcpy(recv_message,"Y\r");
                else
                        strcpy(recv_message,"N\r");
        }else if(strcmp(recv_message,"LIMIT") == 0){
                pinMode(21,INPUT);
                if(digitalRead(21)==0)
                        strcpy(recv_message,"Y\r");
                else
                        strcpy(recv_message,"N\r");
        }else if(strcmp(recv_message,"KNOCK") == 0){
                pinMode(11,INPUT);
                if(digitalRead(11)==0)
                        strcpy(recv_message,"Y\r");
                else
                        strcpy(recv_message,"N\r");
        }else if(strcmp(recv_message,"LIGHT") == 0){
		char arr[50],val;
		if(adc(0)>=800) val = 'Y';
		else val = 'N';
                snprintf(arr,50,"%c\r",val);
                strcpy(recv_message,arr);

	}else if(strcmp(recv_message,"IRO") == 0){
		char arr[50],val;
		if(adc(3)<1200) val = 'Y';
		else val = 'N';
                snprintf(arr,50,"%c\r",val);
                strcpy(recv_message,arr);

	}else if(strcmp(recv_message,"TEMP") == 0){
		char arr[50];
		snprintf(arr,50,"%d\r",dht(0));
		strcpy(recv_message,arr);

	}else if(strcmp(recv_message,"HUMI") == 0){
                char arr[50];
                snprintf(arr,50,"%d\r",dht(1));
                strcpy(recv_message,arr);

	}else if(strcmp(recv_message,"US") == 0){
                char arr[50];
                snprintf(arr,50,"%d\r",us());
                strcpy(recv_message,arr);

        }else if(strcmp(recv_message,"VR") == 0){
                char arr[50];
                snprintf(arr,50,"%d\r",adc(1));
                strcpy(recv_message,arr);

        }else if(strcmp(recv_message,"SOUND") == 0){
                char arr[50];
                snprintf(arr,50,"%d\r",adc(2));
                strcpy(recv_message,arr);

        }else if(strcmp(recv_message,"DUST") == 0){
                char arr[50];
                snprintf(arr,50,"%d\r",dust(3, 4));
                strcpy(recv_message,arr);

        }else if(strcmp(recv_message,"SOIL") == 0){
                char arr[50];
                snprintf(arr,50,"%d\r",adc(5));
                strcpy(recv_message,arr);

        }else if(strcmp(recv_message,"GAS") == 0){
                char arr[50];
                snprintf(arr,50,"%d\r",adc(4));
                strcpy(recv_message,arr);

        }else if(strcmp(recv_message,"THERM") == 0){
                char arr[50];
		double temp;

		temp=log(10000.0/(4096.0/(double)adc(6)-1));
                temp=1/(0.001149148 + (0.000234125 + (0.0000000876741 * temp *
                      temp)) *temp);
                temp=temp - 273.15;

                snprintf(arr,50,"%.2lf\r",temp);
                strcpy(recv_message,arr);

        }else if(strcmp(recv_message,"AT") == 0){
                char arr[50];
		float temp;

		temp=((float)adc(7)*5.0*100.0)/4095.0;
        	temp=5/9.0*(temp-32.0);

                snprintf(arr,50,"%.2f\r",temp);
                strcpy(recv_message,arr);
        }

        write_server(client, recv_message);
    }
}


float f_temp;
int dht(int k){
	delay(80);

	int val[5] = {0,0,0,0,0};
        uint8_t lststate = 1;
        uint8_t cnt = 0;
        uint8_t j=0,i;

        pinMode(25,OUTPUT);

        digitalWrite(25,0);
        delay(18);
	digitalWrite(25,1);
	delayMicroseconds(40);
        pinMode(25,INPUT);

        for(i=0;i<100;i++){
                cnt=0;
                while(digitalRead(25) == lststate){
                        cnt++;
                        delayMicroseconds(1);
                        if(cnt == 255) break;
                }

                lststate = digitalRead(25);

                if(cnt == 255) break;

                if((i>=4) && (i%2==0)){
                        val[j/8]<<=1;
                        if(cnt>16) val[j/8]|=1;
                        j++;
                }
        }

        f_temp=val[2]*9./5.+32;

        if((j>=40)&&(val[4]==((val[0]+val[1]+val[2]+val[3]) & 0xFF))){
                if(k)
			return val[0];
		else
			return val[2];
        }else return -1;
}

#define TRIG 28
#define OUT 29

int us(void){
        int dis=0;
        long start,travel;

        pinMode(TRIG,OUTPUT);
        pinMode(OUT,INPUT);

        digitalWrite(TRIG,0);
        usleep(2);
        digitalWrite(TRIG,1);
        usleep(20);
        digitalWrite(TRIG,0);

        while(digitalRead(OUT) == 0);
        start = micros();
        while(digitalRead(OUT) == 1);
        travel = micros() - start;
        dis = travel / 58;

        return dis;
}

#define SPI_CH 0
#define ADC_CS 29
#define SPI_SPEED 500000

int adc(int pin){
        int value=0;
        unsigned char buf[3];

        if(wiringPiSPISetup() == -1) return -1;

        pinMode(ADC_CS,OUTPUT);

        buf[0] = 0x06 | ((pin & 0x04)>>2);
        buf[1] = ((pin & 0x03)<<6);
        buf[2] = 0x00;

        digitalWrite(ADC_CS,0);

        wiringPiSPIDataRW(SPI_CH,buf,3);

        buf[1]=0x0F & buf[1];
        value = (buf[1]<<8) | buf[2];

        digitalWrite(ADC_CS,1);

       return value;
}

int dust(int pin, int out){
	int value=0;
        unsigned char buf[3];

        pinMode(out,OUTPUT);

        digitalWrite(out,LOW);
        delayMicroseconds(280);

	value = adc(pin);

        delayMicroseconds(40);
        digitalWrite(out,HIGH);
        delayMicroseconds(9680);

	return value;
}

void stmactive(int pin_1A, int pin_1B, int pin_2A, int pin_2B){
	int i;

	pinMode(pin_1A,OUTPUT);
	pinMode(pin_1B,OUTPUT);
	pinMode(pin_2A,OUTPUT);
	pinMode(pin_2B,OUTPUT);

	for(i=0; i<500; i++){
		digitalWrite(pin_1A,HIGH);
		digitalWrite(pin_1B,LOW);
		digitalWrite(pin_2A,LOW);
		digitalWrite(pin_2B,LOW);
		usleep(2000);
		digitalWrite(pin_1A,LOW);
                digitalWrite(pin_1B,HIGH);
                digitalWrite(pin_2A,LOW);
                digitalWrite(pin_2B,LOW);
                usleep(2000);
                digitalWrite(pin_1A,LOW);
                digitalWrite(pin_1B,LOW);
                digitalWrite(pin_2A,HIGH);
                digitalWrite(pin_2B,LOW);
                usleep(2000);
                digitalWrite(pin_1A,LOW);
                digitalWrite(pin_1B,LOW);
                digitalWrite(pin_2A,LOW);
                digitalWrite(pin_2B,HIGH);
                usleep(2000);
	}
}