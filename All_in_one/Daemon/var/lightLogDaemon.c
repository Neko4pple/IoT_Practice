// sudo ./<Daemonname> & 
// ps -elf | grep Daemon
// PID 번호가 주어짐(첫번째 열 번호)
// sudo kill -9 <PID>    ------------------ -9는 signal kill을 의미. (즉시 종료)
#include <stdio.h>
#include <wiringPi.h>
#include <string.h>

#define SPI_CH 0
#define ADC_CH 0
#define ADC_CS 29
#define SPI_SPEED 500000
#define LOG_SIZE 5
#define BUF_SIZE 100

int main(void){
        FILE *fp; //동적 파일 감시 + 생성 시스템
        int value=0, i=0, j;
        unsigned char buf[3];
        char log[LOG_SIZE];
        char str[BUF_SIZE];
        char str_temp[BUF_SIZE];

        if(wiringPiSetup() == -1) return 1;
        if(wiringPiSPISetup() == -1) return -1;
        pinMode(ADC_CS,OUTPUT);
        for(i=0; i<BUF_SIZE; i++) str[i]='\0';
        i=0;

        while(1){
            buf[0] = 0x06 | ((ADC_CH & 0x04)>>2);
            buf[1] = ((ADC_CH & 0x03)<<6);
            buf[2] = 0x00;
            digitalWrite(ADC_CS,0);
            wiringPiSPIDataRW(SPI_CH,buf,3);
            buf[1]=0x0F & buf[1];
            value=(buf[1] << 8) | buf[2];
            digitalWrite(ADC_CS,1);
            log[i] = value;
            printf("log[%d]=%d\n", i,  log[i]);
            i = (i+1) % LOG_SIZE;
            
            if(i==0) {
               sprintf(str, "");
               for(j=0; j<LOG_SIZE;j++) { 
                   sprintf(str_temp, "%d", log[j]);
                   strcat(str, str_temp);
                   if (j != LOG_SIZE-1)
                     strcat(str, ", ");
               }
               fp = fopen("./log/lightLog.txt", "w");
               if (fp == NULL) printf("File Open Error!\n");
               fprintf(fp, "%s", str);
               fclose(fp);
               printf("%s\n", str);
            }
	        delay(500);
        }
}
