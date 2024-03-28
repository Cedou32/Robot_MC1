#include "mbed.h"

BufferedSerial pc(PB_6, PB_7); // USBTX et USBRX sont les broches de communication série sur la carte Nucleo STM32F072RB
uint8_t data[10];


DigitalOut LED(PC_13);

DigitalOut dirPinB(PC_0);
DigitalOut stepPinB(PC_1);

DigitalOut dirPinC(PB_9);
DigitalOut stepPinC(PB_8);

PwmOut ServoCoude(PC_8);
PwmOut ServoPoignet(PC_9);
PwmOut ServoPince(PC_6);

Ticker InterruptionServo;
Ticker InterruptionStepper;

char startMarker[] = "#@+";
char endMarker[] = "?%";
char currentChar;

uint8_t flagBT = 0;
int flag_protection = 0;
int flagStepper = 0;
int flagServo = 0;

float dutyCycleCoude = 0.03;   // Min = 0.03   Max = 0.125
float dutyCyclePoignet = 0.09; // Min = 0.025   Max = 0.115
float dutyCyclePince = 0.08;   // Fermer = 0.08 =    Ouvrir = 0.125 

enum etat
{
  depart,
  mouvement_moteur,
  attente_trame
};

void VerifServo()
{
  flagServo = 1;
}

void VerifStepper()
{
  flagStepper = 1;
}

int main()
{
  InterruptionServo.attach(&VerifServo, 0.001);
  InterruptionStepper.attach(&VerifStepper, 0.002);

  data[5] = 100;
  data[6] = 100;
  data[7] = 100;
  data[8] = 100;
  data[9] = 100;
  

  pc.set_baud(115200);
  etat etat_actuel = depart;
  while (1)
  {
    switch (etat_actuel)
    {
    case depart:
      LED = 1;
      for (int i = 0; i < 750; i++)
      {
        stepPinC = 1;
        thread_sleep_for(2);
        stepPinC = 0;
        thread_sleep_for(2);
      }
      // thread_sleep_for(1000);
      ServoCoude.write(0.03);
      thread_sleep_for(750);
      ServoPoignet.write(0.09);
      thread_sleep_for(500);
      ServoPince.write(0.12);
      thread_sleep_for(500);
      ServoPince.write(0.08);
      thread_sleep_for(500);

      etat_actuel = attente_trame;
      break;
    case attente_trame:

      if (pc.readable() == 1)
      {
        etat_actuel = mouvement_moteur;
      }
      LED = 0;
      break;
    case mouvement_moteur:
      if (pc.readable())
      {
        pc.read(&currentChar, 1);
        if (currentChar == '#')
        {
          flag_protection++;
        }
        else if (currentChar == '@' && flag_protection == 1)
        {
          flag_protection++;
        }
        else if (currentChar == '+' && flag_protection == 2)
        {
          flag_protection++;
          for (int i = 0; i <= 9; i++)
          {
            pc.read(&currentChar, 1);
            data[i] = currentChar;
          }
        }
        else if (currentChar == '?' && flag_protection == 3)
        {
          flag_protection++;
        }
        else if (currentChar == '%' && flag_protection == 4)
        {
          flag_protection = 0;
          pc.write(data, 10);
        }
        else
        {
          memset(data, 100, 10);
        }
        // LED = int(data[7]);
      }

      if (flagStepper == 1)
      {
        flagStepper = 0;
        if (data[6] >= 85 && data[6] <= 170)
        {
          stepPinB = 0;
        }
        else if (data[6] >= 0 && data[6] < 85)
        {
          dirPinB = 0;
          stepPinB = !stepPinB;
        }
        else if (data[6] >= 170 && data[6] <= 270)
        {
          dirPinB = 1;
          stepPinB = !stepPinB;
        }

        if (data[9] >= 85 && data[9] <= 170)
        {
          stepPinC = 0;
        }
        else if (data[9] >= 0 && data[9] < 85)
        {
          dirPinC = 0;
          stepPinC = !stepPinC;
        }
        else if (data[9] >= 170 && data[9] <= 270)
        {
          dirPinC = 1;
          stepPinC = !stepPinC;
        }
      }

      if (flagServo == 1)
      {
        flagServo = 0;
        // Code du servo Poignet
        if (data[8] >= 85 && data[8] <= 170)
        {
        }
        else if (data[85] >= 0 && data[8] < 85)
        {
          dutyCycleCoude -= 0.00005;
        }
        else if (data[8] >= 170 && data[8] <= 255)
        {
          dutyCycleCoude += 0.00005;
        }
        if (dutyCycleCoude < 0.03)
        {
          dutyCycleCoude = 0.03;
        }
        else if (dutyCycleCoude > 0.125)
        {
          dutyCycleCoude = 0.125;
        }
        ServoCoude.write(dutyCycleCoude);
        // Code du servo Coude
        if (data[7] >= 85 && data[7] <= 170)
        {
        }
        else if (data[7] >= 0 && data[7] < 85)
        {
          dutyCyclePoignet -= 0.00005;
        }
        else if (data[7] >= 170 && data[7] <= 255)
        {
          dutyCyclePoignet += 0.00005;
        }
        if (dutyCyclePoignet < 0.025)
        {
          dutyCyclePoignet = 0.025;
        }
        else if (dutyCyclePoignet > 0.115)
        {
          dutyCyclePoignet = 0.115;
        }
        ServoPoignet.write(dutyCyclePoignet);
        // Code du servo Pince
        if (data[5] >= 85 && data[5] <= 170)
        {
        }
        else if (data[5] >= 0 && data[5] < 85)
        {
          dutyCyclePince -= 0.00005;
        }
        else if (data[5] >= 170 && data[5] <= 255)
        {
          dutyCyclePince += 0.00005;
        }
        if (dutyCyclePince < 0.08)
        {
          dutyCyclePince = 0.08;
        }
        else if (dutyCyclePince > 0.125)
        {
          dutyCyclePince = 0.125;
        }
        ServoPince.write(dutyCyclePince);
      }
      //etat_actuel = attente_trame;

      break;
    }
  }
}