#include "mbed.h"
#include "stdio.h"

DigitalOut dir(D11);
DigitalOut step(D10);
AnalogIn Y(A0);
AnalogIn X(A1);

uint16_t valeur_y = 0;

int main (){
    while(1){
        
        valeur_y = Y.read_u16();

        while(valeur_y >= 31000 & valeur_y <= 34000){
            valeur_y = Y.read_u16();
        }
        if(valeur_y > 33500){
            dir = 1;
        }else if (valeur_y < 32000){
            dir = 0;
        }

        step = 1;
        thread_sleep_for(1);
        step = 0;
        thread_sleep_for(1);
    }
}