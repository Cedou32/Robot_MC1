#include "mbed.h"
#include "stdio.h"

AnalogIn PA0(PA_0);
AnalogIn PA1(PA_1);
AnalogIn PA2(PA_2);
AnalogIn PA3(PA_3);
AnalogIn PA4(PA_4);
AnalogIn PA5(PA_5);
AnalogIn PA6(PA_6);
AnalogIn PA7(PA_7);

AnalogIn PB0 (PB_0);
AnalogIn PB1(PB_1);
 
AnalogIn PC0(PC_0);
AnalogIn PC1(PC_1);
AnalogIn PC2(PC_2);
AnalogIn PC3(PC_4);
AnalogIn PC5(PC_5);

uint16_t _0PA = 0;
uint16_t _1PA = 0;
uint16_t _2PA = 0;
uint16_t _3PA = 0;
uint16_t _4PA = 0;
uint16_t _5PA = 0;
uint16_t _6PA = 0;
uint16_t _7PA = 0;

uint16_t _0PB = 0;
uint16_t _1PB = 0;

uint16_t _0PC = 0;
uint16_t _1PC = 0;
uint16_t _2PC = 0;
uint16_t _3PC = 0;
uint16_t _4PC = 0;

int main (){
    while(1){
        _0PA = PA0.read_u16();
        _1PA = PA1.read_u16();
        _2PA = PA2.read_u16();
        _3PA = PA3.read_u16();
        _4PA = PA4.read_u16();
        _5PA = PA5.read_u16();
        _6PA = PA6.read_u16();
        _7PA = PA7.read_u16();

        _0PB = PB0.read_u16();
        _1PB = PB1.read_u16();

        _0PC = PC0.read_u16();
        _1PC = PC1.read_u16();
        _2PC = PC2.read_u16();
        _3PC = PC3.read_u16();
        _4PC = PC4.read_u16();


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