#include "stdio.h"
#include "mbed.h"
#include "TouchScreen.h"
#include "DisplayInterface.h"

// Pins pour l'interface tactile
#define Xp PC_3
#define Yp PC_2
#define Xn PC_1
#define Yn PC_0

// Joysticks
AnalogIn X1(PB_1);
AnalogIn Y1(PC_5);
AnalogIn X2(PA_0);
AnalogIn Y2(PA_1);

// Boutons de controle
DigitalIn pince(PA_3);
DigitalIn ctrl(PB_15);

// Valeurs de l'ecran
uint16_t positionX;
uint16_t positionY;

// trame
uint8_t buff[10];

// Flags
bool flag_menu = false;    // flag pour indiquer si le bouton "Menu" a ete appuye
bool flag_vitesse = false; // flag pour indiquer si le bouton "Vitesse" a ete appuye
bool flag_modes = false;   // flag pour indiquer si le bouton "Modes" a ete appuye

uint8_t vitesse_moteur;    // vitesse des mvt_robot qui sera transmise
uint8_t direction_stepper; // direction de rotation du moteur transmise
enum
{
  demarrage,
  attente_appui,
  detection_appui,
  menu,
  vitesse,
  modes,
  libre,
  enregistrer,
  etendu,
  debogage,
  selection_vitesse1,
  selection_vitesse2,
  selection_vitesse3,
  ok,
  fermer,
  servo,
  mvt_robot
};
uint8_t etat = demarrage;
DisplayInterface Ecran(PA_7, PA_6, PA_5, PA_8, PA_10, PA_9); // mosi, miso, sclk, cs, reset, dc
TouchScreen Touch(Xp, Xn, Yp, Yn);                           // PinName Xp, PinName Xn, PinName Yp, PinName Yn

BufferedSerial pc(PB_6, PB_7); // USBTX et USBRX sont les broches de communication série sur la carte Nucleo STM32F072RB
uint8_t data[10];              // tableau de donnee transmis par BT
int main()
{

  buff[0] = '#';
  buff[1] = '@';
  buff[2] = '+';
  buff[8] = '?';
  buff[9] = '%';

  pc.set_baud(115200); // instancier baud-rate pour la communication BT
  while (1)
  {
    switch (etat)
    {
    // initialisation de l'ecran d'acceuil
    case demarrage:
      Ecran.Demarrage();
      Ecran.BtnMenuNonAppuye();
      Ecran.BtnBatterie();
      /*TFT.background(Black);
      TFT.cls();
      TFT.set_orientation(3);
      TFT.rect(0, 0, 320, 240, Blue);
      TFT.rect(210, 10, 310, 40, White);
      TFT.set_font((unsigned char *)Arial24x23);
      TFT.foreground(Blue);
      TFT.locate(220, 15);
      TFT.printf("Menu");
      TFT.rect(10, 5, 50, 20, White);
      TFT.rect(50, 10, 55, 15, White);
      TFT.line(50, 11, 50, 14, Black);
      TFT.fillrect(11, 6, 20, 19, Red);
      TFT.fillrect(21, 6, 35, 19, Orange);
      TFT.fillrect(36, 6, 49, 19, DarkGreen);
      TFT.fillrect(50, 11, 54, 14, DarkGreen);*/

      etat = attente_appui;
      break;
    // attente d'un appui
    case attente_appui:
      if (Touch.Touch_detect())
      {
        etat = detection_appui;
      }
      if (pince == 1)
      {
        etat = mvt_robot;
        break;

      case mvt_robot:
        buff[3] = Y1.read_u16() * 0.00389106;
        buff[4] = X1.read_u16() * 0.00389106;
        buff[5] = Y2.read_u16() * 0.00389106;
        buff[6] = X2.read_u16() * 0.00389106;
        pc.write(buff, sizeof(buff));
        thread_sleep_for(250);
        etat = attente_appui;
        break;
      case servo:
        data[2] = 1;
        pc.write(data, sizeof(data));
        data[2] = 0;
        etat = attente_appui;
        break;
      // lorsque l'utilisateur appuie sur l'ecran
      case detection_appui:
        positionX = Touch.getX();                  // prendre la valeur de l'axe X
        positionY = Touch.getY();                  // prendre la valeur de l'axe Y
        printf("%d,%d\r\n", positionX, positionY); // afficher
        // si on appuie sur le bouton "Menu"
        if (positionX >= 210 && positionX <= 310 && positionY >= 10 && positionY <= 40 && flag_menu == false)
        {
          flag_menu = true; // activer le flag du bouton
          etat = menu;
        }
        // si on appuie sur le bouton "Vitesse"
        else if (positionX >= 10 && positionX <= 90 && positionY >= 50 && positionY <= 70 && flag_vitesse == false)
        {
          flag_vitesse = true; // activer le flag du bouton
          etat = vitesse;
        }
        // si on appuie sur le bouton "Modes"
        else if (positionX >= 10 && positionX <= 90 && positionY >= 80 && positionY <= 100)
        {
          flag_modes = true;
          etat = modes;
        }
        // si on appuie sur le bouton "Libre"
        else if (positionX >= 120 && positionX <= 210 && positionY >= 80 && positionY <= 100 && flag_modes == true)
        {
          etat = libre;
        }
        // si on appuie sur le bouton "Enregistrer"
        else if (positionX >= 220 && positionX <= 310 && positionY >= 80 && positionY <= 100 && flag_modes == true)
        {
          etat = enregistrer;
        }
        // si on appuie sur le bouton "Etendu"
        else if (positionX >= 120 && positionX <= 210 && positionY >= 110 && positionY <= 130 && flag_modes == true)
        {
          etat = etendu;
        }
        // si on appuie sur le bouton "Debogage"
        else if (positionX >= 220 && positionX <= 310 && positionY >= 110 && positionY <= 130 && flag_modes == true)
        {
          etat = debogage;
        }

        // si on appuie sur le bouton de la vitesse "1"
        else if (positionX >= 120 && positionX <= 140 && positionY >= 50 && positionY <= 70 && flag_vitesse == true)
        {
          etat = selection_vitesse1;
        }
        // si on appuie dur le bouton de la vitesse "2"
        else if (positionX >= 150 && positionX <= 170 && positionY >= 50 && positionY <= 70 && flag_vitesse == true)
        {
          etat = selection_vitesse2;
        }
        // si on appuie sur le bouton de la vitesse "3"
        else if (positionX >= 180 && positionX <= 200 && positionY >= 50 && positionY <= 70 && flag_vitesse == true)
        {
          etat = selection_vitesse3;
        }
        // si on appuie sur le bouton "Fermer"
        else if (positionX >= 240 && positionX <= 310 && positionY >= 210 && positionY <= 230)
        {
          etat = fermer;
        }
        // si on appuie sur le bouton "choisir"
        else if (positionX >= 240 && positionX <= 310 && positionY >= 180 && positionY <= 200)
        {
          etat = ok;
        }
        else
        {
          etat = attente_appui;
        }
        break;
      case menu:
        Ecran.BtnMenuAppuye();
        Ecran.BtnVitesseNonAppuye();
        Ecran.BtnModesNonAppuye();
        Ecran.BtnFermer();
        etat = attente_appui;
        break;
      case vitesse:
        Ecran.FermerMode();
        Ecran.BtnVitesseAppuye();
        Ecran.BtnVitesse1NonAppuye();
        Ecran.BtnVitesse2NonAppuye();
        Ecran.BtnVitesse3NonAppuye();
        etat = attente_appui;
        break;
      case modes:
        Ecran.FermerVitesse();
        Ecran.BtnModesAppuye();
        Ecran.BtnLibreNonAppuye();
        Ecran.BtnEnregistrerNonAppuye();
        Ecran.BtnEtenduNonAppuye();
        Ecran.BtnDebogageNonAppuye();
        etat = attente_appui;
        break;
      case libre:
        Ecran.BtnLibreAppuye();
        Ecran.BtnEnregistrerNonAppuye();
        Ecran.BtnEtenduNonAppuye();
        Ecran.BtnDebogageNonAppuye();
        Ecran.BtnChoisir();
        etat = attente_appui;
        break;
      case enregistrer:
        Ecran.BtnLibreNonAppuye();
        Ecran.BtnEnregistrerAppuye();
        Ecran.BtnEtenduNonAppuye();
        Ecran.BtnDebogageNonAppuye();
        Ecran.BtnChoisir();
        etat = attente_appui;
        break;
      case etendu:
        Ecran.BtnLibreNonAppuye();
        Ecran.BtnEnregistrerNonAppuye();
        Ecran.BtnEtenduAppuye();
        Ecran.BtnDebogageNonAppuye();
        Ecran.BtnChoisir();
        etat = attente_appui;
        break;
      case debogage:
        Ecran.BtnLibreNonAppuye();
        Ecran.BtnEnregistrerNonAppuye();
        Ecran.BtnEtenduNonAppuye();
        Ecran.BtnDebogageAppuye();
        Ecran.BtnChoisir();
        etat = attente_appui;
        break;
      case selection_vitesse1:
        Ecran.BtnVitesse1Appuye();
        Ecran.BtnVitesse2NonAppuye();
        Ecran.BtnVitesse3NonAppuye();
        Ecran.BtnChoisir();
        etat = attente_appui;
        break;
      case selection_vitesse2:
        Ecran.BtnVitesse1NonAppuye();
        Ecran.BtnVitesse2Appuye();
        Ecran.BtnVitesse3NonAppuye();
        Ecran.BtnChoisir();
        etat = attente_appui;
        break;
      case selection_vitesse3:
        Ecran.BtnVitesse1NonAppuye();
        Ecran.BtnVitesse2NonAppuye();
        Ecran.BtnVitesse3Appuye();
        Ecran.BtnChoisir();
        etat = attente_appui;
        break;
      case fermer:
        Ecran.Fermer();
        Ecran.BtnMenuNonAppuye();
        // baisser les flags
        flag_menu = false;
        flag_vitesse = false;
        flag_modes = false;
        etat = attente_appui;
        break;
      case ok:
        Ecran.Fermer();
        Ecran.BtnMenuNonAppuye();
        // baisser les
        flag_menu = false;
        flag_vitesse = false;
        flag_modes = false;
        etat = attente_appui;
        break;
      }
    }
  }
}