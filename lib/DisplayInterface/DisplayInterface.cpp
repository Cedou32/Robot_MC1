/*      Fichier .cpp de la librairie DisplayInterface       */
/*Cette permet de gerer l'affichage de l'ecran sans         */
/*surcharger le code principal                              */
/*Créée par Mihai Stinga                                    */

#include "DisplayInterface.h"

DisplayInterface::DisplayInterface(PinName mosi, PinName miso, PinName sclk, PinName cs, PinName reset, PinName dc)
    : TFT(mosi, miso, sclk, cs, reset, dc) {}

void DisplayInterface::Demarrage()
{
    TFT.background(Black);
    TFT.cls();
    TFT.set_orientation(3);
    TFT.rect(0, 0, 320, 240, Blue);
}

void DisplayInterface::BtnMenuNonAppuye()
{
    TFT.rect(210, 10, 310, 40, White);
    TFT.set_font((unsigned char *)Arial24x23);
    TFT.foreground(Blue);
    TFT.locate(220, 15);
    TFT.printf("Menu");
}

void DisplayInterface::BtnMenuAppuye()
{
    TFT.set_font((unsigned char *)Arial24x23);
    TFT.foreground(DarkGrey);
    TFT.locate(220, 15);
    TFT.printf("Menu");
}

void DisplayInterface::BtnVitesseNonAppuye()
{
    TFT.rect(10, 50, 90, 70, White);
    TFT.set_font((unsigned char *)Arial12x12);
    TFT.foreground(Green);
    TFT.locate(25, 55);
    TFT.printf("Vitesse");
}

void DisplayInterface::BtnVitesseAppuye()
{
    TFT.rect(10, 50, 90, 70, DarkGrey);
    TFT.set_font((unsigned char *)Arial12x12);
    TFT.foreground(DarkGrey);
    TFT.locate(25, 55);
    TFT.printf("Vitesse");
}

void DisplayInterface::BtnVitesse1NonAppuye()
{
    TFT.rect(120, 50, 140, 70, White);
    TFT.set_font((unsigned char *)Arial12x12);
    TFT.foreground(Red);
    TFT.locate(127, 57);
    TFT.printf("1");
}

void DisplayInterface::BtnVitesse2NonAppuye()
{
    TFT.rect(150, 50, 170, 70, White);
    TFT.set_font((unsigned char *)Arial12x12);
    TFT.foreground(Red);
    TFT.locate(157, 57);
    TFT.printf("2");
}

void DisplayInterface::BtnVitesse3NonAppuye()
{
    TFT.rect(180, 50, 200, 70, White);
    TFT.set_font((unsigned char *)Arial12x12);
    TFT.foreground(Red);
    TFT.locate(187, 57);
    TFT.printf("3");
}

void DisplayInterface::BtnVitesse1Appuye()
{
    TFT.rect(120, 50, 140, 70, DarkGrey);
    TFT.set_font((unsigned char *)Arial12x12);
    TFT.foreground(DarkGrey);
    TFT.locate(127, 57);
    TFT.printf("1");
}

void DisplayInterface::BtnVitesse2Appuye()
{
    TFT.rect(150, 50, 170, 70, DarkGrey);
    TFT.set_font((unsigned char *)Arial12x12);
    TFT.foreground(DarkGrey);
    TFT.locate(157, 57);
    TFT.printf("2");
}

void DisplayInterface::BtnVitesse3Appuye()
{
    TFT.rect(180, 50, 200, 70, White);
        TFT.set_font((unsigned char *)Arial12x12);
        TFT.foreground(DarkGrey);
        TFT.locate(187, 57);
        TFT.printf("3");
}

void DisplayInterface::BtnModesNonAppuye()
{
    TFT.rect(10, 80, 90, 100, White);
    TFT.set_font((unsigned char *)Arial12x12);
    TFT.foreground(Orange);
    TFT.locate(25, 85);
    TFT.printf("Modes");
}

void DisplayInterface::BtnModesAppuye()
{
    TFT.rect(10, 80, 90, 100, DarkGrey);
    TFT.set_font((unsigned char *)Arial12x12);
    TFT.foreground(DarkGrey);
    TFT.locate(25, 85);
    TFT.printf("Modes");
}

void DisplayInterface::BtnLibreNonAppuye()
{
    TFT.rect(120, 80, 210, 100, White);
    TFT.set_font((unsigned char *)Arial12x12);
    TFT.foreground(Green);
    TFT.locate(140, 85);
    TFT.printf("Libre");
}

void DisplayInterface::BtnLibreAppuye()
{
    TFT.rect(120, 80, 210, 100, DarkGrey);
    TFT.set_font((unsigned char *)Arial12x12);
    TFT.foreground(DarkGrey);
    TFT.locate(140, 85);
    TFT.printf("Libre");
}

void DisplayInterface::BtnEnregistrerNonAppuye()
{
    TFT.rect(220, 80, 310, 100, White);
    TFT.set_font((unsigned char *)Arial12x12);
    TFT.foreground(Green);
    TFT.locate(225, 85);
    TFT.printf("Enregistrer");
}

void DisplayInterface::BtnEnregistrerAppuye()
{
    TFT.rect(220, 80, 310, 100, DarkGrey);
    TFT.set_font((unsigned char *)Arial12x12);
    TFT.foreground(DarkGrey);
    TFT.locate(225, 85);
    TFT.printf("Enregistrer");
}

void DisplayInterface::BtnEtenduNonAppuye()
{
    TFT.rect(120, 110, 210, 130, White);
    TFT.set_font((unsigned char *)Arial12x12);
    TFT.foreground(Green);
    TFT.locate(140, 115);
    TFT.printf("Etendu");
}

void DisplayInterface::BtnEtenduAppuye()
{
    TFT.rect(120, 110, 210, 130, DarkGrey);
    TFT.set_font((unsigned char *)Arial12x12);
    TFT.foreground(DarkGrey);
    TFT.locate(140, 115);
    TFT.printf("Etendu");
}

void DisplayInterface::BtnDebogageNonAppuye()
{
    TFT.rect(220, 110, 310, 130, White);
    TFT.set_font((unsigned char *)Arial12x12);
    TFT.foreground(Green);
    TFT.locate(225, 115);
    TFT.printf("Debogage");
}

void DisplayInterface::BtnDebogageAppuye()
{
    TFT.rect(220, 110, 310, 130, DarkGrey);
    TFT.set_font((unsigned char *)Arial12x12);
    TFT.foreground(DarkGrey);
    TFT.locate(225, 115);
    TFT.printf("Debogage");
}

void DisplayInterface::BtnFermer()
{
    TFT.rect(240, 210, 310, 230, White);
    TFT.set_font((unsigned char *)Arial12x12);
    TFT.foreground(White);
    TFT.locate(252, 215);
    TFT.printf("Fermer");
}

void DisplayInterface::Fermer()
{
    TFT.fillrect(10, 50, 200, 70, Black);
    TFT.fillrect(240, 210, 310, 230, Black);
    TFT.fillrect(240, 180, 310, 200, Black);
    TFT.fillrect(10, 80, 90, 100, Black);
    TFT.fillrect(120, 80, 210, 100, Black);
    TFT.fillrect(220, 80, 310, 100, Black);
    TFT.fillrect(220, 110, 310, 130, Black);
    TFT.fillrect(120, 110, 210, 130, Black);
}

void DisplayInterface::BtnChoisir()
{
    TFT.rect(240, 180, 310, 200, White);
    TFT.set_font((unsigned char *)Arial12x12);
    TFT.foreground(White);
    TFT.locate(252, 185);
    TFT.printf("Choisir");
}

void DisplayInterface::BtnBatterie()
{
    TFT.rect(10, 5, 50, 20, White);
    TFT.rect(50, 10, 55, 15, White);
    TFT.line(50, 11, 50, 14, Black);
    TFT.fillrect(11, 6, 20, 19, Red);
    TFT.fillrect(21, 6, 35, 19, Orange);
    TFT.fillrect(36, 6, 49, 19, DarkGreen);
    TFT.fillrect(50, 11, 54, 14, DarkGreen);
}