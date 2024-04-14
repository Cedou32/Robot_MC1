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
uint8_t flagSelectionEnregistrement = 0;
// Trames
uint8_t data[15];

//******Machine a etat******//
// Declaration de la variable etat
// uint8_t etat = Demarrage;

//******Declaration des objets******//
DisplayInterface Ecran(PA_7, PA_6, PA_5, PA_8, PA_10, PA_9); // mosi, miso, sclk, cs, reset, dc
TouchScreen Touch(TouchXp, TouchXn, TouchYp, TouchYn);
BufferedSerial pc(PB_6, PB_7); // USBTX et USBRX sont les broches de communication série sur la carte Nucleo STM32F072RB
Ticker InterruptionBatterie;
Ticker InterruptionEnregistrement;

StateInfo info;
EtatLib etat;
std::string nomEtat;

int main()
{
  info.etat = Demarrage;
  info.nom = "Demarrage";
  while (1)
  {
    if (Touch.Touch_detect())
    {
      positionX = Touch.getX(); // prendre la valeur de l'axe X
      positionY = Touch.getY(); // prendre la valeur de l'axe Y
      info = TouchInterface::detectBouton(positionX, positionY, flagMenu, flagModes, flagSelectionMode, flagSelectionEnregistrement);
      etat = info.etat;
      nomEtat = info.nom;
    }

    if (nomEtat == "Menu"){
      LED = !LED;
    }
    switch (etat)
    {
    case Demarrage:
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
      etat = Attente;
      break;

    case Batterie:
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
      etat = Attente;
      break;

    case Attente:
      if (flagBatterie == true)
      {
        flagBatterie = false;
        etat = Batterie;
      }
      else if (flagSelectionMode == 1 && flagSelection) // Mode libre choisi
      {
        etat = TransmissionTrame;
      }
      else if (flagSelectionMode == 4 && flagEnregistrement)
      {
        etat = TransmissionTrame;
      }
      else if (flagSelectionMode == 5 && !flagEnregistrement)
      {
        etat = TransmissionTrame;
      }
      break;
    case Menu:
      flagMenu = !flagMenu; // activer le flag du bouton
      if (flagMenu == true)
      {
        Ecran.Menu();
      }
      else if (flagMenu == false)
      {
        Ecran.FermerMenu();
      }
      etat = Attente;
      break;

    case Modes:

      Ecran.Modes();
      flagModes = true;
      etat = Attente;
      break;
    case Libre:

      flagSelectionMode = 1;
      Ecran.Libre();
      etat = Attente;
      break;

    case Enregistrer:

      flagSelectionMode = 4;
      Ecran.Enregistrer();
      etat = Attente;
      break;
    case Demo:

      flagSelectionMode = 2;
      Ecran.Demo();
      etat = Attente;
      break;

    case Debogage:

      flagSelectionMode = 3;
      Ecran.Debogage();
      etat = Attente;
      break;
    case Selection:
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
      etat = Attente;
      break;

    case TransmissionTrame:
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
      etat = Attente;
      break;
    }
  }
}