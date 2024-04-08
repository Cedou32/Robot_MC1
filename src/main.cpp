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
// Temps d'appui boutons
long currentFermer = 0, previousFermer = 0;
long currentOuvert = 0, previousOuvert = 0;
uint8_t valeurPince = 130;
// Flags
bool flagMenu = false;    // flag pour indiquer si le bouton "Menu" a ete appuye
uint8_t flagV = 0;
bool flagModes = false; // flag pour indiquer si le bouton "Modes" a ete appuye
bool flagBatterie = false;
bool flagLibre = false, flagEtendu = false, flagDebug = false, flagEnregistrement = false;
bool flagSelection = false;
bool flagEnvoiLibre = false;
// Trames
uint8_t trameBras[15];
//******Machine a etat******//
// Declaration de la variable etat
uint8_t etat = demarrage;
//******Declaration des objets******//
DisplayInterface Ecran(PA_7, PA_6, PA_5, PA_8, PA_10, PA_9); // mosi, miso, sclk, cs, reset, dc
TouchScreen Touch(TouchXp, TouchXn, TouchYp, TouchYn);
BufferedSerial pc(PB_6, PB_7); // USBTX et USBRX sont les broches de communication série sur la carte Nucleo STM32F072RB
Ticker InterruptionBatterie;
Timer Ouvrir;
Timer Fermer;
//******Fonctions pour les interruptions******//
void VerifBatterie()
{
  compteur = compteur + 1;
  flagBatterie = true;
}

int main()
{
  // Attacher la fonction
  InterruptionBatterie.attach(&VerifBatterie, 0.01);
  /*SW1.rise(&FermerPinceRise);
  SW2.rise(&OuvrirPinceRise);
  SW1.fall(&FermerPinceFall);
  SW2.fall(&OuvrirPinceFall);*/

  // Indication des valeurs de securite de la trame
  trameBras[0] = '#';
  trameBras[1] = '@';
  trameBras[2] = '+';
  trameBras[13] = '?';
  trameBras[14] = '%';
  pc.set_baud(115200); // instancier baud-rate pour la communication BT
  while (1)
  {
    switch (etat)
    {
    // initialisation de l'ecran d'acceuil
    case demarrage:
      Ecran.Demarrage();
      Ecran.LogoOn();
      // verification du niveau de la batterie au demarrage
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
      Ecran.BtnBatterie(batterie, ligne);
      // afficher le bouton menu
      Ecran.BtnMenuNonAppuye();
      etat = attente;
      break;
    // attente d'un appui
    case attente:
      if (Touch.Touch_detect())
      {
        positionX = Touch.getX(); // prendre la valeur de l'axe X
        positionY = Touch.getY(); // prendre la valeur de l'axe Y
        etat = detectionAppui;
      }
      else if (flagBatterie == true)
      {
        flagBatterie = false;
        etat = battery;
      }
      else if (flagLibre && flagSelection)
      {
        etat = lectureLibre;
      }
      // etat = mvtRobot;

      break;
    case battery:
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
      etat = attente;
      break;
    case lectureLibre:
      if (SW1 == 1 && SW2 == 0)
      {
        trameBras[8] = 1;
      }
      else if (SW2 == 1 && SW1 == 0)
      {
        trameBras[8] = 2;
      }
      else
      {
        trameBras[8] = 0;
      }
      // Lecture et transmission de la valeur des joysticks
      trameBras[9] = DroitX.read_u16() * 0.00389106;   // Base
      trameBras[10] = GaucheY.read_u16() * 0.00389106; // Coude
      trameBras[11] = DroitY.read_u16() * 0.00389106;  // Poignet
      trameBras[12] = GaucheX.read_u16() * 0.00389106; // Epaule
      pc.write(trameBras, sizeof(trameBras));
      thread_sleep_for(100);
      etat = attente;
      break;
    // Controle du robot
    case mvtRobot:

      pc.write(trameBras, sizeof(trameBras));
      thread_sleep_for(100);
      etat = attente;
      break;
    // lorsque l'utilisateur appuie sur l'ecran
    case detectionAppui:
      etat = TouchInterface::detectBouton(positionX, positionY, flagMenu, flagModes);
      break;
    case LedOn:
      trameBras[7] = 1;
      pc.write(trameBras, sizeof(trameBras));
      thread_sleep_for(100);
      etat = attente;
      break;
    case LedOff:
      trameBras[7] = 0;
      pc.write(trameBras, sizeof(trameBras));
      thread_sleep_for(100);
      etat = attente;
      break;
    case menu:
      flagMenu = !flagMenu; // activer le flag du bouton
      if (flagMenu == true)
      {
        //Ecran.FermerAffichage();
        Ecran.Menu();
        
      }
      else if (flagMenu == false)
      {
        Ecran.FermerMenu();
      }
      etat = attente;
      break;
    case modes:
      Ecran.Modes();
      flagModes = true;
      etat = attente;
      break;
    case libre:
      flagLibre = true;
      flagEtendu = false;
      flagDebug = false;
      flagEnregistrement = false;
      Ecran.Libre();
      etat = attente;
      break;
    case enregistrer:
      flagLibre = false;
      flagEtendu = false;
      flagDebug = false;
      flagEnregistrement = true;
      Ecran.Enregistrer();
      etat = attente;
      break;
    case etendu:
      flagLibre = false;
      flagEtendu = true;
      flagDebug = false;
      flagEnregistrement = false;
      Ecran.Etendu();
      etat = attente;
      break;
    case debogage:
      flagLibre = false;
      flagEtendu = false;
      flagDebug = true;
      flagEnregistrement = false;
      Ecran.Debogage();
      etat = attente;
      break;
    case ok:
      pc.write(trameBras, sizeof(trameBras));
      Ecran.Choisir();

      if (flagLibre == true){
        Ecran.AffichageLibre();
      } else if (flagEtendu == true){
        Ecran.AffichageDemo();
      } else if (flagDebug == true){
        Ecran.AffichageDebug();
      } else if (flagEnregistrement == true){
        Ecran.AffichageEnregistrer();
      }

      flagMenu = false;
      flagModes = false;
      flagSelection = true;
      etat = attente;
      break;
    }
  }
}