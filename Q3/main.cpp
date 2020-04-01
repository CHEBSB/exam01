#include "mbed.h"

PwmOut PWM1(D6);
Serial pc( USBTX, USBRX );
DigitalIn Din(D7);
Thread T1;
Thread T2;
double sampledData;

void sendData() {
    while(1){
        pc.printf("%1.3f\r\n", sampledData);
        wait(0.1);
    }
}

void sample() {
    while(1){
        sampledData = Din;
        wait(1 / 2000);
    }
}

int main() {

   PWM1.period(0.001);
   T2.start(sample);
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