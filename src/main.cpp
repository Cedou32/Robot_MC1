#include "mbed.h"

DigitalOut dir(D11);
DigitalOut step(D10);

int main (){
    while(1){
        dir = 1;
        for (uint8_t i = 0; i <= 200; i++){
            step = 1;
            thread_sleep_for(1);
            step = 0;
            thread_sleep_for(1);
        }
        thread_sleep_for(250);
        dir = 0;
        for (uint8_t i = 0; i <= 200; i++){
            step = 1;
            thread_sleep_for(1);
            step = 0;
            thread_sleep_for(1);
        }
        thread_sleep_for(250);
    }
}