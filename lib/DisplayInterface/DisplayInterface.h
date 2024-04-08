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
#include "GraphicsDisplay.h"

class DisplayInterface {
public:
    DisplayInterface(PinName mosi, PinName miso, PinName sclk, PinName cs, PinName rst, PinName dc);

    void BtnOn();
    void BtnOff();
    
    void Demarrage();

    void BtnMenuNonAppuye();
    void BtnMenuAppuye();

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

    void BtnDemarrerNonAppuye();
    void BtnDemarrerAppuye();
    void FermerBtnDemarrer();
    void FinEnregistrement();

    void AffichageLibre();
    void AffichageEnregistrer();
    void AffichageDemo();
    void AffichageDebug();

    void FermerAffichage();

    void FermerMode();

    
    //void BtnFermer();
    void BtnChoisir();
    void BtnBatterie(int8_t batterie, uint8_t ligne);
    void BatterieInteractif(int8_t batterie, int8_t last_batterie, uint8_t ligne, uint8_t last_ligne);
    void BatteryLow();
    void Batterie(int8_t batterie);
    void Fermer();
    void LogoOn();
    void LogoOff();

    void Menu();
    void FermerMenu();
    void Modes();
    void Libre();
    void Enregistrer();
    void Etendu();
    void Debogage();
    void Choisir();
    void SortirEtat();


    void Test(uint8_t variable);

private:
    SPI_TFT_ILI9341 TFT;

};

#endif