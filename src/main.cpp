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
Ticker InterruptionStepperEpaule, InterruptionStepperBase;

char startMarker[] = "#@+";
char endMarker[] = "?%";
char currentChar;

uint8_t flagBT = 0;
int flag_protection = 0;
int flagStepperEpaule = 0, flagStepperBase = 0;
int flagServo = 0;
uint8_t flagVitesseStepperEpaule = 0, flagVitesseStepperBase = 0;

float dutyCycleCoude = 0.03;   // Min = 0.03   Max = 0.125
float dutyCyclePoignet = 0.09; // Min = 0.025   Max = 0.115
float dutyCyclePince = 0.08;   // Fermer = 0.08     Ouvrir = 0.125

float servoInterval = 0.001;
float stepperInterval = 0.001;

float vitesse = 0.0;

enum etat
{
  depart,
  mouvement_moteur,
  lecture_trame,
  lecture_vitesse
};

void VerifServo()
{
  flagServo = 1;
}

/*void VerifStepperEpaule()
{
   else if (flagVitesseStepperEpaule == 7){
    if (flagStepperEpaule > 8)
    {
      flagStepperEpaule = 8;
    }
  } else if (flagVitesseStepperEpaule == 8){
    if (flagStepperEpaule > 7)
    {
      flagStepperEpaule = 7;
    }
  } else if (flagVitesseStepperEpaule == 9){
    if (flagStepperEpaule > 6)
    {
      flagStepperEpaule = 6;
    }
  } else if (flagVitesseStepperEpaule == 10){
    if (flagStepperEpaule > 5)
    {
      flagStepperEpaule = 5;
    }
  }
}*/

void VerifStepperBase()
{
  flagStepperEpaule += 1;
  if (flagVitesseStepperEpaule == 1)
  {
    if (flagStepperEpaule > 20)
    {
      flagStepperEpaule = 20;
    }
  }
  else if (flagVitesseStepperEpaule == 2)
  {
    if (flagStepperEpaule > 17)
    {
      flagStepperEpaule = 17;
    }
  }
  else if (flagVitesseStepperEpaule == 3)
  {
    if (flagStepperEpaule > 14)
    {
      flagStepperEpaule = 14;
    }
  }
  else if (flagVitesseStepperEpaule == 4)
  {
    if (flagStepperEpaule > 11)
    {
      flagStepperEpaule = 11;
    }
  }
  else if (flagVitesseStepperEpaule == 5)
  {
    if (flagStepperEpaule > 8)
    {
      flagStepperEpaule = 8;
    }
  }
  else if (flagVitesseStepperEpaule == 6)
  {
    if (flagStepperEpaule > 5)
    {
      flagStepperEpaule = 5;
    }
  }

  flagStepperBase += 1;
  if (flagVitesseStepperBase == 1)
  {
    if (flagStepperBase > 20)
    {
      flagStepperBase = 20;
    }
  }
  else if (flagVitesseStepperBase == 2)
  {
    if (flagStepperBase > 17)
    {
      flagStepperBase = 17;
    }
  }
  else if (flagVitesseStepperBase == 3)
  {
    if (flagStepperBase > 14)
    {
      flagStepperBase = 14;
    }
  }
  else if (flagVitesseStepperBase == 4)
  {
    if (flagStepperBase > 11)
    {
      flagStepperBase = 11;
    }
  }
  else if (flagVitesseStepperBase == 5)
  {
    if (flagStepperBase > 8)
    {
      flagStepperBase = 8;
    }
  }
  else if (flagVitesseStepperBase == 6)
  {
    if (flagStepperBase > 5)
    {
      flagStepperBase = 5;
    }
  }
}

void ConfigVitesseStepperBase(uint8_t valeur_joystick)
{
  // Stepper base
  if (valeur_joystick >= 120 && valeur_joystick <= 135)
  {
    stepPinB = 0;
  }
  else if (valeur_joystick >= 0 && valeur_joystick < 120)
  {
    dirPinB = 0;
  }
  else if (valeur_joystick >= 120 && valeur_joystick <= 255)
  {
    dirPinB = 1;
  }
  stepPinB = !stepPinB;
}

void ConfigVitesseStepperEpaule(uint8_t valeur_joystick)
{
  // Stepper base
  if (valeur_joystick >= 120 && valeur_joystick <= 135)
  {
    stepPinC = 0;
  }
  else if (valeur_joystick >= 0 && valeur_joystick < 120)
  {
    dirPinC = 0;
  }
  else if (valeur_joystick >= 120 && valeur_joystick <= 255)
  {
    dirPinC = 1;
  }
  stepPinC = !stepPinC;
}

int main()
{
  InterruptionServo.attach(&VerifServo, 0.001);
  InterruptionStepperBase.attach(&VerifStepperBase, 0.0002);

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
        thread_sleep_for(1);
        stepPinC = 0;
        thread_sleep_for(1);
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

      // stepPinC = 0;
      // stepPinB = 0;

      etat_actuel = lecture_trame;
      break;
    case lecture_trame:
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
      etat_actuel = mouvement_moteur;
      break;
    case mouvement_moteur:
      if (data[9] >= 120 && data[9] <= 135)
      {
        stepPinC = 0;
      }
      if ((data[9] >= 135 && data[9] < 160) || (data[9] >= 95 && data[9] < 120))
      {
        flagVitesseStepperEpaule = 1;
        if (flagStepperEpaule == 20)
        {
          flagStepperEpaule = 0;
          ConfigVitesseStepperEpaule(data[9]);
        }
      }
      else if ((data[9] >= 160 && data[9] < 185) || (data[9] >= 70 && data[9] < 95))
      {
        flagVitesseStepperEpaule = 2;
        if (flagStepperEpaule == 17)
        {
          flagStepperEpaule = 0;
          ConfigVitesseStepperEpaule(data[9]);
        }
      }
      else if ((data[9] >= 185 && data[9] < 210) || (data[9] >= 45 && data[9] < 70))
      {
        flagVitesseStepperEpaule = 3;
        if (flagStepperEpaule == 14)
        {
          flagStepperEpaule = 0;
          ConfigVitesseStepperEpaule(data[9]);
        }
      }
      else if ((data[9] >= 210 && data[9] < 230) || (data[9] >= 25 && data[9] < 45))
      {
        flagVitesseStepperEpaule = 4;
        if (flagStepperEpaule == 11)
        {
          flagStepperEpaule = 0;
          ConfigVitesseStepperEpaule(data[9]);
        }
      }
      else if ((data[9] >= 230 && data[9] < 250) || (data[9] >= 5 && data[9] < 25))
      {
        flagVitesseStepperEpaule = 5;
        if (flagStepperEpaule == 8)
        {
          flagStepperEpaule = 0;
          ConfigVitesseStepperEpaule(data[9]);
        }
      }
      else if ((data[9] >= 250 && data[9] <= 255) || (data[9] >= 0 && data[9] < 5))
      {
        flagVitesseStepperEpaule = 6;
        if (flagStepperEpaule == 5)
        {
          flagStepperEpaule = 0;
          ConfigVitesseStepperEpaule(data[9]);
        }
      }

      if (data[6] >= 120 && data[6] <= 135)
      {
        stepPinB = 0;
      }
      if ((data[6] >= 135 && data[6] < 160) || (data[6] >= 95 && data[6] < 120))
      {
        flagVitesseStepperBase = 1;
        if (flagStepperBase == 20)
        {
          flagStepperBase = 0;
          ConfigVitesseStepperBase(data[6]);
        }
      }
      else if ((data[6] >= 160 && data[6] < 185) || (data[6] >= 70 && data[6] < 95))
      {
        flagVitesseStepperBase = 2;
        if (flagStepperBase == 17)
        {
          flagStepperBase = 0;
          ConfigVitesseStepperBase(data[6]);
        }
      }
      else if ((data[6] >= 185 && data[6] < 210) || (data[6] >= 45 && data[6] < 70))
      {
        flagVitesseStepperBase = 3;
        if (flagStepperBase == 14)
        {
          flagStepperBase = 0;
          ConfigVitesseStepperBase(data[6]);
        }
      }
      else if ((data[6] >= 210 && data[6] < 230) || (data[6] >= 25 && data[6] < 45))
      {
        flagVitesseStepperBase = 4;
        if (flagStepperBase == 11)
        {
          flagStepperBase = 0;
          ConfigVitesseStepperBase(data[6]);
        }
      }
      else if ((data[6] >= 230 && data[6] < 250) || (data[6] >= 5 && data[6] < 25))
      {
        flagVitesseStepperBase = 5;
        if (flagStepperBase == 8)
        {
          flagStepperBase = 0;
          ConfigVitesseStepperBase(data[6]);
        }
      }
      else if ((data[6] >= 250 && data[6] <= 255) || (data[6] >= 0 && data[6] < 5))
      {
        flagVitesseStepperBase = 6;
        if (flagStepperBase == 5)
        {
          flagStepperBase = 0;
          ConfigVitesseStepperBase(data[6]);
        }
      } /*else if ((data[6] >= 207 && data[96] < 219) || (data[6] >= 36 && data[6] < 48) )
      {
        flagVitesseStepperBase = 7;
        if (flagStepperBase == 8)
        {
          flagStepperBase = 0;
          ConfigVitesseStepperBase(data[6]);
        }
      } else if ((data[6] >= 219 && data[6] < 231) || (data[6] >= 24 && data[6] < 36) )
      {
        flagVitesseStepperBase = 8;
        if (flagStepperBase == 7)
        {
          flagStepperBase = 0;
          ConfigVitesseStepperBase(data[6]);
        }
      } else if ((data[6] >= 231 && data[6] < 243) || (data[6] >= 12 && data[6] < 24) )
      {
        flagVitesseStepperBase = 9;
        if (flagStepperBase == 6)
        {
          flagStepperBase = 0;
          ConfigVitesseStepperBase(data[6]);
        }
      } else if ((data[6] >= 243) || (data[6] >= 0 && data[6] < 12) )
      {
        flagVitesseStepperBase = 10;
        if (flagStepperBase == 5)
        {
          flagStepperBase = 0;
          ConfigVitesseStepperBase(data[6]);
        }
      }*/

      if (flagServo == 1)
      {
        flagServo = 0;
        // Code du servo Coude
        if ((data[8] >= 135 && data[8] < 160) || (data[8] >= 95 && data[8] < 120))
        {
          if (data[8] >= 135 && data[8] < 160)
          {
            dutyCycleCoude += 0.00001;
          }
          else if (data[8] >= 95 && data[8] < 120)
          {
            dutyCycleCoude -= 0.00001;
          }
        }
        else if ((data[8] >= 160 && data[8] < 185) || (data[8] >= 70 && data[8] < 95))
        {
          if (data[8] >= 160 && data[8] < 185)
          {
            dutyCycleCoude += 0.00002;
          }
          else if (data[8] >= 70 && data[8] < 95)
          {
            dutyCycleCoude -= 0.00002;
          }
        }
        else if ((data[8] >= 185 && data[8] < 210) || (data[8] >= 45 && data[8] < 70))
        {
          if (data[8] >= 185 && data[8] < 210)
          {
            dutyCycleCoude += 0.00003;
          }
          else if (data[8] >= 45 && data[8] < 70)
          {
            dutyCycleCoude -= 0.00003;
          }
        }
        else if ((data[8] >= 210 && data[8] < 230) || (data[8] >= 25 && data[8] < 45))
        {
          if (data[8] >= 210 && data[8] < 230)
          {
            dutyCycleCoude += 0.00004;
          }
          else if (data[8] >= 25 && data[8] < 45)
          {
            dutyCycleCoude -= 0.00004;
          }
        }
        else if ((data[8] >= 230 && data[8] < 250) || (data[8] >= 5 && data[8] < 25))
        {
          if (data[8] >= 230 && data[8] < 250)
          {
            dutyCycleCoude += 0.00005;
          }
          else if (data[8] >= 5 && data[8] < 25)
          {
            dutyCycleCoude -= 0.00005;
          }
        }
        else if ((data[8] >= 250 && data[8] <= 255) || (data[8] >= 0 && data[8] < 5))
        {
          if (data[8] >= 250 && data[8] <= 255)
          {
            dutyCycleCoude += 0.00006;
          }
          else if (data[8] >= 0 && data[8] < 5)
          {
            dutyCycleCoude -= 0.00006;
          }
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

        // Code du servo Poignet
        if ((data[7] >= 135 && data[7] < 160) || (data[7] >= 95 && data[7] < 120))
        {
          if (data[7] >= 135 && data[7] < 160)
          {
            dutyCyclePoignet += 0.00001;
          }
          else if (data[7] >= 95 && data[7] < 120)
          {
            dutyCyclePoignet -= 0.00001;
          }
        }
        else if ((data[7] >= 160 && data[7] < 185) || (data[7] >= 70 && data[7] < 95))
        {
          if (data[7] >= 160 && data[7] < 185)
          {
            dutyCyclePoignet += 0.00002;
          }
          else if (data[7] >= 70 && data[7] < 95)
          {
            dutyCyclePoignet -= 0.00002;
          }
        }
        else if ((data[7] >= 185 && data[7] < 210) || (data[7] >= 45 && data[7] < 70))
        {
          if (data[7] >= 185 && data[7] < 210)
          {
            dutyCyclePoignet += 0.00003;
          }
          else if (data[7] >= 45 && data[7] < 70)
          {
            dutyCyclePoignet -= 0.00003;
          }
        }
        else if ((data[7] >= 210 && data[7] < 230) || (data[7] >= 25 && data[7] < 45))
        {
          if (data[7] >= 210 && data[7] < 230)
          {
            dutyCyclePoignet += 0.00004;
          }
          else if (data[7] >= 25 && data[7] < 45)
          {
            dutyCyclePoignet -= 0.00004;
          }
        }
        else if ((data[7] >= 230 && data[7] < 250) || (data[7] >= 5 && data[7] < 25))
        {
          if (data[7] >= 230 && data[7] < 250)
          {
            dutyCyclePoignet += 0.00005;
          }
          else if (data[7] >= 5 && data[7] < 25)
          {
            dutyCyclePoignet -= 0.00005;
          }
        }
        else if ((data[7] >= 250 && data[7] <= 255) || (data[7] >= 0 && data[7] < 5))
        {
          if (data[7] >= 250 && data[7] <= 255)
          {
            dutyCyclePoignet += 0.00006;
          }
          else if (data[7] >= 0 && data[7] < 5)
          {
            dutyCyclePoignet -= 0.00006;
          }
        }
        if (dutyCyclePoignet < 0.03)
        {
          dutyCyclePoignet = 0.03;
        }
        else if (dutyCyclePoignet > 0.125)
        {
          dutyCyclePoignet = 0.125;
        }
        ServoPoignet.write(dutyCyclePoignet);
        // Code du servo Pince
        if (data[5] == 0)
        {
        }
        else if (data[5] == 1)
        {
          dutyCyclePince -= 0.00005;
        }
        else if (data[5] == 2)
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
      etat_actuel = lecture_trame;
      break;
    }
  }
}