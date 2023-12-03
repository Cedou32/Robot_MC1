#include "mbed.h"
#include "stdio.h"

DigitalOut dir(D11);
DigitalOut step(D10);
AnalogIn Y(A0);
AnalogIn X(A1);

uint16_t valeur_x = 0;

int main (){
    while(1){
        uint16_t W = Y.read_u16();
        printf("\n\r%d",W);
        thread_sleep_for(1000);
        /*
        valeur_x = Y.read_u16();
        printf("\n\r%d",valeur_x);
        thread_sleep_for(1);*/
        /*
        // Code stepper fonctionnel
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
        thread_sleep_for(250);*/
    }
}