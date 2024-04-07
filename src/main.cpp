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
uint8_t flagVitesseStepper = 0;

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

void VerifStepper()
{
  flagStepper += 1;
  if (flagVitesseStepper == 1){
    if (flagStepper > 14)
    {
      flagStepper = 14;
    }
  } else if (flagVitesseStepper == 2){
    if (flagStepper > 13)
    {
      flagStepper = 13;
    }
  } else if (flagVitesseStepper == 3){
    if (flagStepper > 12)
    {
      flagStepper = 12;
    }
  } else if (flagVitesseStepper == 4){
    if (flagStepper > 11)
    {
      flagStepper = 11;
    }
  } else if (flagVitesseStepper == 5){
    if (flagStepper > 10)
    {
      flagStepper = 10;
    }
  } else if (flagVitesseStepper == 6){
    if (flagStepper > 9)
    {
      flagStepper = 9;
    }
  } else if (flagVitesseStepper == 7){
    if (flagStepper > 8)
    {
      flagStepper = 8;
    }
  } else if (flagVitesseStepper == 8){
    if (flagStepper > 7)
    {
      flagStepper = 7;
    }
  } else if (flagVitesseStepper == 9){
    if (flagStepper > 6)
    {
      flagStepper = 6;
    }
  } else if (flagVitesseStepper == 10){
    if (flagStepper > 5)
    {
      flagStepper = 5;
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
  InterruptionStepper.attach(&VerifStepper, 0.0003);

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
      if ((data[9] >= 135 && data[9] < 147) || (data[9] >= 108 && data[9] < 120) )
      {
        flagVitesseStepper = 1;
        if (flagStepper == 14)
        {
          flagStepper = 0;
          ConfigVitesseStepperEpaule(data[9]);
        }
      } else if ((data[9] >= 147 && data[9] < 159) || (data[9] >= 96 && data[9] < 108) )
      {
        flagVitesseStepper = 2;
        if (flagStepper == 13)
        {
          flagStepper = 0;
          ConfigVitesseStepperEpaule(data[9]);
        }
      } else if ((data[9] >= 159 && data[9] < 171) || (data[9] >= 84 && data[9] < 96) )
      {
        flagVitesseStepper = 3;
        if (flagStepper == 12)
        {
          flagStepper = 0;
          ConfigVitesseStepperEpaule(data[9]);
        }
      } else if ((data[9] >= 171 && data[9] < 183) || (data[9] >= 72 && data[9] < 84) )
      {
        flagVitesseStepper = 4;
        if (flagStepper == 11)
        {
          flagStepper = 0;
          ConfigVitesseStepperEpaule(data[9]);
        }
      } else if ((data[9] >= 183 && data[9] < 195) || (data[9] >= 60 && data[9] < 72) )
      {
        flagVitesseStepper = 5;
        if (flagStepper == 10)
        {
          flagStepper = 0;
          ConfigVitesseStepperEpaule(data[9]);
        }
      } else if ((data[9] >= 195 && data[9] < 207) || (data[9] >= 48 && data[9] < 60) )
      {
        flagVitesseStepper = 6;
        if (flagStepper == 9)
        {
          flagStepper = 0;
          ConfigVitesseStepperEpaule(data[9]);
        }
      } else if ((data[9] >= 207 && data[9] < 219) || (data[9] >= 36 && data[9] < 48) )
      {
        flagVitesseStepper = 7;
        if (flagStepper == 8)
        {
          flagStepper = 0;
          ConfigVitesseStepperEpaule(data[9]);
        }
      } else if ((data[9] >= 219 && data[9] < 231) || (data[9] >= 24 && data[9] < 36) )
      {
        flagVitesseStepper = 8;
        if (flagStepper == 7)
        {
          flagStepper = 0;
          ConfigVitesseStepperEpaule(data[9]);
        }
      } else if ((data[9] >= 231 && data[9] < 243) || (data[9] >= 12 && data[9] < 24) )
      {
        flagVitesseStepper = 9;
        if (flagStepper == 6)
        {
          flagStepper = 0;
          ConfigVitesseStepperEpaule(data[9]);
        }
      } else if ((data[9] >= 243) || (data[9] >= 0 && data[9] < 12) )
      {
        flagVitesseStepper = 10;
        if (flagStepper == 5)
        {
          flagStepper = 0;
          ConfigVitesseStepperEpaule(data[9]);
        }
      } 
    
      if (flagServo == 1)
      {
        flagServo = 0;
        // Code du servo Coude
        if (data[8] >= 85 && data[8] <= 170)
        {
        }
        else if (data[8] >= 0 && data[8] < 85)
        {
          dutyCycleCoude -= vitesse;
        }
        else if (data[8] >= 170 && data[8] <= 255)
        {
          dutyCycleCoude += vitesse;
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
        if (data[7] >= 85 && data[7] <= 170)
        {
        }
        else if (data[7] >= 0 && data[7] < 85)
        {
          dutyCyclePoignet -= vitesse;
        }
        else if (data[7] >= 170 && data[7] <= 255)
        {
          dutyCyclePoignet += vitesse;
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
        if (data[5] == 0)
        {
        }
        else if (data[5] == 1)
        {
          dutyCyclePince -= vitesse;
        }
        else if (data[5] == 2)
        {
          dutyCyclePince += vitesse;
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