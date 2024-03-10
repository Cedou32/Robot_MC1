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

void DisplayInterface::FermerVitesse()
{
    TFT.fillrect(120, 50, 200, 70, Black);
}

void DisplayInterface::FermerMode()
{
    TFT.fillrect(120, 80, 310, 130, Black);
}

void DisplayInterface::BtnFermer()
{
    TFT.rect(240, 210, 310, 230, White);
    TFT.set_font((unsigned char *)Arial12x12);
    TFT.foreground(White);
    TFT.locate(252, 215);
    TFT.printf("Fermer");
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
    TFT.fillrect(21, 6, 35, 19, Yellow);
    TFT.fillrect(36, 6, 49, 19, Green);
    TFT.fillrect(50, 11, 54, 14, Green);
}

void DisplayInterface::Batterie(int8_t batterie){
    TFT.rect(240, 180, 310, 200, White);
    TFT.set_font((unsigned char *)Arial12x12);
    TFT.foreground(White);
    TFT.locate(252, 185);
    TFT.printf("%u", batterie);
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

void DisplayInterface::LogoOn()
{
    TFT.line(70,225,250,225, White);
    TFT.line(95,224,225,224, White);
    TFT.line(96,223,224,223, White);
    TFT.line(97,222,223,222, White);
    TFT.line(98,221,222,221, White);


    TFT.line(99,217,222,217, White);
    TFT.line(100,216,221,216, White);
    TFT.line(100,215,221,215, White);
    TFT.line(101,214,220,214, White);
    TFT.line(101,213,220,213, White);
    TFT.line(102,212,219,212, White);
    TFT.line(102,211,219,211, White);
    TFT.line(103,210,218,210, White);
    TFT.line(103,209,218,209, White);
    TFT.line(104,208,217,208, White);
    TFT.line(104,207,217,207, White);
    TFT.line(105,206,216,206, White);
    TFT.line(105,205,216,205, White);
    //
    TFT.line(119,204,161,204, White);
    TFT.line(119,203,161,203, White);
    TFT.line(119,202,160,202, White);
    TFT.line(119,201,160,201, White);
    //
    TFT.line(120,200,160,200, White);
    TFT.line(121,199,160,199, White);
    TFT.line(122,198,159,198, White);
    TFT.line(122,197,159,197, White);
    TFT.line(123,196,159,196, White);
    TFT.line(124,195,158,195, White);
    TFT.line(125,194,158,194, White);
    TFT.line(126,193,158,193, White);
    TFT.line(127,192,157,192, White);
    TFT.line(127,191,157,191, White);
    //
    TFT.line(128,190,157,190, White);
    TFT.line(129,189,157,189, White);
    TFT.line(130,188,156,188, White);
    TFT.line(131,187,156,187, White);
    TFT.line(131,186,156,186, White);
    TFT.line(131,185,156,185, White);
    TFT.line(131,184,156,184, White);
    TFT.line(131,183,156,183, White);
    TFT.line(131,182,155,182, White);
    TFT.line(130,181,155,181, White);
    //
    TFT.line(130,180,155,180, White);
    TFT.line(129,179,155,179, White);
    TFT.line(129,178,154,178, White);
    TFT.line(128,177,154,177, White);
    TFT.line(128,176,154,176, White);
    TFT.line(127,175,153,175, White);
    TFT.line(127,174,153,174, White);
    TFT.line(127,173,152,173, White);
    TFT.line(126,172,151,172, White);
    TFT.line(126,171,151,171, White);
    //
    TFT.line(125,170,150,170, White);
    TFT.line(124,169,149,169, White);
    TFT.line(124,168,148,168, White);
    TFT.line(123,167,147,167, White);
    TFT.line(123,166,146,166, White);
    TFT.line(122,165,146,165, White);
    TFT.line(122,164,146,164, White);
    TFT.line(121,163,146,163, White);
    TFT.line(121,162,146,162, White);
    TFT.line(120,161,146,161, White);
    //
    TFT.line(119,160,145,160, White);
    TFT.line(119,159,145,159, White);
    TFT.line(119,158,145,158, White);
    TFT.line(124,157,145,157, White);
    TFT.line(126,156,145,156, White);
    TFT.line(126,155,145,155, White);
    TFT.line(127,154,145,154, White);
    TFT.line(128,153,145,153, White);
    TFT.line(129,152,145,152, White);
    TFT.line(130,151,145,151, White);
    //
    TFT.line(131,150,137,150, White);   TFT.line(139,150,145,150, White);
    TFT.line(132,149,136,149, White);   TFT.line(141,149,145,149, White);
    TFT.line(133,148,137,148, White);   TFT.line(142,148,145,148, White);
    TFT.line(134,147,138,147, White);
    TFT.line(135,146,139,146, White);
    TFT.line(135,145,140,145, White);
    TFT.line(136,144,244,144, White);
    TFT.line(137,143,244,143, White);
    TFT.line(138,142,244,142, White);
    TFT.line(139,141,244,141, White);
    TFT.line(140,140,244,140, White); 


    TFT.line(163,200,189,200, White);   TFT.fillrect(185,170,189,190, White);
    TFT.line(163,199,189,199, White);
    TFT.line(163,198,189,198, White);
    TFT.line(162,197,189,197, White);
    TFT.line(162,196,189,196, White);
    TFT.line(162,195,189,195, White);
    TFT.line(161,194,189,194, White);
    TFT.line(161,193,189,193, White);
    TFT.line(161,192,189,192, White);
    TFT.line(160,191,189,191, White);
    //
    TFT.line(160,190,171,190, White);
    TFT.line(160,189,171,189, White);
    TFT.line(160,188,171,188, White);
    TFT.line(159,187,171,187, White);
    TFT.line(159,186,171,186, White);
    TFT.line(159,185,171,185, White);
    TFT.line(159,184,171,184, White);
    TFT.line(159,183,171,183, White);
    TFT.line(159,182,171,182, White);
    TFT.line(158,181,171,181, White);
    //
    TFT.line(158,180,171,180, White);
    TFT.line(158,179,171,179, White);
    TFT.line(158,178,171,178, White);
    TFT.line(157,177,171,177, White);
    TFT.line(157,176,171,176, White);
    TFT.line(157,175,171,175, White);
    TFT.line(156,174,171,174, White);
    TFT.line(156,173,171,173, White);
    TFT.line(155,172,171,172, White);
    TFT.line(154,171,171,171, White);
    //
    TFT.line(154,170,171,170, White);
    TFT.line(153,169,171,169, White);
    TFT.line(152,168,171,168, White);
    TFT.line(151,167,171,167, White);
    TFT.line(150,166,171,166, White);   TFT.line(178,166,196,166, White);
    TFT.line(149,165,171,165, White);   TFT.line(177,165,197,165, White);
    TFT.line(149,164,171,164, White);   TFT.line(176,164,198,164, White);
    TFT.line(149,163,171,163, White);   TFT.line(175,163,199,163, White);
    TFT.line(149,162,171,162, White);   TFT.line(174,162,200,162, White);
    TFT.line(149,161,171,161, White);   TFT.line(173,161,201,161, White);
    //
    TFT.line(150,160,207,160, White);
    TFT.line(150,159,208,159, White);
    TFT.line(194,158,209,158, White);
    TFT.line(194,157,210,157, White);
    TFT.line(194,156,211,156, White);
    TFT.line(194,155,212,155, White);
    TFT.fillrect(151,148,241,154, White);

    

}
void DisplayInterface::LogoOff()
{
}