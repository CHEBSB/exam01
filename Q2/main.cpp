#include "mbed.h"

PwmOut PWM1(D6);

int main() {
   PWM1.period(0.01);
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