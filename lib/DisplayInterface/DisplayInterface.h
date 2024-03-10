/*       Fichier .h de la librairie DisplayInterface        */
/*Cette permet de gerer l'affichage de l'ecran sans         */
/*surcharger le code principal                              */
/*Créée par Mihai Stinga                                    */

#ifndef TOUCHSCREEN_H
#define TOUCHSCREEN_H

#include <mbed.h>
#include "SPI_TFT_ILI9341.h"

class DisplayInterface {
public:
    DisplayInterface(PinName mosi, PinName miso, PinName sclk, PinName cs, PinName reset, PinName dc, const char* name ="TFT");
    void Demarrage();
    void BtnMenuNonAppuye();
    void BtnBatterie();

private:
    SPI_TFT_ILI9341 TFT;

};

#endif