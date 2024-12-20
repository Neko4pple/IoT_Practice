  1 #include <stdio.h>
  2 #include <wiringPi.h>
  3
  4 #define SPI_CH 0
  5 #define ADC_CH 0
  6 #define ADC_CS 29
  7 #define SPI_SPEED 500000
  8
  9 int main(void){
 10         int value=0, i;
 11         unsigned char buf[3];
 12
 13         if(wiringPiSetup() == -1) return 1;
 14
 15         if(wiringPiSPISetup() == -1) return -1;
 16
 17         pinMode(ADC_CS,OUTPUT);
 18
 19
 20         buf[0] = 0x06 | ((ADC_CH & 0x04)>>2);
 21         buf[1] = ((ADC_CH & 0x03)<<6);
 22         buf[2] = 0x00;
 23
 24         digitalWrite(ADC_CS,0);
 25         wiringPiSPIDataRW(SPI_CH,buf,3);
 26
 27         buf[1]=0x0F & buf[1];
 28
 29         value=(buf[1] << 8) | buf[2];
 30
 31         digitalWrite(ADC_CS,1);
 32
 33         printf("%d\n", value);
 34
 35         delay(500);
 36
 37 }