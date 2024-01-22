#include "stdio.h"
#include "mbed.h"
#include "SPI_TFT_ILI9341.h"
#include "string"
#include "TextDisplay.h"
#include "Arial12x12.h"
#include "Arial24x23.h"
#include "TouchScreen.h"

#define Xp A4
#define Yp A5
#define Xn A2
#define Yn A3

uint16_t X;
uint16_t Y;
AnalogIn axeX(PC_3);
DigitalIn bouton_servo(PC_9);

bool _menu = false;
bool _vitesse = false;

uint8_t v_moteur;

AnalogIn joystick(PA_0);
uint8_t direction_stepper;

enum
{
  demarrage,
  attente_appui,
  detection_appui,
  menu,
  vitesse,
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
uint8_t data[10];

int main()
{
  pc.set_baud(38400);
  while (1)
  {

    switch (etat){
      case demarrage:
          // TFT.claim(stdout);     
          TFT.background(Black); 
          TFT.cls();             
          TFT.set_orientation(3);

          TFT.rect(0, 0, 320, 240, Blue);

          TFT.rect(10, 10, 110, 40, White);          
          TFT.set_font((unsigned char *)Arial24x23); 
          TFT.foreground(Blue);                      
          TFT.locate(20, 15);
          TFT.printf("Menu");

          etat = attente_appui;
        break;

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

      case detection_appui:
          X = Touch.getX();
          Y = Touch.getY();
          printf("%d,%d\r\n",X,Y);
          if (X >= 10 && X <= 110 && Y >= 10 && Y <= 40 && _menu == false){
            _menu = true;
            etat = menu;
          }
          else if(X >= 10 && X <= 90 && Y >= 50 && Y <= 70 && _vitesse == false){
            _vitesse = true;
            etat = vitesse;
          }
          else if(X >= 120 && X <= 140 && Y >= 50 && Y <= 70){
            etat = selection_vitesse1;
          }
          else if(X >= 150 && X <= 170 && Y >= 50 && Y <= 70){
            etat = selection_vitesse2;
          }
          else if(X >= 180 && X <= 200 && Y >= 50 && Y <= 70){
            etat = selection_vitesse3;
          }
          else if(X >= 240 && X <= 310 && Y >= 210 && Y <= 230){
            etat = fermer;
          }
          else if(X >= 240 && X <= 310 && Y >= 180 && Y <= 200){
            etat = ok;
          }
          else{
            etat = attente_appui;
          }
        break;

        case menu:
            TFT.rect(10, 10, 110, 40, DarkGrey);          
            TFT.set_font((unsigned char *)Arial24x23); 
            TFT.foreground(DarkGrey);                      
            TFT.locate(20, 15);
            TFT.printf("Menu");

            TFT.rect(10, 50, 90, 70, White);           
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(Green);                     
            TFT.locate(25, 55);
            TFT.printf("Vitesse");

            TFT.rect(240, 210, 310, 230, White);       
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(White);                     
            TFT.locate(252, 215);
            TFT.printf("Fermer");

            etat = attente_appui;
          break;

        case vitesse:
            TFT.rect(10, 50, 90, 70, DarkGrey);           
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(DarkGrey);                     
            TFT.locate(25, 55);
            TFT.printf("Vitesse");

            TFT.rect(120, 50, 140, 70, White);         
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(Red);                       
            TFT.locate(127, 57);
            TFT.printf("1");

            TFT.rect(150, 50, 170, 70, White);         
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(Red);                       
            TFT.locate(157, 57);
            TFT.printf("2");

            TFT.rect(180, 50, 200, 70, White);         
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(Red);                       
            TFT.locate(187, 57);
            TFT.printf("3");

            etat = attente_appui;
          break;

        case selection_vitesse1:
            v_moteur = 1;

            TFT.rect(120, 50, 140, 70, DarkGrey);         
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(DarkGrey);                       
            TFT.locate(127, 57);
            TFT.printf("1");

            TFT.rect(150, 50, 170, 70, White);         
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(Red);                       
            TFT.locate(157, 57);
            TFT.printf("2");

            TFT.rect(180, 50, 200, 70, White);         
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(Red);                       
            TFT.locate(187, 57);
            TFT.printf("3");

            TFT.rect(240, 180, 310, 200, White);       
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(White);                     
            TFT.locate(252, 185);
            TFT.printf("Choisir");

            etat = attente_appui;
          break;

        case selection_vitesse2:
            v_moteur = 2;

            TFT.rect(120, 50, 140, 70, White);         
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(Red);                       
            TFT.locate(127, 57);
            TFT.printf("1");

            TFT.rect(150, 50, 170, 70, DarkGrey);         
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(DarkGrey);                       
            TFT.locate(157, 57);
            TFT.printf("2");

            TFT.rect(180, 50, 200, 70, White);         
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(Red);                       
            TFT.locate(187, 57);
            TFT.printf("3");

            TFT.rect(240, 180, 310, 200, White);       
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(White);                     
            TFT.locate(252, 185);
            TFT.printf("Choisir");

            etat = attente_appui;
          break;

        case selection_vitesse3:
            v_moteur = 3;

            TFT.rect(120, 50, 140, 70, White);         
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(Red);                       
            TFT.locate(127, 57);
            TFT.printf("1");

            TFT.rect(150, 50, 170, 70, White);         
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(Red);                       
            TFT.locate(157, 57);
            TFT.printf("2");

            TFT.rect(180, 50, 200, 70, DarkGrey);         
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(DarkGrey);                       
            TFT.locate(187, 57);
            TFT.printf("3");

            TFT.rect(240, 180, 310, 200, White);       
            TFT.set_font((unsigned char *)Arial12x12); 
            TFT.foreground(White);                     
            TFT.locate(252, 185);
            TFT.printf("Choisir");

            etat = attente_appui;
          break;

        case fermer:
            TFT.fillrect(10,50,200,70,Black);
            TFT.fillrect(240, 210, 310, 230, Black); 
            TFT.fillrect(240, 180, 310, 200, Black);

            TFT.rect(10, 10, 110, 40, White);          
            TFT.set_font((unsigned char *)Arial24x23); 
            TFT.foreground(Blue);                      
            TFT.locate(20, 15);
            TFT.printf("Menu");

            _menu = false;
            _vitesse = false;

            etat = attente_appui;
          break;

        case ok:
            if(v_moteur == 1){
            data[1] = 1;  
            pc.write(data, sizeof(data));
            }
            else if(v_moteur == 2){
            data[1] = 2;  
            pc.write(data, sizeof(data));
            }
            else if(v_moteur == 3){
            data[1] = 3;  
            pc.write(data, sizeof(data));
            }

            TFT.fillrect(10,50,200,70,Black);
            TFT.fillrect(240, 210, 310, 230, Black); 
            TFT.fillrect(240, 180, 310, 200, Black);

            TFT.rect(10, 10, 110, 40, White);          
            TFT.set_font((unsigned char *)Arial24x23); 
            TFT.foreground(Blue);                      
            TFT.locate(20, 15);
            TFT.printf("Menu");

            _menu = false;
            _vitesse = false;

            etat = attente_appui;
          break;
    }
  }
}