#include "mbed.h"

BufferedSerial pc(PB_6, PB_7); // USBTX et USBRX sont les broches de communication série sur la carte Nucleo STM32F072RB
uint8_t buffer[15];

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
float dutyCyclePince = 0.08;   // Fermer = 0.025 =    Ouvrir = 0.125 =

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
  InterruptionServo.attach(&VerifServo, 0.002);
  InterruptionStepper.attach(&VerifStepper, 0.002);

  // ServoCoude.period_ms(1);
  buffer[3] = 100;
  buffer[4] = 100;
  buffer[5] = 100;
  buffer[6] = 100;
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

      while (pc.readable() == 0)
      {
      }
      LED = 0;
      etat_actuel = mouvement_moteur;
      break;
    case mouvement_moteur:
      if (pc.readable())
      {
        pc.read(&currentChar, 1);
        if (currentChar == '#')
        {
          buffer[0] = currentChar;
          flag_protection++;
        }
        else if (currentChar == '@' && flag_protection == 1)
        {
          buffer[1] = currentChar;
          flag_protection++;
        }
        else if (currentChar == '+' && flag_protection == 2)
        {
          buffer[2] = currentChar;
          flag_protection++;
          for (int i = 3; i <= 7; i++)
          {
            pc.read(&currentChar, 1);
            buffer[i] = currentChar;
          }
        }
        else if (currentChar == '?' && flag_protection == 3)
        {
          buffer[8] = currentChar;
          flag_protection++;
        }
        else if (currentChar == '%' && flag_protection == 4)
        {
          buffer[9] = currentChar;
          flag_protection = 0;
          pc.write(buffer, 10);
        }
        else
        {
          memset(buffer, 0, 10);
        }
        // LED = int(buffer[7]);
      }

      if (flagStepper == 1)
      {
        flagStepper = 0;
        if (buffer[3] >= 85 && buffer[3] <= 170)
        {
          stepPinB = 0;
        }
        else if (buffer[3] >= 0 && buffer[3] < 85)
        {
          dirPinB = 0;
          stepPinB = !stepPinB;
        }
        else if (buffer[3] >= 170 && buffer[3] <= 270)
        {
          dirPinB = 1;
          stepPinB = !stepPinB;
        }

        if (buffer[6] >= 85 && buffer[6] <= 170)
        {
          stepPinC = 0;
        }
        else if (buffer[6] >= 0 && buffer[6] < 85)
        {
          dirPinC = 0;
          stepPinC = !stepPinC;
        }
        else if (buffer[6] >= 170 && buffer[6] <= 270)
        {
          dirPinC = 1;
          stepPinC = !stepPinC;
        }
      }

      if (flagServo == 1)
      {
        flagServo = 0;
        // Code du servo Poignet
        if (buffer[5] >= 85 && buffer[5] <= 170)
        {
        }
        else if (buffer[5] >= 0 && buffer[5] < 85)
        {
          dutyCycleCoude -= 0.00005;
        }
        else if (buffer[5] >= 170 && buffer[5] <= 255)
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
        if (buffer[4] >= 85 && buffer[4] <= 170)
        {
        }
        else if (buffer[4] >= 0 && buffer[4] < 85)
        {
          dutyCyclePoignet -= 0.00005;
        }
        else if (buffer[4] >= 170 && buffer[4] <= 255)
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
        if (buffer[7] >= 85 && buffer[7] <= 170)
        {
        }
        else if (buffer[7] >= 0 && buffer[7] < 85)
        {
          dutyCyclePince -= 0.00005;
        }
        else if (buffer[7] >= 170 && buffer[7] <= 255)
        {
          dutyCyclePince += 0.00005;
        }
        if (dutyCyclePince < 0.05)
        {
          dutyCyclePince = 0.05;
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