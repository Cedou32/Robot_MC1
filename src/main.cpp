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
bool flagFinEnregistrement = false;
uint8_t modeActuel = 0;
uint8_t enregistrementActuel = 0;

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
bool status;
uint8_t mode;
uint8_t selection;

// fonction qui arrete l'enregistrement
void FinEnregistrement()
{
  LED = !LED;
  InterruptionEnregistrement.detach();

  flagFinEnregistrement = true;
}

Ticker timer;
bool flagTemps = false;
uint8_t temps = 0;
// Fonction de rappel appelée chaque seconde
void chaqueSeconde()
{
  flagTemps = true; // Lever le flag
  temps += 1;
}

int main()
{

  // Indication des valeurs de securite de la trame
  data[0] = '#';
  data[1] = '@';
  data[2] = '+';
  data[13] = '?';
  data[14] = '%';

  pc.set_baud(115200); // instancier baud-rate pour la communication BT

  info.etat = Demarrage;
  info.nom = "Demarrage";
  while (1)
  {
    if (Touch.Touch_detect())
    {
      positionX = Touch.getX(); // prendre la valeur de l'axe X
      positionY = Touch.getY(); // prendre la valeur de l'axe Y
      info = TouchInterface::detectBouton(positionX, positionY, flagMenu, flagModes, modeActuel, enregistrementActuel);
      etat = info.etat;
      nomEtat = info.nom;
      status = info.status;
      mode = info.mode;
    }

    switch (etat)
    {
    case Demarrage:
      Ecran.Initialisation(); // Initialisation de l'ecran
      etat = Attente;
      break;

    case Batterie:
      break;

    case Attente:
      if (mode == 1 && status == true) // Mode libre choisi
      {
        etat = TransmissionTrame;
      }
      else if (data[4] == 1)
      {
        etat = TransmissionTrame;
      }
      if (flagTemps == true)
      {
        flagTemps = false;
        Ecran.EffacerDecompte();
        switch (temps)
        {
        case 10:
          Ecran.Decompte0();
          break;
        case 9:
          Ecran.Decompte1();
          break;
        case 8:
          Ecran.Decompte2();
          break;
        case 7:
          Ecran.Decompte3();
          break;
        case 6:
          Ecran.Decompte4();
          break;
        case 5:
          Ecran.Decompte5();
          break;
        case 4:
          Ecran.Decompte6();
          break;
        case 3:
          Ecran.Decompte7();
          break;
        case 2:
          Ecran.Decompte8();
          break;
        case 1:
          Ecran.Decompte9();
          break;
        }
      }
      if (flagFinEnregistrement == true)
      {
        etat = Enregistrer;
      }

      break;
    case Menu:
      flagMenu = !flagMenu; // activer le flag du bouton
      if (flagMenu == true)
      {
        Ecran.Menu();

        modeActuel = 0;
        enregistrementActuel = 0;
        selection = 0;
        flagFinEnregistrement = false;
        flagModes = false;
      }
      else if (flagMenu == false)
      {
        Ecran.FermerMenu();

        modeActuel = 0;
        enregistrementActuel = 0;
        selection = 0;
        flagFinEnregistrement = false;
        flagModes = false;
      }
      etat = Attente;
      break;

    case Modes:
      Ecran.Modes();
      flagModes = true;
      etat = Attente;
      break;

    case Libre:
      Ecran.Libre();
      etat = Attente;
      break;

    case Demo:
      Ecran.Demo();
      etat = Attente;
      break;

    case Debogage:
      Ecran.Debogage();
      etat = Attente;
      break;

    case Enregistrer:
      if (selection == 0)
      {
        Ecran.Enregistrer();
      }
      else if (selection == 1)
      {
        if (nomEtat == "Enregistrement1")
        {
          enregistrementActuel = 1;
          Ecran.BtnEnregistrement1Appuye();
          Ecran.BtnEnregistrement2NonAppuye();
          Ecran.BtnEnregistrement3NonAppuye();
          Ecran.BtnChoisirNonAppuye();
        }
        else if (nomEtat == "Enregistrement2")
        {
          enregistrementActuel = 2;
          Ecran.BtnEnregistrement1NonAppuye();
          Ecran.BtnEnregistrement2Appuye();
          Ecran.BtnEnregistrement3NonAppuye();
          Ecran.BtnChoisirNonAppuye();
        }
        else if (nomEtat == "Enregistrement3")
        {
          enregistrementActuel = 3;
          Ecran.BtnEnregistrement1NonAppuye();
          Ecran.BtnEnregistrement2NonAppuye();
          Ecran.BtnEnregistrement3Appuye();
          Ecran.BtnChoisirNonAppuye();
        }
      }
      else if (selection == 2 && nomEtat != "Enregistrement")
      {
        selection = 3;
        Ecran.EffacerEnregistrement();
        Ecran.BtnDemarrerNonAppuye();
        Ecran.BtnRejouerNonAppuye();
        etat = Attente;
      }

      // Demarrer enregistrement
      if (nomEtat == "Enregistrement" && flagFinEnregistrement == false)
      {
        Ecran.BtnDemarrerAppuye();
        thread_sleep_for(250);
        Ecran.FermerBtnDemarrer();
        Ecran.FermerBtnRejouer();
        LED = 1;
        InterruptionEnregistrement.attach(&FinEnregistrement, 10.0);
        timer.attach(&chaqueSeconde, 1.0);
        data[4] = 1;
        pc.write(data, sizeof(data));
        etat = Attente;
      }

      // fin enregistrement
      if (flagFinEnregistrement == true)
      {
        timer.detach();
        flagTemps = false;
        temps = 0;
        flagFinEnregistrement = false;
        mode = 0;
        Ecran.FinEnregistrement();
        data[3] = 0;
        data[4] = 0;
        pc.write(data, sizeof(data));
        etat = Attente;
      }

      // Rejouer
      if (nomEtat == "Rejouer")
      {
        Ecran.BtnRejouerAppuye();
        thread_sleep_for(250);
        Ecran.FermerBtnRejouer();
        data[5] = 1;
        pc.write(data, sizeof(data));
        data[5] = 0;
        etat = Attente;
      }

      etat = Attente;
      break;

    case Selection:
      selection += 1;
      Ecran.Choisir();
      switch (mode)
      {
      case 1:
        Ecran.AffichageLibre();
        modeActuel = 1;
        data[3] = 1;
        etat = Attente;
        break;
      case 2:
        data[3] = 2;
        Ecran.AffichageDemo();
        modeActuel = 2;
        etat = Attente;
        break;
      case 3:
        data[3] = 3;
        Ecran.AffichageDebug();
        modeActuel = 3;
        etat = Attente;
        break;
      case 4:
        data[3] = 4;
        Ecran.AffichageEnregistrer();
        if (selection == 1)
        {
          Ecran.BtnEnregistrement1NonAppuye();
          Ecran.BtnEnregistrement2NonAppuye();
          Ecran.BtnEnregistrement3NonAppuye();
        }
        modeActuel = 4;
        etat = Enregistrer;
        break;
      }
      pc.write(data, sizeof(data));

      flagMenu = false;
      flagModes = false;

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