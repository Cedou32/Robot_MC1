#include "stdio.h"
#include "mbed.h"
#include "TouchScreen.h"
#include "DisplayInterface.h"
#include "TouchInterface.h"

// Pins pour l'interface tactile
#define TouchXp PC_3
#define TouchYp PC_2
#define TouchXn PC_1
#define TouchYn PC_0

//******Pins Analogiques*******//
// Joysticks
AnalogIn DroitX(PB_1);
AnalogIn DroitY(PC_5);
AnalogIn GaucheX(PA_0);
AnalogIn GaucheY(PA_1);
// Batterie
AnalogIn Batt(PA_4);

//******Pins Numeriques*******//
// Push button
DigitalIn SW1(PA_3);
DigitalIn SW2(PB_15);
// LEDS
DigitalOut LED(PC_13);

//******Variables Globales******//
// Variables pour la verification de la tension de la batterie
int8_t batterie, prevBatterie;
uint8_t ligne = 0, prevLigne = 0;
uint8_t compteur = 0;
// Variables contenant les coordonnees d'un appui
uint16_t positionX;
uint16_t positionY;
// Flags
bool flagMenu = false;  // flag pour indiquer si le bouton "Menu" a ete appuye
bool flagModes = false; // flag pour indiquer si le bouton "Modes" a ete appuye
bool flagBatterie = false;
uint8_t flagSelectionMode = 0; // flag pour indiquer la selection du mode
bool flagSelection = false;    // flag pour dire qu'une selection a ete faite
bool flagEnregistrement = false;
// Trames
uint8_t data[15];

//******Machine a etat******//
// Declaration de la variable etat
uint8_t etat = caseDemarrage;

//******Declaration des objets******//
DisplayInterface Ecran(PA_7, PA_6, PA_5, PA_8, PA_10, PA_9); // mosi, miso, sclk, cs, reset, dc
TouchScreen Touch(TouchXp, TouchXn, TouchYp, TouchYn);
BufferedSerial pc(PB_6, PB_7); // USBTX et USBRX sont les broches de communication série sur la carte Nucleo STM32F072RB
Ticker InterruptionBatterie;
Ticker InterruptionEnregistrement;

//******Fonctions pour les interruptions******//
// Verification du niveau de la batterie
void VerifBatterie()
{
  compteur = compteur + 1;
  flagBatterie = true;
}

// fonction qui arrete l'enregistrement
void FinEnregistrement()
{
  LED = !LED;
  flagEnregistrement = false;
  InterruptionEnregistrement.detach();
  flagSelectionMode = 5;
}

int main()
{
  // Attacher la fonction de lecture de la batterie
  InterruptionBatterie.attach(&VerifBatterie, 0.01);

  // Indication des valeurs de securite de la trame
  data[0] = '#';
  data[1] = '@';
  data[2] = '+';
  data[13] = '?';
  data[14] = '%';

  pc.set_baud(115200); // instancier baud-rate pour la communication BT

  while (1)
  {
    switch (etat)
    {
    // initialisation de l'ecran d'acceuil
    case caseDemarrage:
      Ecran.Initialisation(); // Initialisation de l'ecran
      Ecran.LogoOn();         // Afficher logo

      // Lecture tension de la batterie
      batterie = (Batt.read_u16() * (100.0 / 40000.0));
      ligne = batterie * 0.43 + 11;
      if (batterie > 100)
      {
        batterie = 100;
      }
      else if (batterie < 0)
      {
        batterie = 0;
      }

      // afficher l'icone de la batteire
      Ecran.IconeBatterie(batterie, ligne);
      // afficher le bouton menu
      Ecran.BtnMenuNonAppuye();
      etat = caseAttente;
      break;

    // attente d'un appui
    case caseAttente:
      if (Touch.Touch_detect())
      {
        positionX = Touch.getX(); // prendre la valeur de l'axe X
        positionY = Touch.getY(); // prendre la valeur de l'axe Y
        etat = caseDetectionAppui;
      }
      else if (flagBatterie == true)
      {
        flagBatterie = false;
        etat = caseBatterie;
      }
      else if (flagSelectionMode == 1 && flagSelection) //Mode libre choisi
      {
        etat = caseEnvoiPosition;
      }
      else if (flagSelectionMode == 4 && flagEnregistrement)
      {
        etat = caseEnvoiPosition;
      }
      else if (flagSelectionMode == 5 && !flagEnregistrement)
      {
        etat = caseFinEnregistrement;
      }
      break;

    // lorsque l'utilisateur appuie sur l'ecran
    case caseDetectionAppui:
      etat = TouchInterface::detectBouton(positionX, positionY, flagMenu, flagModes, flagSelectionMode);
      break;

    case caseBatterie:
      // lecture du niveau de la batterie et mise a jour de l'icone
      batterie = (Batt.read_u16() * (100.0 / 40000.0));
      ligne = batterie * 0.43 + 11;
      if (ligne != prevLigne)
      {
        if (batterie > 100)
        {
          batterie = 100;
        }
        else if (batterie < 0)
        {
          batterie = 0;
        }
        Ecran.BatterieInteractif(batterie, prevBatterie, ligne, prevLigne);
        prevBatterie = batterie;
        prevLigne = ligne;
      }
      etat = caseAttente;
      break;

    case caseMenu:
      flagMenu = !flagMenu; // activer le flag du bouton
      if (flagMenu == true)
      {
        Ecran.Menu();
      }
      else if (flagMenu == false)
      {
        Ecran.FermerMenu();
      }
      etat = caseAttente;
      break;

    case caseModes:
      Ecran.Modes();
      flagModes = true;
      etat = caseAttente;
      break;

    case caseLibre:
      flagSelectionMode = 1;
      Ecran.Libre();
      etat = caseAttente;
      break;

    case caseDemo:
      flagSelectionMode = 2;
      Ecran.Demo();
      etat = caseAttente;
      break;

    case caseDebogage:
      flagSelectionMode = 3;
      Ecran.Debogage();
      etat = caseAttente;
      break;

    case caseEnregistrer:
      flagSelectionMode = 4;
      Ecran.Enregistrer();
      etat = caseAttente;
      break;

    case caseSelection:
      Ecran.Choisir();
      switch (flagSelectionMode)
      {
      case 1:
        Ecran.AffichageLibre();
        data[3] = 1;
        break;
      case 2:
        data[3] = 2;
        Ecran.AffichageDemo();
        break;
      case 3:
        data[3] = 3;
        Ecran.AffichageDebug();
        break;
      case 4:
        data[3] = 4;
        Ecran.AffichageEnregistrer();
        break;
      }
      pc.write(data, sizeof(data));

      flagMenu = false;
      flagModes = false;
      flagSelection = true;
      etat = caseAttente;
      break;

    case caseEnvoiPosition:
      if (SW1 == 1 && SW2 == 0)
      {
        data[8] = 1;
      }
      else if (SW2 == 1 && SW1 == 0)
      {
        data[8] = 2;
      }
      else
      {
        data[8] = 0;
      }
      // Lecture et transmission de la valeur des joysticks
      data[9] = DroitX.read_u16() * 0.00389106;   // Base
      data[10] = GaucheY.read_u16() * 0.00389106; // Coude
      data[11] = DroitY.read_u16() * 0.00389106;  // Poignet
      data[12] = GaucheX.read_u16() * 0.00389106; // Epaule
      pc.write(data, sizeof(data));
      thread_sleep_for(100);
      etat = caseAttente;
      break;

    case caseEnregistrement:
      Ecran.BtnDemarrerAppuye();
      thread_sleep_for(250);
      Ecran.FermerBtnDemarrer();
      LED = 1;
      flagEnregistrement = true;
      InterruptionEnregistrement.attach(&FinEnregistrement, 10.0);
      data[4] = 1;
      pc.write(data, sizeof(data));
      etat = caseAttente;
      break;

    case caseFinEnregistrement:
      flagEnregistrement = false;
      flagSelectionMode = 0;
      Ecran.FinEnregistrement();
      data[4] = 0;
      pc.write(data, sizeof(data));
      etat = caseAttente;
      break;

    case caseRejouer:
      Ecran.BtnRejouerAppuye();
      thread_sleep_for(250);
      Ecran.FermerBtnRejouer();
      data[5] = 1;
      pc.write(data, sizeof(data));
      data[5] = 0;
      etat = caseAttente;
      break;

    case LedOn:
      data[7] = 1;
      pc.write(data, sizeof(data));
      thread_sleep_for(100);
      etat = caseAttente;
      break;

    case LedOff:
      data[7] = 0;
      pc.write(data, sizeof(data));
      thread_sleep_for(100);
      etat = caseAttente;
      break;
    }
  }
}