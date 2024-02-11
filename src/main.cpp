#include "stdio.h"
#include "mbed.h"
#include "SPI_TFT_ILI9341.h"
//#include "string"
//#include "TextDisplay.h"
#include "Arial12x12.h"
#include "Arial24x23.h"
#include "TouchScreen.h"

//Pins pour l<interface tactile
#define Xp A4
#define Yp A5
#define Xn A2
#define Yn A3

uint16_t positionX; //valeur de l'axe X du toucher
uint16_t positionY; //valeur de l'axe Y du toucher

DigitalIn bouton_servo(PC_9); //bouton pour simuler le controle de la pince


bool flag_menu = false; //flag pour indiquer si le bouton "Menu" a ete appuye
bool flag_vitesse = false;  //flag pour indiquer si le bouton "Vitesse" a ete appuye
bool flag_modes = false; //flag pour indiquer si le bouton "Modes" a ete appuye

uint8_t vitesse_moteur; //vitesse des stepper qui sera transmise

AnalogIn joystick(PA_0);  //jostick pour changer la direction des moteurs
uint8_t direction_stepper;  //direction de rotation du moteur transmise

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
  stepper
}; 
uint8_t etat = demarrage;

SPI_TFT_ILI9341 TFT(D11, D12, D13, PD_2, D8, D9, "TFT"); // mosi, miso, sclk, cs, reset, dc
TouchScreen Touch(A4, A2, A5, A3);
BufferedSerial pc(PB_6, PA_10); // USBTX et USBRX sont les broches de communication série sur la carte Nucleo STM32F072RB

uint8_t data[10]; //tableau de donnee transmis par BT

int main()
{
  pc.set_baud(38400); //instancier baud-rate pour la communication BT

  while (1)
  {

    switch (etat){

      //initialisation de l'ecran d'acceuil
      case demarrage:    
          TFT.background(Black); 
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
          TFT.fillrect(50, 11, 54, 14, DarkGreen);


          etat = attente_appui;
        break;

      //attente d'un appui 
      case attente_appui:
          if (Touch.Touch_detect())
          {
            etat = detection_appui;
          }
          if (bouton_servo.read() == 1){
            thread_sleep_for(500);
            etat = servo;
          }
          if (joystick.read_u16() > 0x8500){
              direction_stepper = 1;
              etat = stepper;
          } else if(joystick.read_u16() < 0x7700){
              direction_stepper = 2;
              etat = stepper;
          }
        break;
      
      case stepper:
        data[3] = direction_stepper;
        pc.write(data, sizeof(data));
        data[3] = 0;
        thread_sleep_for(50);
        etat = attente_appui;
        break;

      case servo:
        data[2] = 1;
        pc.write(data, sizeof(data));
        data[2] = 0;
        etat = attente_appui;
        break;

      //lorsque l'utilisateur appuie sur l'ecran
      case detection_appui:
          positionX = Touch.getX(); //prendre la valeur de l'axe X
          positionY = Touch.getY(); //prendre la valeur de l'axe Y

          printf("%d,%d\r\n",positionX,positionY);  //afficher 

          //si on appuie sur le bouton "Menu"
          if (positionX >= 210 && positionX <= 310 && positionY >= 10 && positionY <= 40 && flag_menu == false){
            flag_menu = true;  //activer le flag du bouton
            etat = menu;
          }
          //si on appuie sur le bouton "Vitesse"
          else if(positionX >= 10 && positionX <= 90 && positionY >= 50 && positionY <= 70 && flag_vitesse == false){
            flag_vitesse = true; //activer le flag du bouton
            etat = vitesse;
          }
          //si on appuie sur le bouton "Modes"
          else if(positionX >= 10 && positionX <= 90 && positionY >= 80 && positionY <= 100){
            flag_modes = true;
            etat = modes;
          }
          //si on appuie sur le bouton "Libre"
          else if(positionX >= 120 && positionX <= 210 && positionY >= 80 && positionY <= 100 && flag_modes == true){
            etat = libre;
          }
          //si on appuie sur le bouton "Enregistrer"
          else if(positionX >= 220 && positionX <= 310 && positionY >= 80 && positionY <= 100 && flag_modes == true){
            etat = enregistrer;
          }
          //si on appuie sur le bouton "Etendu"
          else if(positionX >= 120 && positionX <= 210 && positionY >= 110 && positionY <= 130 && flag_modes == true){
            etat = etendu;
          }
          //si on appuie sur le bouton "Debogage"
          else if(positionX >= 220 && positionX <= 310 && positionY >= 110 && positionY <= 130 && flag_modes == true){
            etat = debogage;
          }
          
          //si on appuie sur le bouton de la vitesse "1"
          else if(positionX >= 120 && positionX <= 140 && positionY >= 50 && positionY <= 70 && flag_vitesse == true){
            etat = selection_vitesse1;
          }
          //si on appuie dur le bouton de la vitesse "2"
          else if(positionX >= 150 && positionX <= 170 && positionY >= 50 && positionY <= 70 && flag_vitesse == true){
            etat = selection_vitesse2;
          }
          //si on appuie sur le bouton de la vitesse "3"
          else if(positionX >= 180 && positionX <= 200 && positionY >= 50 && positionY <= 70 && flag_vitesse == true){
            etat = selection_vitesse3;
          }
          //si on appuie sur le bouton "Fermer"
          else if(positionX >= 240 && positionX <= 310 && positionY >= 210 && positionY <= 230){
            etat = fermer;
          }
          //si on appuie sur le bouton "choisir" 
          else if(positionX >= 240 && positionX <= 310 && positionY >= 180 && positionY <= 200){
            etat = ok;
          }
          else{
            etat = attente_appui;
          }
        break;

        case menu:
            //changer la couleur du bouton pour indiquer qu'il a ete appuye
            TFT.rect(210, 10, 310, 40, DarkGrey);          
            TFT.set_font((unsigned char *)Arial24x23); 
            TFT.foreground(DarkGrey);                      
            TFT.locate(220, 15);
            TFT.printf("Menu");

            //afficher le bouton "Vitesse"
            TFT.rect(10, 50, 90, 70, White);           
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(Green);                     
            TFT.locate(25, 55);
            TFT.printf("Vitesse");

            //afficher le bouton "Modes"
            TFT.rect(10, 80, 90, 100, White);           
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(Orange);                     
            TFT.locate(25, 85);
            TFT.printf("Modes");

            //afficher le bouton "Fermer"
            TFT.rect(240, 210, 310, 230, White);       
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(White);                     
            TFT.locate(252, 215);
            TFT.printf("Fermer");

            etat = attente_appui;
          break;

        case vitesse:
            //changer la couleur du bouton pour indiquer qu'il a ete appuye
            TFT.rect(10, 50, 90, 70, DarkGrey);           
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(DarkGrey);                     
            TFT.locate(25, 55);
            TFT.printf("Vitesse");

            //afficher le bouton de vitesse "1"
            TFT.rect(120, 50, 140, 70, White);         
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(Red);                       
            TFT.locate(127, 57);
            TFT.printf("1");

            //afficher le bouton de vitesse "2"
            TFT.rect(150, 50, 170, 70, White);         
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(Red);                       
            TFT.locate(157, 57);
            TFT.printf("2");

            //afficher le bouton de vitesse "3"
            TFT.rect(180, 50, 200, 70, White);         
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(Red);                       
            TFT.locate(187, 57);
            TFT.printf("3");

            etat = attente_appui;
          break;

        case modes:

          //Changer la couleur du bouton
            TFT.rect(10, 80, 90, 100, DarkGrey);           
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(DarkGrey);                     
            TFT.locate(25, 85);
            TFT.printf("Modes");

            TFT.rect(120, 80, 210, 100, White);           
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(Green);                     
            TFT.locate(140, 85);
            TFT.printf("Libre");

            TFT.rect(220, 80, 310, 100, White);           
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(Green);                     
            TFT.locate(225, 85);
            TFT.printf("Enregistrer");

            TFT.rect(120, 110, 210, 130, White);           
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(Green);                     
            TFT.locate(140, 115);
            TFT.printf("Etendu");

            TFT.rect(220, 110, 310, 130, White);           
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(Green);                     
            TFT.locate(225, 115);
            TFT.printf("Debogage");
            

            etat = attente_appui;
          break; 

        case libre:

            TFT.rect(120, 80, 210, 100, DarkGrey);           
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(DarkGrey);                     
            TFT.locate(140, 85);
            TFT.printf("Libre");

            TFT.rect(220, 80, 310, 100, White);           
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(Green);                     
            TFT.locate(225, 85);
            TFT.printf("Enregistrer");

            TFT.rect(120, 110, 210, 130, White);           
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(Green);                     
            TFT.locate(140, 115);
            TFT.printf("Etendu");

            TFT.rect(220, 110, 310, 130, White);           
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(Green);                     
            TFT.locate(225, 115);
            TFT.printf("Debogage");

            //afficher le bouton "Choisir"
            TFT.rect(240, 180, 310, 200, White);       
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(White);                     
            TFT.locate(252, 185);
            TFT.printf("Choisir");

            etat = attente_appui;
          break;

        case enregistrer:

            TFT.rect(120, 80, 210, 100, White);           
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(Green);                     
            TFT.locate(140, 85);
            TFT.printf("Libre");

            TFT.rect(220, 80, 310, 100, DarkGrey);           
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(DarkGrey);                     
            TFT.locate(225, 85);
            TFT.printf("Enregistrer");

            TFT.rect(120, 110, 210, 130, White);           
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(Green);                     
            TFT.locate(140, 115);
            TFT.printf("Etendu");

            TFT.rect(220, 110, 310, 130, White);           
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(Green);                     
            TFT.locate(225, 115);
            TFT.printf("Debogage");

            //afficher le bouton "Choisir"
            TFT.rect(240, 180, 310, 200, White);       
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(White);                     
            TFT.locate(252, 185);
            TFT.printf("Choisir");

            etat =  attente_appui;
          break;

        case etendu:

            TFT.rect(120, 80, 210, 100, White);           
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(Green);                     
            TFT.locate(140, 85);
            TFT.printf("Libre");

            TFT.rect(220, 80, 310, 100, White);           
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(Green);                     
            TFT.locate(225, 85);
            TFT.printf("Enregistrer");

            TFT.rect(120, 110, 210, 130, DarkGrey);           
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(DarkGrey);                     
            TFT.locate(140, 115);
            TFT.printf("Etendu");

            TFT.rect(220, 110, 310, 130, White);           
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(Green);                     
            TFT.locate(225, 115);
            TFT.printf("Debogage");

            //afficher le bouton "Choisir"
            TFT.rect(240, 180, 310, 200, White);       
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(White);                     
            TFT.locate(252, 185);
            TFT.printf("Choisir");

            etat = attente_appui;
          break;

        case debogage:

            TFT.rect(120, 80, 210, 100, White);           
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(Green);                     
            TFT.locate(140, 85);
            TFT.printf("Libre");

            TFT.rect(220, 80, 310, 100, White);           
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(Green);                     
            TFT.locate(225, 85);
            TFT.printf("Enregistrer");

            TFT.rect(120, 110, 210, 130, White);           
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(Green);                     
            TFT.locate(140, 115);
            TFT.printf("Etendu");

            TFT.rect(220, 110, 310, 130, DarkGrey);           
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(DarkGrey);                     
            TFT.locate(225, 115);
            TFT.printf("Debogage");

            //afficher le bouton "Choisir"
            TFT.rect(240, 180, 310, 200, White);       
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(White);                     
            TFT.locate(252, 185);
            TFT.printf("Choisir");

            etat = attente_appui;
          break;

        case selection_vitesse1:
            vitesse_moteur = 1; // mettre la vitesse a 1

            //changer la couleur du bouton pour indiquer qu'il a ete appuye
            TFT.rect(120, 50, 140, 70, DarkGrey);         
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(DarkGrey);                       
            TFT.locate(127, 57);
            TFT.printf("1");

            //remettre la couleur originale du bouton
            TFT.rect(150, 50, 170, 70, White);         
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(Red);                       
            TFT.locate(157, 57);
            TFT.printf("2");

            //remettre la couleur originale du bouton
            TFT.rect(180, 50, 200, 70, White);         
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(Red);                       
            TFT.locate(187, 57);
            TFT.printf("3");

            //afficher le bouton "Choisir"
            TFT.rect(240, 180, 310, 200, White);       
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(White);                     
            TFT.locate(252, 185);
            TFT.printf("Choisir");

            etat = attente_appui;
          break;

        case selection_vitesse2:
            vitesse_moteur = 2; //mettre la vitesse a 2

            //remettre la couleur originale du bouton
            TFT.rect(120, 50, 140, 70, White);         
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(Red);                       
            TFT.locate(127, 57);
            TFT.printf("1");

            //changer la couleur du bouton pour indiquer qu'il a ete appuye
            TFT.rect(150, 50, 170, 70, DarkGrey);         
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(DarkGrey);                       
            TFT.locate(157, 57);
            TFT.printf("2");

            //remettre la couleur originale du bouton
            TFT.rect(180, 50, 200, 70, White);         
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(Red);                       
            TFT.locate(187, 57);
            TFT.printf("3");

            //afficher le bouton "Choisir"
            TFT.rect(240, 180, 310, 200, White);       
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(White);                     
            TFT.locate(252, 185);
            TFT.printf("Choisir");

            etat = attente_appui;
          break;

        case selection_vitesse3:
            vitesse_moteur = 3; //mettrre la vitesse a 3

            //remettre la couleur originale du bouton
            TFT.rect(120, 50, 140, 70, White);         
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(Red);                       
            TFT.locate(127, 57);
            TFT.printf("1");

            //remettre la couleur originale du bouton
            TFT.rect(150, 50, 170, 70, White);         
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(Red);                       
            TFT.locate(157, 57);
            TFT.printf("2");

            //changer la couleur du bouton pour indiquer qu'il a ete appuye
            TFT.rect(180, 50, 200, 70, DarkGrey);         
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(DarkGrey);                       
            TFT.locate(187, 57);
            TFT.printf("3");

            //afficher le bouton "Choisir"
            TFT.rect(240, 180, 310, 200, White);       
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(White);                     
            TFT.locate(252, 185);
            TFT.printf("Choisir");

            etat = attente_appui;
          break;

        case fermer:
            //fermer les boutons affiche
            TFT.fillrect(10,50,200,70,Black);
            TFT.fillrect(240, 210, 310, 230, Black); 
            TFT.fillrect(240, 180, 310, 200, Black);
            TFT.fillrect(10, 80, 90, 100, Black);  
            TFT.fillrect(120, 80, 210, 100, Black);
            TFT.fillrect(220, 80, 310, 100, Black);
            TFT.fillrect(220, 110, 310, 130, Black);
            TFT.fillrect(120, 110, 210, 130, Black);
            

            //remettre la couleur originale du bouton "Menu"
            TFT.rect(210, 10, 310, 40, White);          
            TFT.set_font((unsigned char *)Arial24x23); 
            TFT.foreground(Blue);                      
            TFT.locate(220, 15);
            TFT.printf("Menu");

            //baisser les flags
            flag_menu = false;
            flag_vitesse = false;
            flag_modes = false;

            etat = attente_appui;
          break;

        case ok:
            //envoyer la vitesse par BT
            data[1] = vitesse_moteur;  
            pc.write(data, sizeof(data));
            
            //effacer les boutons affiche
            TFT.fillrect(10,50,200,70,Black);
            TFT.fillrect(240, 210, 310, 230, Black); 
            TFT.fillrect(240, 180, 310, 200, Black);
            TFT.fillrect(10, 80, 90, 100, Black);  
            TFT.fillrect(120, 80, 210, 100, Black);
            TFT.fillrect(220, 80, 310, 100, Black);
            TFT.fillrect(220, 110, 310, 130, Black);
            TFT.fillrect(120, 110, 210, 130, Black);

            //remettre la couleur originale du bouton "Menu"
            TFT.rect(210, 10, 310, 40, White);          
            TFT.set_font((unsigned char *)Arial24x23); 
            TFT.foreground(Blue);                      
            TFT.locate(220, 15);
            TFT.printf("Menu");

            //baisser les
            flag_menu = false;
            flag_vitesse = false;
            flag_modes = false;

            etat = attente_appui;
          break;
    }
  }
}