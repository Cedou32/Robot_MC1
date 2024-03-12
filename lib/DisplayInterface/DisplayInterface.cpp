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

void DisplayInterface::BtnBatterie(int8_t batterie, uint8_t ligne)
{
    TFT.rect(10, 5, 50, 20, White);
    TFT.rect(50, 10, 55, 15, White);
    TFT.line(50, 11, 50, 14, Black);

    // uint8_t ligne = batterie * 0.43 + 11;

    if (ligne < 21)
    {
        TFT.fillrect(11, 6, ligne, 19, Red);
    }
    else if (ligne > 20 && ligne < 36)
    {
        TFT.fillrect(11, 6, 20, 19, Red);
        TFT.fillrect(21, 6, ligne, 19, Yellow);
    }
    else if (ligne > 35 && ligne < 51)
    {
        TFT.fillrect(11, 6, 20, 19, Red);
        TFT.fillrect(21, 6, 35, 19, Yellow);
        TFT.fillrect(36, 6, ligne, 19, Green);
    }
    else if (ligne > 49 && ligne < 55)
    {
        TFT.fillrect(11, 6, 20, 19, Red);
        TFT.fillrect(21, 6, 35, 19, Yellow);
        TFT.fillrect(36, 6, 49, 19, Green);
        TFT.fillrect(50, 11, ligne, 14, Green);
    }
}

void DisplayInterface::BatterieInteractif(int8_t batterie, int8_t last_batterie, uint8_t ligne, uint8_t last_ligne)
{
    // uint8_t ligne = batterie * 0.43 + 11;
    // uint8_t last_ligne = last_batterie * 0.43 + 11;
    int8_t etat = batterie - last_batterie; //<0 = decharge
    uint16_t couleur;
    if (ligne < 21)
    {
        if (etat < 0)
        {
            TFT.line(last_ligne, 6, last_ligne, 19, Black);
        }
        couleur = 0xF800;
        TFT.line(ligne, 6, ligne, 19, couleur);
    }
    else if (ligne > 20 && ligne < 36)
    {
        if (etat < 0)
        {
            TFT.line(last_ligne, 6, last_ligne, 19, Black);
        }
        couleur = 0xFFE0;
        TFT.line(ligne, 6, ligne, 19, couleur);
    }
    else if (ligne > 35 && ligne < 50)
    {
        if (etat < 0 && last_ligne == 50)
        {
            TFT.line(last_ligne, 11, last_ligne, 14, Black);
        }
        else if (etat < 0)
        {
            TFT.line(last_ligne, 6, last_ligne, 19, Black);
        }
        couleur = 0x07E0;
        TFT.line(ligne, 6, ligne, 19, couleur);
    }
    else if (ligne > 49 && ligne < 55)
    {
        if (etat < 0)
        {
            TFT.line(last_ligne, 11, last_ligne, 14, Black);
        }
        couleur = 0x07E0;
        TFT.line(ligne, 11, ligne, 14, couleur);
    }
}

void DisplayInterface::BatteryLow()
{
    TFT.fillrect(10, 5, 55, 20, Black);
}

void DisplayInterface::Batterie(int8_t batterie)
{
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

void DisplayInterface::Test(uint8_t variable)
{
    TFT.rect(240, 180, 310, 200, White);
    TFT.set_font((unsigned char *)Arial12x12);
    TFT.foreground(White);
    TFT.locate(252, 185);
    TFT.printf("Test %u", variable);
}

void DisplayInterface::Menu()
{
    DisplayInterface::LogoOff();
    DisplayInterface::BtnMenuAppuye();
    DisplayInterface::BtnVitesseNonAppuye();
    DisplayInterface::BtnModesNonAppuye();
    DisplayInterface::BtnFermer();
    

}

void DisplayInterface::Vitesse()
{
    DisplayInterface::FermerMode();
    DisplayInterface::BtnModesNonAppuye();
    DisplayInterface::BtnVitesseAppuye();
    DisplayInterface::BtnVitesse1NonAppuye();
    DisplayInterface::BtnVitesse2NonAppuye();
    DisplayInterface::BtnVitesse3NonAppuye();
}

void DisplayInterface::Modes()
{
    DisplayInterface::FermerVitesse();
    DisplayInterface::BtnVitesseNonAppuye();
    DisplayInterface::BtnModesAppuye();
    DisplayInterface::BtnLibreNonAppuye();
    DisplayInterface::BtnEnregistrerNonAppuye();
    DisplayInterface::BtnEtenduNonAppuye();
    DisplayInterface::BtnDebogageNonAppuye();
}

void DisplayInterface::Libre()
{
    DisplayInterface::BtnLibreAppuye();
    DisplayInterface::BtnEnregistrerNonAppuye();
    DisplayInterface::BtnEtenduNonAppuye();
    DisplayInterface::BtnDebogageNonAppuye();
    DisplayInterface::BtnChoisir();
}

void DisplayInterface::Enregistrer()
{
    DisplayInterface::BtnLibreNonAppuye();
    DisplayInterface::BtnEnregistrerAppuye();
    DisplayInterface::BtnEtenduNonAppuye();
    DisplayInterface::BtnDebogageNonAppuye();
    DisplayInterface::BtnChoisir();
}

void DisplayInterface::Etendu()
{
    DisplayInterface::BtnLibreNonAppuye();
    DisplayInterface::BtnEnregistrerNonAppuye();
    DisplayInterface::BtnEtenduAppuye();
    DisplayInterface::BtnDebogageNonAppuye();
    DisplayInterface::BtnChoisir();
}

void DisplayInterface::Debogage()
{
    DisplayInterface::BtnLibreNonAppuye();
    DisplayInterface::BtnEnregistrerNonAppuye();
    DisplayInterface::BtnEtenduNonAppuye();
    DisplayInterface::BtnDebogageAppuye();
    DisplayInterface::BtnChoisir();
}

void DisplayInterface::Vitesse1()
{
    DisplayInterface::BtnVitesse1Appuye();
    DisplayInterface::BtnVitesse2NonAppuye();
    DisplayInterface::BtnVitesse3NonAppuye();
    DisplayInterface::BtnChoisir();
}
void DisplayInterface::Vitesse2()
{
    DisplayInterface::BtnVitesse1NonAppuye();
    DisplayInterface::BtnVitesse2Appuye();
    DisplayInterface::BtnVitesse3NonAppuye();
    DisplayInterface::BtnChoisir();
}
void DisplayInterface::Vitesse3()
{
    DisplayInterface::BtnVitesse1NonAppuye();
    DisplayInterface::BtnVitesse2NonAppuye();
    DisplayInterface::BtnVitesse3Appuye();
    DisplayInterface::BtnChoisir();
}
void DisplayInterface::Fin()
{
    DisplayInterface::Fermer();
    DisplayInterface::BtnMenuNonAppuye();
    DisplayInterface::LogoOn();
}

void DisplayInterface::LogoOn()
{
    //Base
    TFT.line(70, 225, 250, 225, White);
    TFT.line(95, 224, 225, 224, White);
    TFT.line(96, 223, 224, 223, White);
    TFT.line(97, 222, 223, 222, White);
    TFT.line(98, 221, 222, 221, White);

    //Grosse base
    TFT.line(99, 217, 222, 217, White);
    TFT.line(100, 216, 221, 216, White);
    TFT.line(100, 215, 221, 215, White);
    TFT.line(101, 214, 220, 214, White);
    TFT.line(101, 213, 220, 213, White);
    TFT.line(102, 212, 219, 212, White);
    TFT.line(102, 211, 219, 211, White);
    TFT.line(103, 210, 218, 210, White);
    TFT.line(103, 209, 218, 209, White);
    TFT.line(104, 208, 217, 208, White);
    TFT.line(104, 207, 217, 207, White);
    TFT.line(105, 206, 216, 206, White);
    TFT.line(105, 205, 216, 205, White);
    //
    TFT.line(119, 204, 161, 204, White);
    TFT.line(119, 203, 161, 203, White);
    TFT.line(119, 202, 160, 202, White);
    TFT.line(119, 201, 160, 201, White);
    //
    TFT.line(120, 200, 160, 200, White);
    TFT.line(121, 199, 160, 199, White);
    TFT.line(122, 198, 159, 198, White);
    TFT.line(122, 197, 159, 197, White);
    TFT.line(123, 196, 159, 196, White);
    TFT.line(124, 195, 158, 195, White);
    TFT.line(125, 194, 158, 194, White);
    TFT.line(126, 193, 158, 193, White);
    TFT.line(127, 192, 157, 192, White);
    TFT.line(127, 191, 157, 191, White);
    //
    TFT.line(128, 190, 157, 190, White);
    TFT.line(129, 189, 157, 189, White);
    TFT.line(130, 188, 156, 188, White);
    TFT.line(131, 187, 156, 187, White);
    TFT.line(131, 186, 156, 186, White);
    TFT.line(131, 185, 156, 185, White);
    TFT.line(131, 184, 156, 184, White);
    TFT.line(131, 183, 156, 183, White);
    TFT.line(131, 182, 155, 182, White);
    TFT.line(130, 181, 155, 181, White);
    //
    TFT.line(130, 180, 155, 180, White);
    TFT.line(129, 179, 155, 179, White);
    TFT.line(129, 178, 154, 178, White);
    TFT.line(128, 177, 154, 177, White);
    TFT.line(128, 176, 154, 176, White);
    TFT.line(127, 175, 153, 175, White);
    TFT.line(127, 174, 153, 174, White);
    TFT.line(127, 173, 152, 173, White);
    TFT.line(126, 172, 151, 172, White);
    TFT.line(126, 171, 151, 171, White);
    //
    TFT.line(125, 170, 150, 170, White);
    TFT.line(124, 169, 149, 169, White);
    TFT.line(124, 168, 148, 168, White);
    TFT.line(123, 167, 147, 167, White);
    TFT.line(123, 166, 146, 166, White);
    TFT.line(122, 165, 146, 165, White);
    TFT.line(122, 164, 146, 164, White);
    TFT.line(121, 163, 146, 163, White);
    TFT.line(121, 162, 146, 162, White);
    TFT.line(120, 161, 146, 161, White);
    //
    TFT.line(119, 160, 145, 160, White);
    TFT.line(119, 159, 145, 159, White);
    TFT.line(119, 158, 145, 158, White);
    TFT.line(124, 157, 145, 157, White);
    TFT.line(126, 156, 145, 156, White);
    TFT.line(126, 155, 145, 155, White);
    TFT.line(127, 154, 145, 154, White);
    TFT.line(128, 153, 145, 153, White);
    TFT.line(129, 152, 145, 152, White);
    TFT.line(130, 151, 145, 151, White);
    //
    TFT.line(131, 150, 137, 150, White);
    TFT.line(139, 150, 145, 150, White);
    TFT.line(132, 149, 136, 149, White);
    TFT.line(141, 149, 145, 149, White);
    TFT.line(133, 148, 137, 148, White);
    TFT.line(142, 148, 145, 148, White);
    TFT.line(134, 147, 138, 147, White);
    TFT.line(135, 146, 139, 146, White);
    TFT.line(135, 145, 140, 145, White);
    TFT.line(136, 144, 244, 144, White);
    TFT.line(137, 143, 244, 143, White);
    TFT.line(138, 142, 244, 142, White);
    TFT.line(139, 141, 244, 141, White);
    TFT.line(140, 140, 244, 140, White);

    //Support Base
    TFT.line(163, 200, 189, 200, White);
    TFT.fillrect(185, 170, 189, 190, White);
    TFT.line(163, 199, 189, 199, White);
    TFT.line(163, 198, 189, 198, White);
    TFT.line(162, 197, 189, 197, White);
    TFT.line(162, 196, 189, 196, White);
    TFT.line(162, 195, 189, 195, White);
    TFT.line(161, 194, 189, 194, White);
    TFT.line(161, 193, 189, 193, White);
    TFT.line(161, 192, 189, 192, White);
    TFT.line(160, 191, 189, 191, White);
    //
    TFT.line(160, 190, 171, 190, White);
    TFT.line(160, 189, 171, 189, White);
    TFT.line(160, 188, 171, 188, White);
    TFT.line(159, 187, 171, 187, White);
    TFT.line(159, 186, 171, 186, White);
    TFT.line(159, 185, 171, 185, White);
    TFT.line(159, 184, 171, 184, White);
    TFT.line(159, 183, 171, 183, White);
    TFT.line(159, 182, 171, 182, White);
    TFT.line(158, 181, 171, 181, White);
    //
    TFT.line(158, 180, 171, 180, White);
    TFT.line(158, 179, 171, 179, White);
    TFT.line(158, 178, 171, 178, White);
    TFT.line(157, 177, 171, 177, White);
    TFT.line(157, 176, 171, 176, White);
    TFT.line(157, 175, 171, 175, White);
    TFT.line(156, 174, 171, 174, White);
    TFT.line(156, 173, 171, 173, White);
    TFT.line(155, 172, 171, 172, White);
    TFT.line(154, 171, 171, 171, White);
    //
    TFT.line(154, 170, 171, 170, White);
    TFT.line(153, 169, 171, 169, White);
    TFT.line(152, 168, 171, 168, White);
    TFT.line(151, 167, 171, 167, White);
    TFT.line(150, 166, 171, 166, White);
    TFT.line(178, 166, 196, 166, White);
    TFT.line(149, 165, 171, 165, White);
    TFT.line(177, 165, 197, 165, White);
    TFT.line(149, 164, 171, 164, White);
    TFT.line(176, 164, 198, 164, White);
    TFT.line(149, 163, 171, 163, White);
    TFT.line(175, 163, 199, 163, White);
    TFT.line(149, 162, 171, 162, White);
    TFT.line(174, 162, 200, 162, White);
    TFT.line(149, 161, 171, 161, White);
    TFT.line(173, 161, 201, 161, White);
    //
    TFT.line(150, 160, 207, 160, White);
    TFT.line(150, 159, 208, 159, White);
    TFT.line(194, 158, 209, 158, White);
    TFT.line(194, 157, 210, 157, White);
    TFT.line(194, 156, 211, 156, White);
    TFT.line(194, 155, 212, 155, White);
    TFT.fillrect(151, 148, 241, 154, White);

    //rectangle+table au dessu de base
      
    TFT.line(199, 135, 237, 135, White);
    TFT.line(200, 134, 237, 134, White);
    TFT.line(202, 133, 236, 133, White);
    TFT.line(204, 132, 236, 132, White);

    TFT.fillrect(187, 123, 245, 129, White);

    TFT.line(136, 129, 156, 129, White);
    TFT.line(136, 128, 156, 128, White);
    TFT.line(135, 127, 156, 127, White);
    TFT.line(135, 126, 156, 126, White);
    TFT.line(135, 125, 156, 125, White);
    TFT.line(134, 124, 156, 124, White);
    TFT.line(133, 123, 156, 123, White);

    TFT.fillrect(158, 120, 185, 122, White);

    TFT.fillrect(161, 117, 182, 118, White);

    TFT.line(148, 115, 192, 115, White);
    TFT.line(147, 114, 193, 114, White);
    TFT.line(147, 113, 193, 113, White);
    TFT.line(147, 112, 192, 112, White);
    TFT.line(149, 111, 190, 111, White);
    TFT.line(154, 110, 156, 110, White);
    TFT.line(154, 109, 156, 109, White);
    TFT.line(154, 108, 156, 108, White);
    TFT.line(154, 107, 156, 107, White);
    TFT.line(153, 106, 156, 106, White);
    TFT.line(152, 105, 157, 105, White);
    TFT.line(153, 104, 156, 104, White);

    TFT.line(172, 105, 173, 105, White);
    TFT.line(172, 104, 173, 104, White);
    TFT.line(171, 103, 174, 103, White);
    TFT.line(171, 102, 174, 102, White);

    TFT.line(169, 99, 176, 99, White);
    TFT.line(169, 98, 176, 98, White);
    TFT.line(169, 97, 176, 97, White);
    TFT.line(170, 96, 175, 96, White);
    TFT.line(170, 95, 175, 95, White);
    TFT.line(169, 94, 176, 94, White);
    TFT.line(169, 93, 176, 93, White);

    TFT.line(163, 90, 182, 90, White);
    TFT.line(162, 89, 183, 89, White);
    TFT.line(161, 88, 184, 88, White);
    TFT.line(168, 87, 177, 87, White);
    TFT.line(161, 87, 164, 87, White);
    TFT.line(181, 87, 184, 87, White);
    TFT.fillrect(168, 69, 177, 88, White);
    TFT.fillrect(161, 71, 163, 86, White);
    TFT.fillrect(182, 71, 184, 86, White);
    TFT.line(160, 70, 163, 70, White);
    TFT.line(182, 70, 185, 70, White);
    TFT.line(158, 69, 162, 69, White);
    TFT.line(183, 69, 187, 69, White);
    TFT.line(158, 68, 162, 68, White);
    TFT.line(168, 68, 170, 68, White);
    TFT.line(175, 68, 177, 68, White);
    TFT.line(183, 68, 187, 68, White);
    TFT.line(158, 67, 161, 67, White);
    TFT.line(166, 67, 168, 67, White);
    TFT.line(177, 67, 179, 67, White);
    TFT.line(184, 67, 187, 67, White);
    TFT.line(158, 66, 161, 66, White);
    TFT.line(165, 66, 166, 66, White);
    TFT.line(179, 66, 180, 66, White);
    TFT.line(184, 66, 187, 66, White);
    TFT.line(158, 65, 161, 65, White);
    TFT.line(164, 65, 165, 65, White);
    TFT.line(180, 65, 181, 65, White);
    TFT.line(184, 65, 187, 65, White);
    TFT.line(158, 64, 161, 64, White);
    TFT.line(164, 64, 164, 64, White);
    TFT.line(181, 64, 181, 64, White);
    TFT.line(184, 64, 187, 64, White);
    TFT.line(159, 63, 161, 63, White);
    TFT.line(184, 63, 186, 63, White);
    TFT.line(160, 62, 161, 62, White);
    TFT.line(184, 62, 185, 62, White);

    TFT.line(169, 65, 175, 65, White);
    TFT.line(168, 64, 176, 64, White);
    TFT.line(167, 63, 177, 63, White);
    TFT.line(166, 62, 178, 62, White);
    TFT.line(166, 61, 170, 61, White);
    TFT.line(175, 61, 179, 61, White);
    //
    TFT.line(165, 60, 169, 60, White);
    TFT.line(176, 60, 180, 60, White);
    TFT.line(165, 59, 167, 59, White);
    TFT.line(171, 59, 173, 59, White);
    TFT.line(177, 59, 180, 59, White);
    TFT.line(164, 58, 166, 58, White);
    TFT.line(170, 58, 174, 58, White);
    TFT.line(178, 58, 180, 58, White);
    TFT.line(164, 57, 165, 57, White);
    TFT.line(169, 57, 175, 57, White);
    TFT.line(179, 57, 181, 57, White);
    TFT.line(164, 56, 165, 56, White);
    TFT.line(168, 56, 176, 56, White);
    TFT.line(179, 56, 181, 56, White);
    TFT.line(163, 55, 165, 55, White);
    TFT.line(168, 55, 176, 55, White);
    TFT.line(179, 55, 181, 55, White);
    TFT.line(163, 54, 165, 54, White);
    TFT.line(169, 54, 175, 54, White);
    TFT.line(179, 54, 181, 54, White);
    TFT.line(162, 53, 166, 53, White);
    TFT.line(170, 53, 174, 53, White);
    TFT.line(178, 53, 181, 53, White);
    TFT.line(162, 52, 167, 52, White);
    TFT.line(171, 52, 173, 52, White);
    TFT.line(178, 52, 181, 52, White);
    TFT.line(161, 51, 167, 51, White);
    TFT.line(177, 51, 181, 51, White);
    //
    TFT.line(161, 50, 170, 50, White);
    TFT.line(176, 50, 181, 50, White);
    TFT.line(161, 49, 170, 49, White);
    TFT.line(173, 49, 181, 49, White);
    TFT.line(161, 48, 170, 48, White);
    TFT.line(173, 48, 181, 48, White);
    TFT.line(161, 47, 170, 47, White);
    TFT.line(173, 47, 182, 47, White);
    TFT.line(161, 46, 170, 46, White);
    TFT.line(173, 46, 182, 46, White);
    TFT.line(161, 45, 170, 45, White);
    TFT.line(173, 45, 182, 45, White);
    TFT.line(161, 44, 170, 44, White);
    TFT.line(173, 44, 182, 44, White);
    TFT.line(161, 43, 170, 43, White);
    TFT.line(173, 43, 182, 43, White);
    TFT.line(161, 42, 170, 42, White);
    TFT.line(173, 42, 182, 42, White);
    TFT.line(161, 41, 170, 41, White);
    TFT.line(173, 41, 182, 41, White);
    //
    TFT.line(161, 40, 170, 40, White);
    TFT.line(173, 40, 182, 40, White);
    TFT.line(161, 39, 170, 39, White);
    TFT.line(173, 39, 182, 39, White);
    TFT.line(161, 38, 170, 38, White);
    TFT.line(173, 38, 182, 38, White);
    TFT.line(161, 37, 170, 37, White);
    TFT.line(173, 37, 182, 37, White);
    TFT.line(161, 36, 170, 36, White);
    TFT.line(173, 36, 182, 36, White);
    TFT.line(162, 35, 170, 35, White);
    TFT.line(173, 35, 182, 35, White);
    TFT.line(162, 34, 170, 34, White);
    TFT.line(173, 34, 182, 34, White);
    TFT.line(163, 33, 170, 33, White);
    TFT.line(173, 33, 182, 33, White);
    TFT.line(163, 32, 170, 32, White);
    TFT.line(173, 32, 182, 32, White);
    TFT.line(163, 31, 170, 31, White);
    TFT.line(173, 31, 182, 31, White);
    //
    TFT.line(163, 30, 170, 30, White);
    TFT.line(173, 30, 182, 30, White);
    TFT.line(163, 29, 170, 29, White);
    TFT.line(173, 29, 182, 29, White);
    TFT.line(163, 28, 169, 28, White);
    TFT.line(173, 28, 182, 28, White);
    TFT.line(162, 27, 169, 27, White);
    TFT.line(173, 27, 181, 27, White);
    TFT.line(161, 26, 169, 26, White);
    TFT.line(173, 26, 180, 26, White);
    TFT.line(161, 25, 169, 25, White);
    TFT.line(172, 25, 180, 25, White);
    TFT.line(160, 24, 168, 24, White);
    TFT.line(171, 24, 179, 24, White);
    TFT.line(159, 23, 167, 23, White);
    TFT.line(171, 23, 178, 23, White);
    TFT.line(158, 22, 167, 22, White);
    TFT.line(170, 22, 178, 22, White);
    TFT.line(157, 21, 166, 21, White);
    TFT.line(170, 21, 177, 21, White);
    //
    TFT.line(158, 20, 165, 20, White);
    TFT.line(169, 20, 176, 20, White);
    TFT.line(160, 19, 165, 19, White);
    TFT.line(168, 19, 175, 19, White);
    TFT.line(161, 18, 164, 18, White);
    TFT.line(169, 18, 175, 18, White);
    TFT.line(163, 17, 164, 17, White);
    TFT.line(170, 17, 174, 17, White);
    TFT.line(171, 16, 174, 16, White);
    TFT.line(172, 15, 173, 15, White);
}
void DisplayInterface::LogoOff()
{
    TFT.fillrect(70, 10, 200, 120, Black);
    TFT.fillrect(70, 120, 250, 230, Black);

}