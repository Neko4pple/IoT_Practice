#include <stdio.h>
#include <wiringPi.h>
#include <pthread.h>
#include <unistd.h> // usleep 추가

#define TRIG 28
#define OUT 26
#define PIN_1A 27
#define PIN_1B 0
#define PIN_2A 1
#define PIN_2B 24
#define DELAY 8000 //7000 //2000
#define LED_PIN 7
#define BUZZER_PIN 15
#define SPI_CH 0
#define ADC_CH 0
#define ADC_CS 29
#define SPI_SPEED 500000
int buzzerOn = 0;

void led_on(void){
digitalWrite(LED_PIN,HIGH);
}   
void led_off(void){
digitalWrite(LED_PIN,LOW);
}
void buzzer_on(void){
digitalWrite(BUZZER_PIN,HIGH);
}   
void buzzer_off(void){
digitalWrite(BUZZER_PIN,LOW);
}
void stepD() {
                digitalWrite(PIN_1A,HIGH);
                digitalWrite(PIN_1B,LOW);
                digitalWrite(PIN_2A,LOW);
                digitalWrite(PIN_2B,LOW);
                delay(1000);
                digitalWrite(PIN_1A,LOW);
                digitalWrite(PIN_1B,HIGH);
                digitalWrite(PIN_2A,LOW);
                digitalWrite(PIN_2B,LOW);
                delay(1000);
                digitalWrite(PIN_1A,LOW);
                digitalWrite(PIN_1B,LOW);
                digitalWrite(PIN_2A,HIGH);
                digitalWrite(PIN_2B,LOW);
                delay(1000);
                digitalWrite(PIN_1A,LOW);
                digitalWrite(PIN_1B,LOW);
                digitalWrite(PIN_2A,LOW);
                digitalWrite(PIN_2B,HIGH);
                delay(1000);
}

int get_distance(){
        int dis=0, i;
        long start,travel; 
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

// 초음파 센서 측정 함수
void *ultrasonic_task(void *arg) {
     pinMode(TRIG,OUTPUT);
     pinMode(OUT,INPUT);
     int ledOn = 0;
     int motor_running = 0;
     while(1) {
           int dis=get_distance();
           if(dis >= 20 && ledOn == 1){
               printf("%dcm >= 20cm, LED off.\n", dis);
               ledOn = 0;
               led_off();
           }
           if(dis < 30){
               if(motor_running==1){
                   printf("%dcm < 30cm, Step Moteor Stopped.\n", dis);
                   motor_running = 0;
               }
               if(dis<20){
                   if(ledOn == 0){
                     printf("%dcm < 20cm, LED On.\n", dis);
                     ledOn = 1;
                     led_on();
                   }
               }
               if (dis<10) {
                    printf("%dcm < 10cm, Buzzer On.\n", dis);
                    buzzerOn = 1;
                    buzzer_on();
                } else {
                    printf("%dcm >= 10cm, Buzzer Off.\n", dis);
                    buzzerOn = 0;
                    buzzer_off();
                }
           }
           else{ 
                if(motor_running==0){
                  printf("%dcm >= 30cm, Step Moteor Resumed.\n", dis);
                  motor_running = 1;
                }
                stepD(); 
           }
           delay(100);

        }
}

// 조도 센서 측정 함수
void *light_task(void *arg) {
    unsigned char buf[3];
    if (wiringPiSPISetup(SPI_CH,SPI_SPEED) == -1) pthread_exit(NULL);
    pinMode(ADC_CS,OUTPUT);
    pinMode(BUZZER_PIN,OUTPUT);
    while(1) {
        buf[0] = 0x06 | ((ADC_CH & 0x04)>>2);
        buf[1] = ((ADC_CH & 0x03)<<6);
        buf[2] = 0x00;
        digitalWrite(ADC_CS,0);
        wiringPiSPIDataRW(SPI_CH,buf,3);
        buf[1]=0x0F & buf[1];
        int value=(buf[1] << 8) | buf[2];
        digitalWrite(ADC_CS,1);
        printf("Light Sensor: %d\n", value);
        while(1) {
        buf[0] = 0x06 | ((ADC_CH & 0x04)>>2);
        buf[1] = ((ADC_CH & 0x03)<<6);
        buf[2] = 0x00;
        digitalWrite(ADC_CS,0);
        wiringPiSPIDataRW(SPI_CH,buf,3);
        buf[1]=0x0F & buf[1];
        int value=(buf[1] << 8) | buf[2];
        digitalWrite(ADC_CS,1);
        printf("Light Sensor: %d\n", value);
        if (value < 1000) {
            if (buzzerOn == 0) {
                printf("Light sensor value < 1000, Buzzer On.\n");
                buzzerOn = 1;
                buzzer_on();
            }
        } else {
            if (buzzerOn == 1) {
                printf("Light sensor value >= 1000, Buzzer Off.\n");
                buzzerOn = 0;
                buzzer_off();
            }
        }
        delay(100);
    }
    }
}

int main(void) {
    int motor_running=1;
    int ledOn = 0;
    int buzzerOn = 0;
    if (wiringPiSetup() == -1) return 1;
    pinMode(TRIG,OUTPUT);
    pinMode(OUT,INPUT);
    pinMode(PIN_1A,OUTPUT);
    pinMode(PIN_1B,OUTPUT);
    pinMode(PIN_2A,OUTPUT);
    pinMode(PIN_2B,OUTPUT);
    pinMode(LED_PIN,OUTPUT);
    pinMode(BUZZER_PIN,OUTPUT);
    stepD();

    pthread_t ultrasonic_thread, light_thread;
    //pthread_create(thread, attr, fucntion, argument);
    //여기선 지정한 함수들의 주소값을 반환하기 위해 &로 호출.
    //실제 작동부는 ultrasonic_task, light_task.
    pthread_create(&ultrasonic_thread, NULL, ultrasonic_task, NULL);
    pthread_create(&light_thread, NULL, light_task, NULL);


    //pthread_join(thread, retreval);
    //반환값을 리턴하고, 종료 대기상태 진입하는 코드.
    pthread_join(ultrasonic_thread, NULL);
    pthread_join(light_thread, NULL);

    //해당 코드를 스레딩 컴파일 시키고 싶다면?
    //gcc -o <filename> <codename.c> -lwiringPi -lwiringPiDev -lpthread
    return 0;
}
