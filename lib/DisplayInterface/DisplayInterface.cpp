/*      Fichier .cpp de la librairie DisplayInterface       */
/*Cette permet de gerer l'affichage de l'ecran sans         */
/*surcharger le code principal                              */
/*Créée par Mihai Stinga                                    */

#include "DisplayInterface.h"

DisplayInterface::DisplayInterface(PinName mosi, PinName miso, PinName sclk, PinName cs, PinName reset, PinName dc)
    : TFT(mosi, miso, sclk, cs, reset, dc) {}

void DisplayInterface::BtnOn()
{
    TFT.rect(60, 100, 130, 140, Black);
    TFT.set_font((unsigned char *)Arial24x23);
    TFT.foreground(Green);
    TFT.locate(75, 110);
    TFT.printf("ON");
}
void DisplayInterface::BtnOff()
{
    TFT.rect(190, 100, 260, 140, Black);
    TFT.set_font((unsigned char *)Arial24x23);
    TFT.foreground(Red);
    TFT.locate(193, 110);
    TFT.printf("OFF");
}

void DisplayInterface::Initialisation()
{
    TFT.background(White);
    TFT.cls();
    TFT.set_orientation(3);
    TFT.rect(0, 0, 319, 240, Black);

    DisplayInterface::BtnMenuNonAppuye();
    DisplayInterface::LogoOn();
}

void DisplayInterface::BtnMenuNonAppuye()
{
    TFT.rect(210, 10, 310, 40, Black);
    TFT.rect(209, 9, 311, 41, Black);
    TFT.set_font((unsigned char *)Arial24x23);
    TFT.foreground(Black);
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

void DisplayInterface::BtnModesNonAppuye()
{
    TFT.rect(100, 60, 220, 90, Black);
    TFT.rect(99, 59, 221, 91, Black);
    TFT.set_font((unsigned char *)Arial24x23);
    TFT.foreground(Black);
    TFT.locate(105, 65);
    TFT.printf("Modes");
}
void DisplayInterface::BtnModesAppuye()
{
    TFT.rect(100, 60, 220, 90, LightGrey);
    TFT.rect(99, 59, 221, 91, LightGrey);
    TFT.set_font((unsigned char *)Arial24x23);
    TFT.foreground(LightGrey);
    TFT.locate(105, 65);
    TFT.printf("Modes");
}

void DisplayInterface::BtnLibreNonAppuye()
{
    TFT.rect(50, 110, 150, 135, Black);
    TFT.rect(49, 109, 151, 136, Black);
    TFT.set_font((unsigned char *)Arial24x23);
    TFT.foreground(Black);
    TFT.locate(60, 112);
    TFT.printf("Libre");
}
void DisplayInterface::BtnLibreAppuye()
{
    TFT.rect(50, 110, 150, 135, LightGrey);
    TFT.rect(49, 109, 151, 136, LightGrey);
    TFT.set_font((unsigned char *)Arial24x23);
    TFT.foreground(LightGrey);
    TFT.locate(60, 112);
    TFT.printf("Libre");
}
void DisplayInterface::BtnEnregistrerNonAppuye()
{
    TFT.rect(170, 110, 270, 135, Black);
    TFT.rect(169, 109, 271, 136, Black);
    TFT.set_font((unsigned char *)Arial24x23);
    TFT.foreground(Black);
    TFT.locate(175, 112);
    TFT.printf("Enreg");
}
void DisplayInterface::BtnEnregistrerAppuye()
{
    TFT.rect(170, 110, 270, 135, LightGrey);
    TFT.rect(169, 109, 271, 136, LightGrey);
    TFT.set_font((unsigned char *)Arial24x23);
    TFT.foreground(LightGrey);
    TFT.locate(175, 112);
    TFT.printf("Enreg");
}
void DisplayInterface::BtnEtenduNonAppuye()
{
    TFT.rect(50, 145, 150, 170, Black);
    TFT.rect(49, 144, 151, 171, Black);
    TFT.set_font((unsigned char *)Arial24x23);
    TFT.foreground(Black);
    TFT.locate(60, 147);
    TFT.printf("Demo");
}
void DisplayInterface::BtnEtenduAppuye()
{
    TFT.rect(50, 145, 150, 170, LightGrey);
    TFT.rect(49, 144, 151, 171, LightGrey);
    TFT.set_font((unsigned char *)Arial24x23);
    TFT.foreground(LightGrey);
    TFT.locate(60, 147);
    TFT.printf("Demo");
}
void DisplayInterface::BtnDebogageNonAppuye()
{
    TFT.rect(170, 145, 270, 170, Black);
    TFT.rect(169, 144, 271, 171, Black);
    TFT.set_font((unsigned char *)Arial24x23);
    TFT.foreground(Black);
    TFT.locate(175, 147);
    TFT.printf("Debug");
}
void DisplayInterface::BtnDebogageAppuye()
{
    TFT.rect(170, 145, 270, 170, LightGrey);
    TFT.rect(169, 144, 271, 171, LightGrey);
    TFT.set_font((unsigned char *)Arial24x23);
    TFT.foreground(LightGrey);
    TFT.locate(175, 147);
    TFT.printf("Debug");
}

void DisplayInterface::BtnEnregistrement1NonAppuye()
{
    TFT.rect(70, 130, 110, 170, Black);
    TFT.rect(69, 129, 111, 171, Black);
    TFT.set_font((unsigned char *)Arial24x23);
    TFT.foreground(Black);
    TFT.locate(80, 140);
    TFT.printf("1");
}
void DisplayInterface::BtnEnregistrement1Appuye()
{
    TFT.rect(70, 130, 110, 170, LightGrey);
    TFT.rect(69, 129, 111, 171, LightGrey);
    TFT.set_font((unsigned char *)Arial24x23);
    TFT.foreground(LightGrey);
    TFT.locate(80, 140);
    TFT.printf("1");
}
void DisplayInterface::BtnEnregistrement2NonAppuye()
{
    TFT.rect(140, 130, 180, 170, Black);
    TFT.rect(139, 129, 181, 171, Black);
    TFT.set_font((unsigned char *)Arial24x23);
    TFT.foreground(Black);
    TFT.locate(150, 140);
    TFT.printf("2");
}
void DisplayInterface::BtnEnregistrement2Appuye()
{
    TFT.rect(140, 130, 180, 170, LightGrey);
    TFT.rect(139, 129, 181, 171, LightGrey);
    TFT.set_font((unsigned char *)Arial24x23);
    TFT.foreground(LightGrey);
    TFT.locate(150, 140);
    TFT.printf("2");
}
void DisplayInterface::BtnEnregistrement3NonAppuye()
{
    TFT.rect(210, 130, 250, 170, Black);
    TFT.rect(209, 129, 251, 171, Black);
    TFT.set_font((unsigned char *)Arial24x23);
    TFT.foreground(Black);
    TFT.locate(220, 140);
    TFT.printf("3");
}
void DisplayInterface::BtnEnregistrement3Appuye()
{
    TFT.rect(210, 130, 250, 170, LightGrey);
    TFT.rect(209, 129, 251, 171, LightGrey);
    TFT.set_font((unsigned char *)Arial24x23);
    TFT.foreground(LightGrey);
    TFT.locate(220, 140);
    TFT.printf("3");
}

void DisplayInterface::EffacerAffichageEnregistrement(){
    TFT.fillrect(40, 90, 280, 171, White);
}

void DisplayInterface::BtnChoisirNonAppuye()
{
    TFT.rect(240, 190, 310, 220, Black);
    TFT.rect(239, 189, 311, 221, Black);
    TFT.set_font((unsigned char *)Arial12x12);
    TFT.foreground(Black);
    TFT.locate(252, 200);
    TFT.printf("Choisir");
}
void DisplayInterface::BtnChoisirAppuye()
{
    TFT.rect(240, 190, 310, 220, LightGrey);
    TFT.rect(239, 189, 311, 221, LightGrey);
    TFT.set_font((unsigned char *)Arial12x12);
    TFT.foreground(LightGrey);
    TFT.locate(252, 200);
    TFT.printf("Choisir");
}

void DisplayInterface::BtnDemarrerNonAppuye()
{

    TFT.set_font((unsigned char *)Arial24x23);
    TFT.foreground(Black);
    TFT.locate(90, 104);
    TFT.printf("Demarrer");
    TFT.rect(85, 100, 235, 130, Black);
    TFT.rect(84, 99, 236, 131, Black);
}
void DisplayInterface::BtnDemarrerAppuye()
{

    TFT.set_font((unsigned char *)Arial24x23);
    TFT.foreground(LightGrey);
    TFT.locate(90, 104);
    TFT.printf("Demarrer");
    TFT.rect(85, 100, 235, 130, LightGrey);
    TFT.rect(84, 99, 236, 131, LightGrey);
}
void DisplayInterface::FermerBtnDemarrer()
{
    TFT.fillrect(84, 99, 236, 131, White);
}
void DisplayInterface::FinEnregistrement()
{
    TFT.set_font((unsigned char *)Arial24x23);
    TFT.foreground(Black);
    TFT.locate(20, 100);
    TFT.printf("Enregistrement fini");
}

void DisplayInterface::BtnRejouerNonAppuye()
{
    TFT.set_font((unsigned char *)Arial24x23);
    TFT.foreground(Black);
    TFT.locate(90, 144);
    TFT.printf("Rejouer");
    TFT.rect(85, 140, 235, 170, Black);
    TFT.rect(84, 139, 236, 171, Black);
}
void DisplayInterface::BtnRejouerAppuye()
{
    TFT.set_font((unsigned char *)Arial24x23);
    TFT.foreground(LightGrey);
    TFT.locate(90, 144);
    TFT.printf("Rejouer");
    TFT.rect(85, 140, 235, 170, LightGrey);
    TFT.rect(84, 139, 236, 171, LightGrey);
}
void DisplayInterface::FermerBtnRejouer()
{
    TFT.fillrect(84, 139, 236, 171, White);
}

void DisplayInterface::Decompte0(){
    TFT.set_font((unsigned char *)Arial24x23);
    TFT.foreground(Black);
    TFT.locate(150, 180);
    TFT.printf("0");
}
void DisplayInterface::Decompte1(){
    TFT.set_font((unsigned char *)Arial24x23);
    TFT.foreground(Black);
    TFT.locate(150, 180);
    TFT.printf("1");
}
void DisplayInterface::Decompte2(){
    TFT.set_font((unsigned char *)Arial24x23);
    TFT.foreground(Black);
    TFT.locate(150, 180);
    TFT.printf("2");
}
void DisplayInterface::Decompte3(){
    TFT.set_font((unsigned char *)Arial24x23);
    TFT.foreground(Black);
    TFT.locate(150, 180);
    TFT.printf("3");
}
void DisplayInterface::Decompte4(){
    TFT.set_font((unsigned char *)Arial24x23);
    TFT.foreground(Black);
    TFT.locate(150, 180);
    TFT.printf("4");
}
void DisplayInterface::Decompte5(){
    TFT.set_font((unsigned char *)Arial24x23);
    TFT.foreground(Black);
    TFT.locate(150, 180);
    TFT.printf("5");
}
void DisplayInterface::Decompte6(){
    TFT.set_font((unsigned char *)Arial24x23);
    TFT.foreground(Black);
    TFT.locate(150, 180);
    TFT.printf("6");
}
void DisplayInterface::Decompte7(){
    TFT.set_font((unsigned char *)Arial24x23);
    TFT.foreground(Black);
    TFT.locate(150, 180);
    TFT.printf("7");
}
void DisplayInterface::Decompte8(){
    TFT.set_font((unsigned char *)Arial24x23);
    TFT.foreground(Black);
    TFT.locate(150, 180);
    TFT.printf("8");
}
void DisplayInterface::Decompte9(){
    TFT.set_font((unsigned char *)Arial24x23);
    TFT.foreground(Black);
    TFT.locate(150, 180);
    TFT.printf("9");
}
void DisplayInterface::EffacerDecompte(){
    TFT.fillrect(150,180,175, 210, White);
}

void DisplayInterface::AffichageLibre()
{
    TFT.set_font((unsigned char *)Arial24x23);
    TFT.foreground(Black);
    TFT.locate(80, 60);
    TFT.printf("Mode: Libre");
}
void DisplayInterface::AffichageEnregistrer()
{
    TFT.set_font((unsigned char *)Arial24x23);
    TFT.foreground(Black);
    TFT.locate(30, 60);
    TFT.printf("Mode: Enregistrer");
    TFT.foreground(Black);
    TFT.locate(40, 90);
    TFT.printf("Enregistrement:");

    /*DisplayInterface::BtnEnregistrement1NonAppuye();
    DisplayInterface::BtnEnregistrement2NonAppuye();
    DisplayInterface::BtnEnregistrement3NonAppuye();*/
    // DisplayInterface::BtnDemarrerNonAppuye();
    // DisplayInterface::BtnRejouerNonAppuye();
}
void DisplayInterface::EffacerEnregistrement(){
    TFT.fillrect(40, 90, 280, 120, White);
}
void DisplayInterface::AffichageDemo()
{
    TFT.set_font((unsigned char *)Arial24x23);
    TFT.foreground(Black);
    TFT.locate(80, 60);
    TFT.printf("Mode: Demo");
}
void DisplayInterface::AffichageDebug()
{
    TFT.set_font((unsigned char *)Arial24x23);
    TFT.foreground(Black);
    TFT.locate(80, 60);
    TFT.printf("Mode: Debug");
}

void DisplayInterface::IconeBatterie(int8_t batterie, uint8_t ligne)
{
    TFT.rect(10, 5, 50, 20, Black);
    TFT.rect(50, 10, 55, 15, Black);
    TFT.line(50, 11, 50, 14, LightGrey);

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
    TFT.fillrect(10, 5, 55, 20, White);
}

void DisplayInterface::EffacerEcran()
{
    TFT.fillrect(60, 10, 200, 50, White);
    TFT.fillrect(10, 50, 315, 235, White);
}

void DisplayInterface::Menu()
{
    // DisplayInterface::LogoOff();
    DisplayInterface::EffacerEcran();
    DisplayInterface::BtnMenuAppuye();
    DisplayInterface::BtnModesNonAppuye();
}
void DisplayInterface::FermerMenu()
{
    DisplayInterface::EffacerEcran();
    DisplayInterface::BtnMenuNonAppuye();
    DisplayInterface::LogoOn();
}

// Controler des appuies des modes
void DisplayInterface::Modes()
{
    DisplayInterface::BtnModesAppuye();
    DisplayInterface::BtnLibreNonAppuye();
    DisplayInterface::BtnEnregistrerNonAppuye();
    DisplayInterface::BtnEtenduNonAppuye();
    DisplayInterface::BtnDebogageNonAppuye();
}
void DisplayInterface::FermerModes(){
    DisplayInterface::BtnModesNonAppuye();
    TFT.fillrect(49, 109, 271, 171, White);
}
void DisplayInterface::Libre()
{
    DisplayInterface::BtnLibreAppuye();
    DisplayInterface::BtnEnregistrerNonAppuye();
    DisplayInterface::BtnEtenduNonAppuye();
    DisplayInterface::BtnDebogageNonAppuye();
    DisplayInterface::BtnChoisirNonAppuye();
}
void DisplayInterface::Enregistrer()
{
    DisplayInterface::BtnLibreNonAppuye();
    DisplayInterface::BtnEnregistrerAppuye();
    DisplayInterface::BtnEtenduNonAppuye();
    DisplayInterface::BtnDebogageNonAppuye();
    DisplayInterface::BtnChoisirNonAppuye();
}
void DisplayInterface::Demo()
{
    DisplayInterface::BtnLibreNonAppuye();
    DisplayInterface::BtnEnregistrerNonAppuye();
    DisplayInterface::BtnEtenduAppuye();
    DisplayInterface::BtnDebogageNonAppuye();
    DisplayInterface::BtnChoisirNonAppuye();
}
void DisplayInterface::Debogage()
{
    DisplayInterface::BtnLibreNonAppuye();
    DisplayInterface::BtnEnregistrerNonAppuye();
    DisplayInterface::BtnEtenduNonAppuye();
    DisplayInterface::BtnDebogageAppuye();
    DisplayInterface::BtnChoisirNonAppuye();
}

void DisplayInterface::Choisir()
{
    DisplayInterface::BtnChoisirAppuye();
    thread_sleep_for(200);
    DisplayInterface::EffacerEcran();
    DisplayInterface::BtnMenuNonAppuye();
}

void DisplayInterface::Test(uint8_t variable)
{
    TFT.rect(240, 180, 310, 200, Black);
    TFT.set_font((unsigned char *)Arial12x12);
    TFT.foreground(Black);
    TFT.locate(252, 185);
    TFT.printf("Test %u", variable);
}

void DisplayInterface::LogoOff()
{
    TFT.fillrect(70, 10, 200, 80, White);

    TFT.fillrect(70, 80, 250, 230, White);
}
void DisplayInterface::LogoOn()
{
    // Base
    TFT.line(70, 225, 250, 225, Black);
    TFT.line(95, 224, 225, 224, Black);
    TFT.line(96, 223, 224, 223, Black);
    TFT.line(97, 222, 223, 222, Black);
    TFT.line(98, 221, 222, 221, Black);

    // Grosse base
    TFT.line(99, 217, 222, 217, Black);
    TFT.line(100, 216, 221, 216, Black);
    TFT.line(100, 215, 221, 215, Black);
    TFT.line(101, 214, 220, 214, Black);
    TFT.line(101, 213, 220, 213, Black);
    TFT.line(102, 212, 219, 212, Black);
    TFT.line(102, 211, 219, 211, Black);
    TFT.line(103, 210, 218, 210, Black);
    TFT.line(103, 209, 218, 209, Black);
    TFT.line(104, 208, 217, 208, Black);
    TFT.line(104, 207, 217, 207, Black);
    TFT.line(105, 206, 216, 206, Black);
    TFT.line(105, 205, 216, 205, Black);
    //
    TFT.line(119, 204, 161, 204, Black);
    TFT.line(119, 203, 161, 203, Black);
    TFT.line(119, 202, 160, 202, Black);
    TFT.line(119, 201, 160, 201, Black);
    //
    TFT.line(120, 200, 160, 200, Black);
    TFT.line(121, 199, 160, 199, Black);
    TFT.line(122, 198, 159, 198, Black);
    TFT.line(122, 197, 159, 197, Black);
    TFT.line(123, 196, 159, 196, Black);
    TFT.line(124, 195, 158, 195, Black);
    TFT.line(125, 194, 158, 194, Black);
    TFT.line(126, 193, 158, 193, Black);
    TFT.line(127, 192, 157, 192, Black);
    TFT.line(127, 191, 157, 191, Black);
    //
    TFT.line(128, 190, 157, 190, Black);
    TFT.line(129, 189, 157, 189, Black);
    TFT.line(130, 188, 156, 188, Black);
    TFT.line(131, 187, 156, 187, Black);
    TFT.line(131, 186, 156, 186, Black);
    TFT.line(131, 185, 156, 185, Black);
    TFT.line(131, 184, 156, 184, Black);
    TFT.line(131, 183, 156, 183, Black);
    TFT.line(131, 182, 155, 182, Black);
    TFT.line(130, 181, 155, 181, Black);
    //
    TFT.line(130, 180, 155, 180, Black);
    TFT.line(129, 179, 155, 179, Black);
    TFT.line(129, 178, 154, 178, Black);
    TFT.line(128, 177, 154, 177, Black);
    TFT.line(128, 176, 154, 176, Black);
    TFT.line(127, 175, 153, 175, Black);
    TFT.line(127, 174, 153, 174, Black);
    TFT.line(127, 173, 152, 173, Black);
    TFT.line(126, 172, 151, 172, Black);
    TFT.line(126, 171, 151, 171, Black);
    //
    TFT.line(125, 170, 150, 170, Black);
    TFT.line(124, 169, 149, 169, Black);
    TFT.line(124, 168, 148, 168, Black);
    TFT.line(123, 167, 147, 167, Black);
    TFT.line(123, 166, 146, 166, Black);
    TFT.line(122, 165, 146, 165, Black);
    TFT.line(122, 164, 146, 164, Black);
    TFT.line(121, 163, 146, 163, Black);
    TFT.line(121, 162, 146, 162, Black);
    TFT.line(120, 161, 146, 161, Black);
    //
    TFT.line(119, 160, 145, 160, Black);
    TFT.line(119, 159, 145, 159, Black);
    TFT.line(119, 158, 145, 158, Black);
    TFT.line(124, 157, 145, 157, Black);
    TFT.line(126, 156, 145, 156, Black);
    TFT.line(126, 155, 145, 155, Black);
    TFT.line(127, 154, 145, 154, Black);
    TFT.line(128, 153, 145, 153, Black);
    TFT.line(129, 152, 145, 152, Black);
    TFT.line(130, 151, 145, 151, Black);
    //
    TFT.line(131, 150, 137, 150, Black);
    TFT.line(139, 150, 145, 150, Black);
    TFT.line(132, 149, 136, 149, Black);
    TFT.line(141, 149, 145, 149, Black);
    TFT.line(133, 148, 137, 148, Black);
    TFT.line(142, 148, 145, 148, Black);
    TFT.line(134, 147, 138, 147, Black);
    TFT.line(135, 146, 139, 146, Black);
    TFT.line(135, 145, 140, 145, Black);
    TFT.line(136, 144, 244, 144, Black);
    TFT.line(137, 143, 244, 143, Black);
    TFT.line(138, 142, 244, 142, Black);
    TFT.line(139, 141, 244, 141, Black);
    TFT.line(140, 140, 244, 140, Black);

    // Support Base
    TFT.line(163, 200, 189, 200, Black);
    TFT.fillrect(185, 170, 189, 190, Black);
    TFT.line(163, 199, 189, 199, Black);
    TFT.line(163, 198, 189, 198, Black);
    TFT.line(162, 197, 189, 197, Black);
    TFT.line(162, 196, 189, 196, Black);
    TFT.line(162, 195, 189, 195, Black);
    TFT.line(161, 194, 189, 194, Black);
    TFT.line(161, 193, 189, 193, Black);
    TFT.line(161, 192, 189, 192, Black);
    TFT.line(160, 191, 189, 191, Black);
    //
    TFT.line(160, 190, 171, 190, Black);
    TFT.line(160, 189, 171, 189, Black);
    TFT.line(160, 188, 171, 188, Black);
    TFT.line(159, 187, 171, 187, Black);
    TFT.line(159, 186, 171, 186, Black);
    TFT.line(159, 185, 171, 185, Black);
    TFT.line(159, 184, 171, 184, Black);
    TFT.line(159, 183, 171, 183, Black);
    TFT.line(159, 182, 171, 182, Black);
    TFT.line(158, 181, 171, 181, Black);
    //
    TFT.line(158, 180, 171, 180, Black);
    TFT.line(158, 179, 171, 179, Black);
    TFT.line(158, 178, 171, 178, Black);
    TFT.line(157, 177, 171, 177, Black);
    TFT.line(157, 176, 171, 176, Black);
    TFT.line(157, 175, 171, 175, Black);
    TFT.line(156, 174, 171, 174, Black);
    TFT.line(156, 173, 171, 173, Black);
    TFT.line(155, 172, 171, 172, Black);
    TFT.line(154, 171, 171, 171, Black);
    //
    TFT.line(154, 170, 171, 170, Black);
    TFT.line(153, 169, 171, 169, Black);
    TFT.line(152, 168, 171, 168, Black);
    TFT.line(151, 167, 171, 167, Black);
    TFT.line(150, 166, 171, 166, Black);
    TFT.line(178, 166, 196, 166, Black);
    TFT.line(149, 165, 171, 165, Black);
    TFT.line(177, 165, 197, 165, Black);
    TFT.line(149, 164, 171, 164, Black);
    TFT.line(176, 164, 198, 164, Black);
    TFT.line(149, 163, 171, 163, Black);
    TFT.line(175, 163, 199, 163, Black);
    TFT.line(149, 162, 171, 162, Black);
    TFT.line(174, 162, 200, 162, Black);
    TFT.line(149, 161, 171, 161, Black);
    TFT.line(173, 161, 201, 161, Black);
    //
    TFT.line(150, 160, 207, 160, Black);
    TFT.line(150, 159, 208, 159, Black);
    TFT.line(194, 158, 209, 158, Black);
    TFT.line(194, 157, 210, 157, Black);
    TFT.line(194, 156, 211, 156, Black);
    TFT.line(194, 155, 212, 155, Black);
    TFT.fillrect(151, 148, 241, 154, Black);

    // rectangle+table au dessu de base

    TFT.line(199, 135, 237, 135, Black);
    TFT.line(200, 134, 237, 134, Black);
    TFT.line(202, 133, 236, 133, Black);
    TFT.line(204, 132, 236, 132, Black);

    TFT.fillrect(187, 123, 245, 129, Black);

    TFT.line(136, 129, 156, 129, Black);
    TFT.line(136, 128, 156, 128, Black);
    TFT.line(135, 127, 156, 127, Black);
    TFT.line(135, 126, 156, 126, Black);
    TFT.line(135, 125, 156, 125, Black);
    TFT.line(134, 124, 156, 124, Black);
    TFT.line(133, 123, 156, 123, Black);

    TFT.fillrect(158, 120, 185, 122, Black);

    TFT.fillrect(161, 117, 182, 118, Black);

    TFT.line(148, 115, 192, 115, Black);
    TFT.line(147, 114, 193, 114, Black);
    TFT.line(147, 113, 193, 113, Black);
    TFT.line(147, 112, 192, 112, Black);
    TFT.line(149, 111, 190, 111, Black);
    TFT.line(154, 110, 156, 110, Black);
    TFT.line(154, 109, 156, 109, Black);
    TFT.line(154, 108, 156, 108, Black);
    TFT.line(154, 107, 156, 107, Black);
    TFT.line(153, 106, 156, 106, Black);
    TFT.line(152, 105, 157, 105, Black);
    TFT.line(153, 104, 156, 104, Black);

    // 1ere articulation
    TFT.line(112, 153, 120, 153, Black);
    TFT.line(106, 152, 121, 152, Black);
    TFT.line(105, 151, 122, 151, Black);
    TFT.line(104, 150, 123, 150, Black);
    TFT.line(103, 149, 124, 149, Black);
    TFT.line(101, 148, 125, 148, Black);
    TFT.line(100, 147, 125, 147, Black);
    TFT.line(99, 146, 126, 146, Black);
    TFT.line(98, 145, 108, 145, Black);
    TFT.line(116, 145, 127, 145, Black);
    TFT.line(97, 144, 106, 144, Black);
    TFT.line(117, 144, 128, 144, Black);
    TFT.line(97, 143, 103, 143, Black);
    TFT.line(118, 143, 128, 143, Black);
    TFT.line(96, 142, 102, 142, Black);
    TFT.line(119, 142, 129, 142, Black);
    TFT.line(95, 141, 102, 141, Black);
    TFT.line(120, 141, 130, 141, Black);
    TFT.line(95, 140, 101, 140, Black);
    TFT.line(121, 140, 130, 140, Black);
    TFT.line(94, 139, 100, 139, Black);
    TFT.line(121, 139, 130, 139, Black);
    TFT.line(94, 138, 100, 138, Black);
    TFT.line(122, 138, 130, 138, Black);
    TFT.line(94, 137, 100, 137, Black);
    TFT.line(123, 137, 130, 137, Black);
    TFT.line(93, 136, 99, 136, Black);
    TFT.line(123, 136, 130, 136, Black);
    TFT.line(93, 135, 99, 135, Black);
    TFT.line(123, 135, 130, 135, Black);
    TFT.line(93, 134, 99, 134, Black);
    TFT.line(123, 134, 130, 134, Black);
    TFT.line(93, 133, 99, 133, Black);
    TFT.line(123, 133, 130, 133, Black);
    TFT.line(93, 132, 99, 132, Black);
    TFT.line(123, 132, 130, 132, Black);
    TFT.line(92, 131, 99, 131, Black);
    TFT.line(123, 131, 130, 131, Black);
    TFT.line(92, 130, 99, 130, Black);
    TFT.line(123, 130, 130, 130, Black);
    TFT.line(92, 129, 99, 129, Black);
    TFT.line(123, 129, 130, 129, Black);
    TFT.line(92, 128, 100, 128, Black);
    TFT.line(122, 128, 130, 128, Black);
    TFT.line(92, 127, 100, 127, Black);
    TFT.line(121, 127, 130, 127, Black);
    TFT.line(92, 126, 101, 126, Black);
    TFT.line(121, 126, 129, 126, Black);
    TFT.line(92, 125, 103, 125, Black);
    TFT.line(120, 125, 128, 125, Black);
    TFT.line(92, 124, 103, 124, Black);
    TFT.line(118, 124, 128, 124, Black);
    TFT.line(93, 123, 104, 123, Black);
    TFT.line(117, 123, 128, 123, Black);
    TFT.line(94, 122, 106, 122, Black);
    TFT.line(115, 122, 128, 122, Black);
    TFT.line(94, 121, 127, 121, Black);
    TFT.line(95, 120, 126, 120, Black);
    TFT.line(96, 119, 125, 119, Black);
    TFT.line(97, 118, 124, 118, Black);
    TFT.line(98, 117, 123, 117, Black);
    TFT.line(99, 116, 122, 116, Black);
    TFT.line(100, 115, 121, 115, Black);
    TFT.line(101, 114, 117, 114, Black);
    TFT.line(102, 113, 114, 113, Black);
    TFT.line(103, 112, 112, 112, Black);
    TFT.line(104, 111, 110, 111, Black);
    // boule centrale
    TFT.line(109, 142, 113, 142, Black);
    TFT.line(108, 141, 115, 141, Black);
    TFT.line(106, 140, 116, 140, Black);
    TFT.line(105, 139, 117, 139, Black);
    TFT.line(105, 138, 118, 138, Black);
    TFT.line(104, 137, 118, 137, Black);
    TFT.line(104, 136, 119, 136, Black);
    TFT.line(103, 135, 120, 135, Black);
    TFT.line(103, 134, 120, 134, Black);
    TFT.line(103, 133, 120, 133, Black);
    TFT.line(103, 132, 120, 132, Black);
    TFT.line(103, 131, 119, 131, Black);
    TFT.line(104, 130, 119, 130, Black);
    TFT.line(104, 129, 118, 129, Black);
    TFT.line(105, 128, 118, 128, Black);
    TFT.line(106, 127, 116, 127, Black);
    TFT.line(107, 126, 115, 126, Black);
    TFT.line(108, 125, 114, 125, Black);
    TFT.line(109, 124, 113, 124, Black);

    // bras
    TFT.line(89, 121, 90, 121, Black);
    TFT.line(89, 120, 91, 120, Black);
    TFT.line(88, 119, 92, 119, Black);
    TFT.line(88, 118, 93, 118, Black);
    TFT.line(88, 117, 94, 117, Black);
    TFT.line(87, 116, 95, 116, Black);
    TFT.line(86, 115, 96, 115, Black);
    TFT.line(86, 114, 97, 114, Black);
    TFT.line(86, 113, 98, 113, Black);
    TFT.line(85, 112, 99, 112, Black);
    TFT.line(85, 111, 100, 111, Black);
    TFT.line(85, 110, 101, 110, Black);
    TFT.line(116, 110, 118, 110, Black);
    TFT.line(84, 109, 102, 109, Black);
    TFT.line(115, 109, 117, 109, Black);
    TFT.line(84, 108, 103, 108, Black);
    TFT.line(111, 108, 116, 108, Black);
    TFT.line(83, 107, 116, 107, Black);
    TFT.line(83, 106, 115, 106, Black);
    TFT.line(83, 105, 115, 105, Black);
    TFT.line(82, 104, 114, 104, Black);
    TFT.line(82, 103, 114, 103, Black);
    TFT.line(81, 102, 113, 102, Black);
    TFT.line(81, 101, 113, 101, Black);
    TFT.line(81, 100, 112, 100, Black);
    TFT.line(80, 99, 112, 99, Black);
    TFT.line(80, 98, 111, 98, Black);
    TFT.line(80, 97, 111, 97, Black);
    TFT.line(80, 96, 90, 96, Black);
    TFT.line(95, 96, 110, 96, Black);
    TFT.line(80, 95, 90, 95, Black);
    TFT.line(96, 95, 110, 95, Black);
    TFT.line(79, 94, 88, 94, Black);
    TFT.line(98, 94, 109, 94, Black);
    TFT.line(79, 93, 85, 93, Black);
    TFT.line(100, 93, 108, 93, Black);
    TFT.line(79, 92, 84, 92, Black);
    TFT.line(101, 92, 108, 92, Black);
    TFT.line(78, 91, 83, 91, Black);
    TFT.line(102, 91, 107, 91, Black);
    TFT.line(78, 90, 80, 90, Black);
    TFT.line(104, 90, 107, 90, Black);
    TFT.line(78, 89, 79, 89, Black);
    TFT.line(105, 89, 106, 89, Black);

    // Articulation 2
    TFT.line(91, 92, 94, 92, Black);
    TFT.line(90, 91, 95, 91, Black);
    TFT.line(90, 90, 96, 90, Black);
    TFT.line(88, 89, 98, 89, Black);
    TFT.line(85, 88, 101, 88, Black);
    TFT.line(84, 87, 102, 87, Black);
    TFT.line(82, 86, 103, 86, Black);
    TFT.line(81, 85, 104, 85, Black);
    TFT.line(81, 84, 105, 84, Black);
    TFT.line(79, 83, 89, 83, Black);
    TFT.line(95, 83, 105, 83, Black);
    TFT.line(79, 82, 87, 82, Black);
    TFT.line(97, 82, 106, 82, Black);
    TFT.line(79, 81, 86, 81, Black);
    TFT.line(98, 81, 106, 81, Black);
    TFT.line(79, 80, 85, 80, Black);
    TFT.line(99, 80, 108, 80, Black);
    TFT.line(78, 79, 84, 79, Black);
    TFT.line(101, 79, 108, 79, Black);
    TFT.line(78, 78, 83, 78, Black);
    TFT.line(101, 78, 108, 78, Black);
    TFT.line(78, 77, 83, 77, Black);
    TFT.line(101, 77, 108, 77, Black);
    TFT.line(78, 76, 83, 76, Black);
    TFT.line(102, 76, 108, 76, Black);
    TFT.line(78, 75, 83, 75, Black);
    TFT.line(103, 75, 108, 75, Black);
    TFT.line(78, 74, 83, 74, Black);
    TFT.line(103, 74, 108, 74, Black);
    TFT.line(78, 73, 83, 73, Black);
    TFT.line(103, 73, 108, 73, Black);
    TFT.line(78, 72, 83, 72, Black);
    TFT.line(103, 72, 108, 72, Black);
    TFT.line(78, 71, 83, 71, Black);
    TFT.line(103, 71, 108, 71, Black);
    TFT.line(78, 70, 83, 70, Black);
    TFT.line(102, 70, 108, 70, Black);
    TFT.line(78, 69, 84, 69, Black);
    TFT.line(102, 69, 108, 69, Black);
    TFT.line(78, 68, 84, 68, Black);
    TFT.line(101, 68, 108, 68, Black);
    TFT.line(79, 67, 85, 67, Black);
    TFT.line(100, 67, 108, 67, Black);
    TFT.line(80, 66, 86, 66, Black);
    TFT.line(99, 66, 107, 66, Black);
    TFT.line(80, 65, 87, 65, Black);
    TFT.line(97, 65, 107, 65, Black);
    TFT.line(81, 64, 89, 64, Black);
    TFT.line(96, 64, 106, 64, Black);
    TFT.line(81, 63, 105, 63, Black);
    TFT.line(82, 62, 104, 62, Black);
    TFT.line(83, 61, 104, 61, Black);
    TFT.line(84, 60, 103, 60, Black);
    TFT.line(85, 59, 102, 59, Black);
    TFT.line(87, 58, 100, 58, Black);
    // Boule centrale
    TFT.line(91, 80, 94, 80, Black);
    TFT.line(89, 79, 96, 79, Black);
    TFT.line(88, 78, 97, 78, Black);
    TFT.line(88, 77, 98, 77, Black);
    TFT.line(87, 76, 98, 76, Black);
    TFT.line(87, 75, 99, 75, Black);
    TFT.line(87, 74, 99, 74, Black);
    TFT.line(87, 73, 99, 73, Black);
    TFT.line(87, 72, 99, 72, Black);
    TFT.line(87, 71, 98, 71, Black);
    TFT.line(88, 70, 98, 70, Black);
    TFT.line(88, 69, 97, 69, Black);
    TFT.line(89, 68, 96, 68, Black);
    TFT.line(91, 67, 94, 67, Black);

    // Avant bras
    TFT.line(111, 68, 112, 68, Black);
    TFT.line(111, 67, 113, 67, Black);
    TFT.line(111, 66, 114, 66, Black);
    TFT.line(111, 65, 116, 65, Black);
    TFT.line(110, 64, 118, 64, Black);
    TFT.line(109, 63, 120, 63, Black);
    TFT.line(108, 62, 121, 62, Black);
    TFT.line(107, 61, 123, 61, Black);
    TFT.line(106, 60, 125, 60, Black);
    TFT.line(105, 59, 127, 59, Black);
    TFT.line(105, 58, 130, 58, Black);
    TFT.line(105, 57, 130, 57, Black);
    TFT.line(105, 56, 132, 56, Black);
    TFT.line(106, 55, 133, 55, Black);
    TFT.line(107, 54, 135, 54, Black);
    TFT.line(108, 53, 137, 53, Black);
    TFT.line(110, 52, 140, 52, Black);
    TFT.line(111, 51, 142, 51, Black);
    TFT.line(112, 50, 144, 50, Black);
    TFT.line(113, 49, 144, 49, Black);
    TFT.line(114, 48, 146, 48, Black);
    TFT.line(115, 47, 150, 47, Black);
    TFT.line(116, 46, 152, 46, Black);
    TFT.line(117, 45, 154, 45, Black);
    TFT.line(118, 44, 155, 44, Black);
    TFT.line(119, 43, 155, 43, Black);
    TFT.line(120, 42, 156, 42, Black);
    TFT.line(121, 41, 156, 41, Black);
    TFT.line(122, 40, 157, 40, Black);
    TFT.line(122, 39, 157, 39, Black);
    TFT.line(123, 38, 158, 38, Black);
    TFT.line(124, 37, 158, 37, Black);
    TFT.line(125, 36, 158, 36, Black);
    TFT.line(126, 35, 158, 35, Black);
    TFT.line(127, 34, 159, 34, Black);
    TFT.line(128, 33, 160, 33, Black);
    TFT.line(129, 32, 160, 32, Black);
    TFT.line(130, 31, 160, 31, Black);
    TFT.line(131, 30, 160, 30, Black);
    TFT.line(132, 29, 159, 29, Black);
    TFT.line(132, 28, 158, 28, Black);
    TFT.line(133, 27, 157, 27, Black);
    TFT.line(134, 26, 157, 26, Black);
    TFT.line(135, 25, 156, 25, Black);
    TFT.line(135, 24, 155, 24, Black);
    TFT.line(136, 23, 155, 23, Black);
    TFT.line(137, 22, 154, 22, Black);
    TFT.line(138, 21, 154, 21, Black);
    TFT.line(142, 20, 153, 20, Black);
    TFT.line(146, 19, 153, 19, Black);
    TFT.line(149, 18, 152, 18, Black);

    // Pince
    TFT.line(172, 105, 173, 105, Black);
    TFT.line(172, 104, 173, 104, Black);
    TFT.line(171, 103, 174, 103, Black);
    TFT.line(171, 102, 174, 102, Black);

    TFT.line(169, 99, 176, 99, Black);
    TFT.line(169, 98, 176, 98, Black);
    TFT.line(169, 97, 176, 97, Black);
    TFT.line(170, 96, 175, 96, Black);
    TFT.line(170, 95, 175, 95, Black);
    TFT.line(169, 94, 176, 94, Black);
    TFT.line(169, 93, 176, 93, Black);

    TFT.line(163, 90, 182, 90, Black);
    TFT.line(162, 89, 183, 89, Black);
    TFT.line(161, 88, 184, 88, Black);
    TFT.line(168, 87, 177, 87, Black);
    TFT.line(161, 87, 164, 87, Black);
    TFT.line(181, 87, 184, 87, Black);
    TFT.fillrect(168, 69, 177, 88, Black);
    TFT.fillrect(161, 71, 163, 86, Black);
    TFT.fillrect(182, 71, 184, 86, Black);
    TFT.line(160, 70, 163, 70, Black);
    TFT.line(182, 70, 185, 70, Black);
    TFT.line(158, 69, 162, 69, Black);
    TFT.line(183, 69, 187, 69, Black);
    TFT.line(158, 68, 162, 68, Black);
    TFT.line(168, 68, 170, 68, Black);
    TFT.line(175, 68, 177, 68, Black);
    TFT.line(183, 68, 187, 68, Black);
    TFT.line(158, 67, 161, 67, Black);
    TFT.line(166, 67, 168, 67, Black);
    TFT.line(177, 67, 179, 67, Black);
    TFT.line(184, 67, 187, 67, Black);
    TFT.line(158, 66, 161, 66, Black);
    TFT.line(165, 66, 166, 66, Black);
    TFT.line(179, 66, 180, 66, Black);
    TFT.line(184, 66, 187, 66, Black);
    TFT.line(158, 65, 161, 65, Black);
    TFT.line(164, 65, 165, 65, Black);
    TFT.line(180, 65, 181, 65, Black);
    TFT.line(184, 65, 187, 65, Black);
    TFT.line(158, 64, 161, 64, Black);
    TFT.line(164, 64, 164, 64, Black);
    TFT.line(181, 64, 181, 64, Black);
    TFT.line(184, 64, 187, 64, Black);
    TFT.line(159, 63, 161, 63, Black);
    TFT.line(184, 63, 186, 63, Black);
    TFT.line(160, 62, 161, 62, Black);
    TFT.line(184, 62, 185, 62, Black);

    TFT.line(169, 65, 175, 65, Black);
    TFT.line(168, 64, 176, 64, Black);
    TFT.line(167, 63, 177, 63, Black);
    TFT.line(166, 62, 178, 62, Black);
    TFT.line(166, 61, 170, 61, Black);
    TFT.line(175, 61, 179, 61, Black);
    //
    TFT.line(165, 60, 169, 60, Black);
    TFT.line(176, 60, 180, 60, Black);
    TFT.line(165, 59, 167, 59, Black);
    TFT.line(171, 59, 173, 59, Black);
    TFT.line(177, 59, 180, 59, Black);
    TFT.line(164, 58, 166, 58, Black);
    TFT.line(170, 58, 174, 58, Black);
    TFT.line(178, 58, 180, 58, Black);
    TFT.line(164, 57, 165, 57, Black);
    TFT.line(169, 57, 175, 57, Black);
    TFT.line(179, 57, 181, 57, Black);
    TFT.line(164, 56, 165, 56, Black);
    TFT.line(168, 56, 176, 56, Black);
    TFT.line(179, 56, 181, 56, Black);
    TFT.line(163, 55, 165, 55, Black);
    TFT.line(168, 55, 176, 55, Black);
    TFT.line(179, 55, 181, 55, Black);
    TFT.line(163, 54, 165, 54, Black);
    TFT.line(169, 54, 175, 54, Black);
    TFT.line(179, 54, 181, 54, Black);
    TFT.line(162, 53, 166, 53, Black);
    TFT.line(170, 53, 174, 53, Black);
    TFT.line(178, 53, 181, 53, Black);
    TFT.line(162, 52, 167, 52, Black);
    TFT.line(171, 52, 173, 52, Black);
    TFT.line(178, 52, 181, 52, Black);
    TFT.line(161, 51, 167, 51, Black);
    TFT.line(177, 51, 181, 51, Black);
    //
    TFT.line(161, 50, 170, 50, Black);
    TFT.line(176, 50, 181, 50, Black);
    TFT.line(161, 49, 170, 49, Black);
    TFT.line(173, 49, 181, 49, Black);
    TFT.line(161, 48, 170, 48, Black);
    TFT.line(173, 48, 181, 48, Black);
    TFT.line(161, 47, 170, 47, Black);
    TFT.line(173, 47, 182, 47, Black);
    TFT.line(161, 46, 170, 46, Black);
    TFT.line(173, 46, 182, 46, Black);
    TFT.line(161, 45, 170, 45, Black);
    TFT.line(173, 45, 182, 45, Black);
    TFT.line(161, 44, 170, 44, Black);
    TFT.line(173, 44, 182, 44, Black);
    TFT.line(161, 43, 170, 43, Black);
    TFT.line(173, 43, 182, 43, Black);
    TFT.line(161, 42, 170, 42, Black);
    TFT.line(173, 42, 182, 42, Black);
    TFT.line(161, 41, 170, 41, Black);
    TFT.line(173, 41, 182, 41, Black);
    //
    TFT.line(161, 40, 170, 40, Black);
    TFT.line(173, 40, 182, 40, Black);
    TFT.line(161, 39, 170, 39, Black);
    TFT.line(173, 39, 182, 39, Black);
    TFT.line(161, 38, 170, 38, Black);
    TFT.line(173, 38, 182, 38, Black);
    TFT.line(161, 37, 170, 37, Black);
    TFT.line(173, 37, 182, 37, Black);
    TFT.line(161, 36, 170, 36, Black);
    TFT.line(173, 36, 182, 36, Black);
    TFT.line(162, 35, 170, 35, Black);
    TFT.line(173, 35, 182, 35, Black);
    TFT.line(162, 34, 170, 34, Black);
    TFT.line(173, 34, 182, 34, Black);
    TFT.line(163, 33, 170, 33, Black);
    TFT.line(173, 33, 182, 33, Black);
    TFT.line(163, 32, 170, 32, Black);
    TFT.line(173, 32, 182, 32, Black);
    TFT.line(163, 31, 170, 31, Black);
    TFT.line(173, 31, 182, 31, Black);
    //
    TFT.line(163, 30, 170, 30, Black);
    TFT.line(173, 30, 182, 30, Black);
    TFT.line(163, 29, 170, 29, Black);
    TFT.line(173, 29, 182, 29, Black);
    TFT.line(163, 28, 169, 28, Black);
    TFT.line(173, 28, 182, 28, Black);
    TFT.line(162, 27, 169, 27, Black);
    TFT.line(173, 27, 181, 27, Black);
    TFT.line(161, 26, 169, 26, Black);
    TFT.line(173, 26, 180, 26, Black);
    TFT.line(161, 25, 169, 25, Black);
    TFT.line(172, 25, 180, 25, Black);
    TFT.line(160, 24, 168, 24, Black);
    TFT.line(171, 24, 179, 24, Black);
    TFT.line(159, 23, 167, 23, Black);
    TFT.line(171, 23, 178, 23, Black);
    TFT.line(158, 22, 167, 22, Black);
    TFT.line(170, 22, 178, 22, Black);
    TFT.line(157, 21, 166, 21, Black);
    TFT.line(170, 21, 177, 21, Black);
    //
    TFT.line(158, 20, 165, 20, Black);
    TFT.line(169, 20, 176, 20, Black);
    TFT.line(160, 19, 165, 19, Black);
    TFT.line(168, 19, 175, 19, Black);
    TFT.line(161, 18, 164, 18, Black);
    TFT.line(169, 18, 175, 18, Black);
    TFT.line(163, 17, 164, 17, Black);
    TFT.line(170, 17, 174, 17, Black);
    TFT.line(171, 16, 174, 16, Black);
    TFT.line(172, 15, 173, 15, Black);
}
