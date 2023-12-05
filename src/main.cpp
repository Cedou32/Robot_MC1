#include "mbed.h"
#include "stdio.h"

DigitalOut dir(D11);
DigitalOut step(D10);
AnalogIn Y(A0);
AnalogIn X(A1);

uint16_t valeur_y = 0;

enum {attente_mouvement, dir_droite, dir_gauche, mouv_un_step};
uint8_t etat = 0;



int main (){
    etat = attente_mouvement;
    while(1){
        /**/
        valeur_y = Y.read_u16();

        switch(etat){
            case attente_mouvement:
                if(valeur_y > 35000){
                    etat = dir_droite;
                }else if(valeur_y < 31000){
                    etat = dir_gauche;
                }
            break;

            case dir_droite:
                dir = 1;
                etat = mouv_un_step;
            break;

            case dir_gauche:
                dir = 0;
                etat = mouv_un_step;
            break;

            case mouv_un_step:
                step = 1;
                thread_sleep_for(1);
                step = 0;
                thread_sleep_for(1);
                etat = attente_mouvement;
            break;
        }
    }
}