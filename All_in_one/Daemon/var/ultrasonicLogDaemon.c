#include <stdio.h>
#include <wiringPi.h>
#include <string.h>

#define TRIG 28
#define OUT 29
#define LOG_SIZE 5
#define BUF_SIZE 100

int main(void){

        FILE *fp;
        int value=0, i=0, j;
        
        unsigned char buf[3];
        char log[LOG_SIZE];
        char str[BUF_SIZE];
        char str_temp[BUF_SIZE];

        for(i=0; i<BUF_SIZE; i++) str[i]='\0';
        i=0;

        int dis=0;
        long start,travel;

        if(wiringPiSetup() == -1) return 1;

        pinMode(TRIG,OUTPUT);
        pinMode(OUT,INPUT);

        while(1){
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

                printf("%d\n", dis);
                delay(100);

                log[i] = dis;
                printf("log[%d]=%d\n", i,  log[i]);
                i = (i+1) % LOG_SIZE;
            }

            if(i==0) {
               sprintf(str, "");
               for(j=0; j<LOG_SIZE;j++) { 
                   sprintf(str_temp, "%d", log[j]);
                   strcat(str, str_temp);
                   if (j != LOG_SIZE-1)
                     strcat(str, ", ");
               }
               fp = fopen("./log/DistanceLog.txt", "w");
               if (fp == NULL) printf("File Open Error!\n");
               fprintf(fp, "%s", str);
               fclose(fp);
               printf("%s\n", str);
            }
        delay(500);
}