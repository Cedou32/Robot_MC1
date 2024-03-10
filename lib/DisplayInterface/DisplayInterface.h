/*       Fichier .h de la librairie DisplayInterface        */
/*Cette permet de gerer l'affichage de l'ecran sans         */
/*surcharger le code principal                              */
/*Créée par Mihai Stinga                                    */

#ifndef DISPLAYINTERFACE_H
#define DISPLAYINTERFACE_H

#include <mbed.h>
#include "SPI_TFT_ILI9341.h"
#include "Arial12x12.h"
#include "Arial24x23.h"

class DisplayInterface {
public:
    DisplayInterface(PinName mosi, PinName miso, PinName sclk, PinName cs, PinName rst, PinName dc);
    
    void Demarrage();

    void BtnMenuNonAppuye();
    void BtnMenuAppuye();

    void BtnVitesseNonAppuye();
    void BtnVitesseAppuye();

    void BtnVitesse1NonAppuye();
    void BtnVitesse2NonAppuye();
    void BtnVitesse3NonAppuye();
    void BtnVitesse1Appuye();
    void BtnVitesse2Appuye();
    void BtnVitesse3Appuye();

    void BtnModesNonAppuye();
    void BtnModesAppuye();

    void BtnLibreNonAppuye();
    void BtnLibreAppuye();

    void BtnEnregistrerNonAppuye();
    void BtnEnregistrerAppuye();

    void BtnEtenduNonAppuye();
    void BtnEtenduAppuye();

    void BtnDebogageNonAppuye();
    void BtnDebogageAppuye();

    void FermerVitesse();
    void FermerMode();

    
    void BtnFermer();
    void BtnChoisir();
    void BtnBatterie(int8_t batterie, uint8_t ligne);
    void BatterieInteractif(int8_t batterie, int8_t last_batterie, uint8_t ligne, uint8_t last_ligne);
    void Batterie(int8_t batterie);
    void Fermer();
    void LogoOn();
    void LogoOff();

private:
    SPI_TFT_ILI9341 TFT;

};

#endif