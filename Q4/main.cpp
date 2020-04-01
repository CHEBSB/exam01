#include "mbed.h"
#include "uLCD_4DGL.h"

uLCD_4DGL uLCD(D1, D0, D2); // serial tx, serial rx, reset pin;
PwmOut PWM1(D6);
Serial pc( USBTX, USBRX );
DigitalIn Din(D7);
Thread T1;
Thread T2;
Thread T3;
double sampledData;
double sampled[128];

void sendData() {
    while(1){
        pc.printf("%d\n", (int)sampledData);
        wait(0.1);
    }
}

void sample() {
    static int i = 0;
    while(1){
        if (i < 128)
            sampled[i] = Din;
        sampledData = Din;
        wait(1 / 2000);
        i++;
    }
}

void sendToPython() {
    for (int i = 0; i < 128; i++) {
        wait(0.1);
        pc.printf("%1.3f\r\n", sampled[i]);
    }
}
int main() {
    // basic printf demo = 16 by 18 characters on screen
    uLCD.printf("\n107061110\n"); //Default Green on black text
    
    uLCD.line(20,20 , 30, 20, BLUE);
    uLCD.line(20, 30 , 30, 30, BLUE);
    uLCD.line(20, 20 , 20, 30, BLUE);
    uLCD.line(30, 20 , 30, 30, BLUE);
   PWM1.period(0.001);
   T2.start(sample);
   T3.start(sendToPython);
   T1.start(sendData);
    while(1) {
        for (double i = 0.1; i < 1; i += 0.1) {
            PWM1 = i;
            wait(0.1);
        }
        for (double i = 1; i > 0.1; i -= 0.1) {
            PWM1 = i;
            wait(0.1);
        }
    }
}