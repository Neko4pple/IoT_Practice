#include <stdio.h>
#include <wiringPi.h>
#include <math.h>

#define SPI_CH 0
#define ADC_CH 6
#define ADC_CS 29
#define SPI_SPEED 500000

int main(void){
        int value=0, i;
        unsigned char buf[3];
	double temp;

        if(wiringPiSetup() == -1) return 1;

        if(wiringPiSPISetup() == -1) return -1;

        pinMode(ADC_CS,OUTPUT);


        buf[0] = 0x06 | ((ADC_CH & 0x04)>>2);
        buf[1] = ((ADC_CH & 0x03)<<6);
        buf[2] = 0x00;

        digitalWrite(ADC_CS,0);

        wiringPiSPIDataRW(SPI_CH,buf,3);

        buf[1]=0x0F & buf[1];

        value=(buf[1] << 8) | buf[2];

        digitalWrite(ADC_CS,1);

	temp=log(10000.0/(4096.0/(double)value-1));
	temp=1/(0.001335148 + (0.000234125 + (0.0000000876741 * temp * temp)) *temp);
	temp=temp - 273.15;

        printf("%.2lf", temp);
}
