#include <stdio.h>
#include <wiringPi.h>

#define SPI_CH 0
#define ADC_CH 7
#define ADC_CS 29
#define SPI_SPEED 500000

int main(void){
        int value=0, i;
        unsigned char buf[3];
	float temp;

        if(wiringPiSetup() == -1) return 1;
        if(wiringPiSPISetup() == -1) return -1;

        pinMode(ADC_CS,OUTPUT);


        for(i=0; i<20; i++){
                buf[0] = 0x06 | ((ADC_CH & 0x04)>>2);
                buf[1] = ((ADC_CH & 0x03)<<6);
                buf[2] = 0x00;

                digitalWrite(ADC_CS,0);

                wiringPiSPIDataRW(SPI_CH,buf,3);

                buf[1]=0x0F & buf[1];

                value=(buf[1] << 8) | buf[2];

                digitalWrite(ADC_CS,1);

		temp=((float)value*5.0*100.0)/4095.0;
        	temp=5/9.0*(temp-32.0);
                printf("%f\n", temp);
		delay(100);
        }
}
