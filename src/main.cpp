#include "mbed.h"
#include "stdio.h"

DigitalOut PA0(PA_0);
DigitalOut PA5(PA_5);
DigitalOut PA6(PA_6);
DigitalOut PA7(PA_7);
DigitalOut RX(PA_10);

DigitalOut PB0(PB_0);
PwmOut PWMB3(PB_3);
DigitalOut PB4(PB_4);
DigitalOut PB5(PB_5);
DigitalOut TX(PB_6);
DigitalOut PB7(PB_7);
DigitalOut PB8(PB_8);
DigitalOut PB9(PB_9);

DigitalOut PC0(PC_0);
DigitalOut PC1(PC_1);
DigitalOut PC2(PC_2);
DigitalOut PC3(PC_3);
DigitalOut PC4(PC_4);
DigitalOut PC5(PC_5);
PwmOut PWMC11(PC_11);
PwmOut PWMC12(PC_12);

int main()
{
  PWMB3.period_ms(250);
  PWMC11.period_ms(250);
  PWMC11.period_ms(250);

  PWMB3.write(0.5f);
  PWMC11.write(0.5f);
  PWMC12.write(0.5f);
  while (1)
  {

    /*PA0 = 1;
    PA5 = 1;
    PA6 = 1;
    PA7 = 1;
    RX = 1;

    PB0 = 1;
    PB4 = 1;
    PB5 = 1;
    TX = 1;
    PB7 = 1;
    PB8 = 1;
    PB9 = 1;

    PC0 = 1;
    PC1 = 1;
    PC2 = 1;
    PC3 = 1;
    PC4 = 1;
    PC5 = 1;

    thread_sleep_for(200);

    PA0 = 0;
    PA5 = 0;
    PA6 = 0;
    PA7 = 0;
    RX = 0;

    PB0 = 0;
    PB4 = 0;
    PB5 = 0;
    TX = 0;
    PB7 = 0;
    PB8 = 0;
    PB9 = 0;

    PC0 = 0;
    PC1 = 0;
    PC2 = 0;
    PC3 = 0;
    PC4 = 0;
    PC5 = 0;

    thread_sleep_for(200);*/

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