#include "mbed.h"

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