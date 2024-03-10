/*      Fichier .cpp de la librairie DisplayInterface       */
/*Cette permet de gerer l'affichage de l'ecran sans         */
/*surcharger le code principal                              */
/*Créée par Mihai Stinga                                    */

#include "DisplayInterface.h"
#include "mbed.h"
#include "SPI_TFT_ILI9341.h"
#include "Arial12x12.h"
#include "Arial24x23.h"


DisplayInterface::DisplayInterface(PinName mosi, PinName miso, PinName sclk, PinName cs, PinName reset, PinName dc, const char * name)
    : TFT(mosi, miso, sclk, cs, reset, dc, name) {}

void DisplayInterface::Demarrage()
{
    TFT.background(Black);
    TFT.cls();
    TFT.set_orientation(3);
    TFT.rect(0, 0, 320, 240, Red);
}

void DisplayInterface::BtnMenuNonAppuye()
{
    TFT.rect(210, 10, 310, 40, White);
    TFT.set_font((unsigned char *)Arial24x23);
    TFT.foreground(Red);
    TFT.locate(220, 15);
    TFT.printf("Menu");
}

void DisplayInterface::BtnBatterie(){
    TFT.rect(10, 5, 50, 20, White);
    TFT.rect(50, 10, 55, 15, White);
    TFT.line(50, 11, 50, 14, Black);
    TFT.fillrect(11, 6, 20, 19, Red);
    TFT.fillrect(21, 6, 35, 19, Orange);
    TFT.fillrect(36, 6, 49, 19, DarkGreen);
    TFT.fillrect(50, 11, 54, 14, DarkGreen);
}