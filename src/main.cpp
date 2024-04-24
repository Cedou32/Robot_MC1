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

SPI spi(PA_7, PA_6, PA_5); // mosi, miso, sck
DigitalOut cs2(PC_4);      // CS U2
DigitalOut cs3(PC_5);      // CS U3
uint8_t ecriture[5];
uint8_t lecture[5];

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
int16_t valeur_encodeur = 0;
uint8_t ancien_mode = 0;
int16_t resultat_encodeur = 0;

//*****Enregistrement******//
uint8_t buffer_enregsitrement_1[500];
uint8_t buffer_enregsitrement_2[500];
uint8_t buffer_enregsitrement_3[500];
uint8_t buff[500];

uint16_t flag_10_sec = 0;
uint8_t flag_10_sec_termine = 0;
uint8_t flag_rejouer_10sec = 0;
uint8_t flag_reception_trame = 0;
uint8_t flag_enregistrement_1 = 0;
uint8_t flag_enregistrement_2 = 0;
uint8_t flag_enregistrement_3 = 0;

uint16_t curseur_enregistrement = 0;

uint8_t nouvelEnregistrement = 0;
uint8_t ancienEnregistrement = 0;

//*****Libre******//
bool flag_libre = 0;

//*******Debug*******//
bool flag_debug_1 = 0;
bool flag_debug_2 = 0;
bool flag_debug_3 = 0;
bool flag_debug_4 = 0;

/******Demo*******/
int flag_protectionDemo = 0;
bool flagDemo = 0;

char currentCharDemo;

uint8_t dataDemo[10];
enum etat
{
  depart,
  lecture_trame,
  detection_mode,
  libre,
  enregistrement,
  demo,
  deboguage,
  retour_maison,
  rejouer_sequence,
  lecture_vitesse
};

void VerifServoEtLecture()
{
  flagServo = 1;
  flag_rejouer_10sec += 1;
  flag_10_sec += 1;
}

void VerifStepper()
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
  else if (valeur_joystick >= 135 && valeur_joystick <= 255)
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
    valeur_encodeur += 1;
  }
  else if (valeur_joystick >= 135 && valeur_joystick <= 255)
  {
    dirPinC = 1;
    valeur_encodeur -= 1;
  }
  stepPinC = !stepPinC;
}

void MouvementMoteur(void)
{
  //**********Stepper Épaule************//
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
  //**********Stepper 360************/
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
  }

  if (flagServo == 1)
  {
    flagServo = 0;
    //*********Servo Coude//
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

    //**********Servo Poignet//
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
    else if (dutyCyclePoignet > 0.115)
    {
      dutyCyclePoignet = 0.115;
    }
    ServoPoignet.write(dutyCyclePoignet);
    //**********Servo Pince//
    if (data[5] == 0)
    {
    }
    else if (data[5] == 2)
    {
      dutyCyclePince -= 0.00005;
    }
    else if (data[5] == 1)
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
}

void EcritureEEPROM(uint8_t ecriture[])
{
  LED = !LED;
  cs2 = 0;
  spi.write(0x06);
  cs2 = 1;

  cs2 = 0;
  spi.write(0x02);
  spi.write(0x00);
  spi.write(0x01);
  spi.write(0x00);
  for (int i = 0; i < sizeof(ecriture); i++)
  {
    spi.write(ecriture[i]);
  }
  cs2 = 1;

  /*cs2 = 0;
  spi.write(0x06);
  cs2 = 1;

  cs2 = 0;
  spi.write(0x02);
  spi.write(0x00);
  spi.write(0x02);
  spi.write(0x00);
  for (int i = 250; i < 500; i++)
  {
    spi.write(ecriture[i]);
  }
  cs2 = 1;*/
}

void LectureEEPROM()
{
  cs2 = 0;         // Select EEPROM
  spi.write(0x03); // Read command
  spi.write(0x00);
  spi.write(0x01);
  spi.write(0x00);
  for (int i = 0; i < 250; i++)
  {
    lecture[i] = spi.write(0);
  }
  cs2 = 1; // Deselect EEPROM

  cs2 = 0;         // Select EEPROM
  spi.write(0x03); // Read command
  spi.write(0x00);
  spi.write(0x02);
  spi.write(0x00);
  for (int i = 250; i < 500; i++)
  {
    lecture[i] = spi.write(0);
  }
  cs2 = 1;
}

void Enregistrement(uint8_t enregistrement)
{
  if (flag_reception_trame == 1)
  {
    buff[curseur_enregistrement] = data[5];
    // pc.write(&buff[curseur_enregistrement], 1);
    curseur_enregistrement++;
    buff[curseur_enregistrement] = data[6];
    // pc.write(&buff[curseur_enregistrement], 1);
    curseur_enregistrement++;
    buff[curseur_enregistrement] = data[7];
    // pc.write(&buff[curseur_enregistrement], 1);
    curseur_enregistrement++;
    buff[curseur_enregistrement] = data[8];
    // pc.write(&buff[curseur_enregistrement], 1);
    curseur_enregistrement++;
    buff[curseur_enregistrement] = data[9];
    // pc.write(&buff[curseur_enregistrement], 1);
    curseur_enregistrement++;
    flag_reception_trame = 0;
  }
  if (curseur_enregistrement == 495)
  {
    curseur_enregistrement = 0;
  }
  /*
  uint8_t high = curseur_enregistrement >> 8;
  uint8_t low = curseur_enregistrement;

  pc.write(&high, 1);
  pc.write(&low, 1);*/

  switch (enregistrement)
  {
  case 1:
    memcpy(buffer_enregsitrement_1, buff, sizeof(buff));
    break;
  case 2:
    memcpy(buffer_enregsitrement_2, buff, sizeof(buff));
    break;
  case 3:
    memcpy(buffer_enregsitrement_3, buff, sizeof(buff));
    break;
  }
}

void  Rejouer(uint8_t enregistrement)
{
  switch (enregistrement)
  {
  case 1:
    memcpy(buff, buffer_enregsitrement_1, sizeof(buffer_enregsitrement_1));
    break;
  case 2:
    memcpy(buff, buffer_enregsitrement_2, sizeof(buffer_enregsitrement_2));
    break;
  case 3:
    memcpy(buff, buffer_enregsitrement_3, sizeof(buffer_enregsitrement_3));
    break;
  }

  if (flag_enregistrement_1 == 1)
  {
    // flag_enregistrement_1 = 0;
    for (uint16_t i = 0; i < 100; i++)
    {
      data[5] = buff[i * 5];
      data[6] = buff[(i * 5) + 1];
      data[7] = buff[(i * 5) + 2];
      data[8] = buff[(i * 5) + 3];
      data[9] = buff[(i * 5) + 4];
      flag_rejouer_10sec = 0;
      while (flag_rejouer_10sec < 100)
      {
        MouvementMoteur();
      }
      flag_rejouer_10sec = 0;
    }
  }
}

void LectureDemo()
{
  if (pc.readable())
  {
    pc.read(&currentCharDemo, 1);
    if (currentCharDemo == '#')
    {
      flag_protectionDemo++;
    }
    else if (currentCharDemo == '@' && flag_protectionDemo == 1)
    {
      flag_protectionDemo++;
    }
    else if (currentCharDemo == '+' && flag_protectionDemo == 2)
    {
      flag_protectionDemo++;
      for (int i = 0; i <= 9; i++)
      {
        pc.read(&currentCharDemo, 1);
        dataDemo[i] = currentCharDemo;
      }
    }
    else if (currentCharDemo == '?' && flag_protectionDemo == 3)
    {
      flag_protectionDemo++;
    }
    else if (currentCharDemo == '%' && flag_protectionDemo == 4)
    {
      flag_protectionDemo = 0;
      // pc.write(data, 10);
    }
    else
    {
      memset(dataDemo, 125, 10);
    }
  }
}
int main()
{

  spi.format(8, 0);
  spi.frequency(5000000);

  InterruptionServo.attach(&VerifServoEtLecture, 0.001);
  InterruptionStepperBase.attach(&VerifStepper, 0.0002);

  data[5] = 125;
  data[6] = 125;
  data[7] = 125;
  data[8] = 125;
  data[9] = 125;

  pc.set_baud(115200);
  etat etat_actuel = depart;
  while (1)
  {
    switch (etat_actuel)
    {
    case depart:
      // LED = 1;
      for (int i = 0; i <= 750; i++)
      {
        stepPinC = 1;
        wait_us(2000);
        stepPinC = 0;
        wait_us(2000);
      }
      thread_sleep_for(1000);
      ServoCoude.write(0.03);
      thread_sleep_for(1000);
      ServoPoignet.write(0.09);
      thread_sleep_for(1000);
      ServoPince.write(0.12);
      thread_sleep_for(1000);
      ServoPince.write(0.08);
      thread_sleep_for(1000);

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
          flag_reception_trame = 1;
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
          // pc.write(data, 10);
        }
        else
        {
          memset(data, 125, 10);
        }
      }
      etat_actuel = detection_mode;
      break;
    case detection_mode:
      if (data[0] == 0)
      {
        etat_actuel = retour_maison;
      }
      else if (data[0] == 1)
      {
        if (ancien_mode > 1)
        {
          flag_libre = 1;
          etat_actuel = retour_maison;
        }
        else if (ancien_mode == 1)
        {
          etat_actuel = libre;
        }
        else if (ancien_mode == 0)
        {
          etat_actuel = libre;
        }
        ancien_mode = 1;
      }
      else if (data[0] == 2)
      {
        if (ancien_mode > 2 || (ancien_mode < 2 && ancien_mode > 0))
        {
          etat_actuel = retour_maison;
        }
        else if (ancien_mode == 2)
        {
          etat_actuel = demo;
        }
        else if (ancien_mode == 0)
        {
          etat_actuel = demo;
        }
        ancien_mode = 2;
      }
      else if (data[0] == 3)
      {
        if (ancien_mode > 3 || (ancien_mode < 3 && ancien_mode > 0))
        {
          etat_actuel = retour_maison;
        }
        else if (ancien_mode == 3)
        {
          etat_actuel = deboguage;
        }
        else if (ancien_mode == 0)
        {
          etat_actuel = deboguage;
        }
        ancien_mode = 3;
      }
      else if (data[0] == 4)
      {
        if (ancien_mode < 4 && ancien_mode > 0)
        {
          etat_actuel = retour_maison;
        }
        else if (ancien_mode == 4 && nouvelEnregistrement == 0)
        {
          etat_actuel = enregistrement;
        }
        else if (ancien_mode == 4 && nouvelEnregistrement == 1)
        {
          etat_actuel = retour_maison;
        }
        else if (ancien_mode == 0)
        {
          etat_actuel = enregistrement;
        }
        ancien_mode = 4;
      }
      else
      {
        etat_actuel = lecture_trame;
      }
      break;
    case libre:
      LED = 0;
      MouvementMoteur();
      etat_actuel = lecture_trame;
      break;
    case enregistrement:
      // LED = 0;

      if (data[2] == 1)
      {
        flag_10_sec = 0;
        flag_enregistrement_1 = 1;
        MouvementMoteur();
        Enregistrement(data[1]);
        flag_10_sec_termine = 1;
      }

      etat_actuel = lecture_trame;

      if (flag_10_sec_termine == 1 && flag_10_sec >= 10000)
      {
        etat_actuel = retour_maison;
      }
      if (flag_10_sec_termine == 1 && data[2] == 2)
      {
        // data[1] = 0;
        // flag_10_sec_termine = 0;
        etat_actuel = retour_maison;
      }
      else if (data[1] == 0)
      {
        etat_actuel = lecture_trame;
      }
      break;
    case demo:
      LED = 0;
      if (data[4] == 1)
      {
        /*********Portion steppers**********/
        dirPinB = 0;
        for (int i = 0; i < 1600; i++)
        {
          LectureDemo();
          if (dataDemo[4] == 2)
          {
            flagDemo = 1;
            break;
          }
          if (i >= 0 && i < 266)
          {
            stepPinB = 1;
            wait_us(1200);
            stepPinB = 0;
            wait_us(1200);
          }
          else if (i >= 266 && i < 532)
          {
            stepPinB = 1;
            wait_us(1600);
            stepPinB = 0;
            wait_us(1600);
          }
          else if (i >= 532 && i < 798)
          {
            stepPinB = 1;
            wait_us(2200);
            stepPinB = 0;
            wait_us(2200);
          }
          else if (i >= 798 && i < 1064)
          {
            stepPinB = 1;
            wait_us(2800);
            stepPinB = 0;
            wait_us(2800);
          }
          else if (i >= 1064 && i < 1330)
          {
            stepPinB = 1;
            wait_us(3400);
            stepPinB = 0;
            wait_us(3400);
          }
          else if (i >= 1330 && i < 1600)
          {
            stepPinB = 1;
            wait_us(4000);
            stepPinB = 0;
            wait_us(4000);
          }
        }
        dirPinB = 1;
        if (flagDemo == 1)
        {
          flagDemo = 0;
          data[4] = 0;
          etat_actuel = retour_maison;
          break;
        }
        for (int i = 0; i < 3200; i++)
        {
          LectureDemo();
          if (dataDemo[4] == 2)
          {
            flagDemo = 1;
            break;
          }
          if (i >= 0 && i < 533)
          {
            stepPinB = 1;
            wait_us(1200);
            stepPinB = 0;
            wait_us(1200);
          }
          else if (i >= 533 && i < 1066)
          {
            stepPinB = 1;
            wait_us(1600);
            stepPinB = 0;
            wait_us(1600);
          }
          else if (i >= 1066 && i < 1599)
          {
            stepPinB = 1;
            wait_us(2200);
            stepPinB = 0;
            wait_us(2200);
          }
          else if (i >= 1599 && i < 2132)
          {
            stepPinB = 1;
            wait_us(2800);
            stepPinB = 0;
            wait_us(2800);
          }
          else if (i >= 2132 && i < 2665)
          {
            stepPinB = 1;
            wait_us(3400);
            stepPinB = 0;
            wait_us(3400);
          }
          else if (i >= 2665 && i < 3200)
          {
            stepPinB = 1;
            wait_us(4000);
            stepPinB = 0;
            wait_us(4000);
          }
        }
        dirPinB = 0;
        if (flagDemo == 1)
        {
          flagDemo = 0;
          data[4] = 0;
          etat_actuel = retour_maison;
          break;
        }
        for (int i = 0; i < 1600; i++)
        {
          LectureDemo();
          if (dataDemo[4] == 2)
          {
            flagDemo = 1;
            break;
          }
          stepPinB = 1;
          wait_us(1000);
          stepPinB = 0;
          wait_us(1000);
        }
        if (flagDemo == 1)
        {
          flagDemo = 0;
          data[4] = 0;
          etat_actuel = retour_maison;
          break;
        }
        thread_sleep_for(1000);
        while (dutyCycleCoude < 0.065)
        {
          LectureDemo();
          if (dataDemo[4] == 2)
          {
            flagDemo = 1;
            break;
          }
          wait_us(500);
          dutyCycleCoude += 0.00001;
          ServoCoude.write(dutyCycleCoude);
        }
        thread_sleep_for(1000);
        dirPinC = 1;
        for (int i = 0; i < 750; i++)
        {
          LectureDemo();
          if (dataDemo[4] == 2)
          {
            flagDemo = 1;
            break;
          }
          valeur_encodeur -= 2;
          if (i >= 0 && i < 133)
          {
            stepPinC = 1;
            wait_us(1200);
            stepPinC = 0;
            wait_us(1200);
          }
          else if (i >= 133 && i < 266)
          {
            stepPinC = 1;
            wait_us(1600);
            stepPinC = 0;
            wait_us(1600);
          }
          else if (i >= 266 && i < 399)
          {
            stepPinC = 1;
            wait_us(2200);
            stepPinC = 0;
            wait_us(2200);
          }
          else if (i >= 399 && i < 532)
          {
            stepPinC = 1;
            wait_us(2800);
            stepPinC = 0;
            wait_us(2800);
          }
          else if (i >= 532 && i < 665)
          {
            stepPinC = 1;
            wait_us(3400);
            stepPinC = 0;
            wait_us(3400);
          }
          else if (i >= 665 && i < 800)
          {
            stepPinC = 1;
            wait_us(4000);
            stepPinC = 0;
            wait_us(4000);
          }
        }
        dirPinC = 0;
        if (flagDemo == 1)
        {
          flagDemo = 0;
          etat_actuel = retour_maison;
          break;
        }
        for (int i = 0; i < 750; i++)
        {
          LectureDemo();
          if (dataDemo[4] == 2)
          {
            flagDemo = 1;
            break;
          }
          valeur_encodeur += 2;
          if (i >= 0 && i < 133)
          {
            stepPinC = 1;
            wait_us(4000);
            stepPinC = 0;
            wait_us(4000);
          }
          else if (i >= 133 && i < 266)
          {
            stepPinC = 1;
            wait_us(3400);
            stepPinC = 0;
            wait_us(3400);
          }
          else if (i >= 266 && i < 399)
          {
            stepPinC = 1;
            wait_us(2800);
            stepPinC = 0;
            wait_us(2800);
          }
          else if (i >= 399 && i < 532)
          {
            stepPinC = 1;
            wait_us(2200);
            stepPinC = 0;
            wait_us(2200);
          }
          else if (i >= 532 && i < 665)
          {
            stepPinC = 1;
            wait_us(1600);
            stepPinC = 0;
            wait_us(1600);
          }
          else if (i >= 665 && i < 800)
          {
            stepPinC = 1;
            wait_us(1200);
            stepPinC = 0;
            wait_us(1200);
          }
        }
        if (flagDemo == 1)
        {
          flagDemo = 0;
          etat_actuel = retour_maison;
          break;
        }
        while (dutyCycleCoude > 0.03)
        {
          LectureDemo();
          if (dataDemo[4] == 2)
          {
            flagDemo = 1;
            break;
          }
          wait_us(500);
          dutyCycleCoude -= 0.00001;
          ServoCoude.write(dutyCycleCoude);
        }
        thread_sleep_for(500);
        if (flagDemo == 1)
        {
          flagDemo = 0;
          etat_actuel = retour_maison;
          break;
        }
        /************Portion servo Coude*************/
        while (dutyCyclePoignet > 0.08)
        {
          LectureDemo();
          if (dataDemo[4] == 2)
          {
            flagDemo = 1;
            break;
          }
          wait_us(500);
          dutyCyclePoignet -= 0.00001;
          ServoPoignet.write(dutyCyclePoignet);
        }
        if (flagDemo == 1)
        {
          flagDemo = 0;
          etat_actuel = retour_maison;
          break;
        }
        thread_sleep_for(500);
        dirPinC = 1;
        for (int i = 0; i < 200; i++)
        {
          LectureDemo();
          if (dataDemo[4] == 2)
          {
            flagDemo = 1;
            break;
          }
          valeur_encodeur--;
          stepPinC = 1;
          wait_us(1250);
          stepPinC = 0;
          wait_us(1250);
        }
        if (flagDemo == 1)
        {
          flagDemo = 0;
          etat_actuel = retour_maison;
          break;
        }
        thread_sleep_for(1000);
        while (dutyCycleCoude < 0.077)
        {
          LectureDemo();
          if (dataDemo[4] == 2)
          {
            flagDemo = 1;
            break;
          }
          wait_us(500);
          dutyCycleCoude += 0.00001;
          ServoCoude.write(dutyCycleCoude);
        }
        if (flagDemo == 1)
        {
          flagDemo = 0;
          etat_actuel = retour_maison;
          break;
        }
        thread_sleep_for(1000);
        while (dutyCycleCoude > 0.03)
        {
          LectureDemo();
          if (dataDemo[4] == 2)
          {
            flagDemo = 1;
            break;
          }
          wait_us(500);
          dutyCycleCoude -= 0.00001;
          ServoCoude.write(dutyCycleCoude);
        }
        thread_sleep_for(1000);
        if (flagDemo == 1)
        {
          flagDemo = 0;
          etat_actuel = retour_maison;
          break;
        }
        /************Servo Poignet************/
        dirPinC = 0;
        for (int i = 0; i < 200; i++)
        {
          LectureDemo();
          if (dataDemo[4] == 2)
          {
            flagDemo = 1;
            break;
          }
          stepPinC = 1;
          wait_us(1250);
          stepPinC = 0;
          wait_us(1250);
        }
        thread_sleep_for(1000);
        if (flagDemo == 1)
        {
          flagDemo = 0;
          etat_actuel = retour_maison;
          break;
        }
        while (dutyCyclePoignet < 0.09)
        {
          LectureDemo();
          if (dataDemo[4] == 2)
          {
            flagDemo = 1;
            break;
          }
          wait_us(500);
          dutyCyclePoignet += 0.00001;
          ServoPoignet.write(dutyCyclePoignet);
        }
        if (flagDemo == 1)
        {
          flagDemo = 0;
          etat_actuel = retour_maison;
          break;
        }
        thread_sleep_for(1000);
        while (dutyCyclePoignet < 0.115)
        {
          LectureDemo();
          if (dataDemo[4] == 2)
          {
            flagDemo = 1;
            break;
          }
          wait_us(500);
          dutyCyclePoignet += 0.00001;
          ServoPoignet.write(dutyCyclePoignet);
        }
        if (flagDemo == 1)
        {
          flagDemo = 0;
          etat_actuel = retour_maison;
          break;
        }
        thread_sleep_for(1000);
        while (dutyCycleCoude < 0.05)
        {
          LectureDemo();
          if (dataDemo[4] == 2)
          {
            flagDemo = 1;
            break;
          }
          wait_us(500);
          dutyCycleCoude += 0.00001;
          ServoCoude.write(dutyCycleCoude);
        }
        if (flagDemo == 1)
        {
          flagDemo = 0;
          etat_actuel = retour_maison;
          break;
        }
        thread_sleep_for(1000);
        while (dutyCyclePoignet > 0.03)
        {
          LectureDemo();
          if (dataDemo[4] == 2)
          {
            flagDemo = 1;
            break;
          }
          wait_us(500);
          dutyCyclePoignet -= 0.00001;
          ServoPoignet.write(dutyCyclePoignet);
        }
        if (flagDemo == 1)
        {
          flagDemo = 0;
          etat_actuel = retour_maison;
          break;
        }
        thread_sleep_for(1000);
        while (dutyCyclePoignet < 0.09)
        {
          LectureDemo();
          if (dataDemo[4] == 2)
          {
            flagDemo = 1;
            break;
          }
          wait_us(500);
          dutyCyclePoignet += 0.00001;
          ServoPoignet.write(dutyCyclePoignet);
        }
        if (flagDemo == 1)
        {
          flagDemo = 0;
          etat_actuel = retour_maison;
          break;
        }
        thread_sleep_for(1000);
        while (dutyCycleCoude > 0.03)
        {
          LectureDemo();
          if (dataDemo[4] == 2)
          {
            flagDemo = 1;
            break;
          }
          wait_us(500);
          dutyCycleCoude -= 0.00001;
          ServoCoude.write(dutyCycleCoude);
        }
        if (flagDemo == 1)
        {
          flagDemo = 0;
          etat_actuel = retour_maison;
          break;
        }
        /***********Servo Pince***********/
        thread_sleep_for(1000);
        while (dutyCyclePince < 0.12)
        {
          LectureDemo();
          if (dataDemo[4] == 2)
          {
            flagDemo = 1;
            break;
          }
          wait_us(500);
          dutyCyclePince += 0.01;
          ServoPince.write(dutyCyclePince);
        }
        if (flagDemo == 1)
        {
          flagDemo = 0;
          etat_actuel = retour_maison;
          break;
        }
        thread_sleep_for(1000);
        while (dutyCyclePince > 0.08)
        {
          LectureDemo();
          if (dataDemo[4] == 2)
          {
            flagDemo = 1;
            break;
          }
          wait_us(500);
          dutyCyclePince -= 0.01;
          ServoPince.write(dutyCyclePince);
        }
        if (flagDemo == 1)
        {
          flagDemo = 0;
          etat_actuel = retour_maison;
          break;
        }
        thread_sleep_for(1000);
      }
      else if (data[4] == 0)
      {
        etat_actuel = lecture_trame;
      }
      break;
    case deboguage:
      LED = 0;
      if (data[3] == 1)
      {
        data[3] = 0;
        dirPinB = 0;
        for (int i = 0; i < 1600; i++)
        {
          if (i >= 0 && i < 266)
          {
            stepPinB = 1;
            wait_us(1200);
            stepPinB = 0;
            wait_us(1200);
          }
          else if (i >= 266 && i < 532)
          {
            stepPinB = 1;
            wait_us(1600);
            stepPinB = 0;
            wait_us(1600);
          }
          else if (i >= 532 && i < 798)
          {
            stepPinB = 1;
            wait_us(2200);
            stepPinB = 0;
            wait_us(2200);
          }
          else if (i >= 798 && i < 1064)
          {
            stepPinB = 1;
            wait_us(2800);
            stepPinB = 0;
            wait_us(2800);
          }
          else if (i >= 1064 && i < 1330)
          {
            stepPinB = 1;
            wait_us(3400);
            stepPinB = 0;
            wait_us(3400);
          }
          else if (i >= 1330 && i < 1600)
          {
            stepPinB = 1;
            wait_us(4000);
            stepPinB = 0;
            wait_us(4000);
          }
        }
        dirPinB = 1;
        for (int i = 0; i < 3200; i++)
        {
          if (i >= 0 && i < 533)
          {
            stepPinB = 1;
            wait_us(1200);
            stepPinB = 0;
            wait_us(1200);
          }
          else if (i >= 533 && i < 1066)
          {
            stepPinB = 1;
            wait_us(1600);
            stepPinB = 0;
            wait_us(1600);
          }
          else if (i >= 1066 && i < 1599)
          {
            stepPinB = 1;
            wait_us(2200);
            stepPinB = 0;
            wait_us(2200);
          }
          else if (i >= 1599 && i < 2132)
          {
            stepPinB = 1;
            wait_us(2800);
            stepPinB = 0;
            wait_us(2800);
          }
          else if (i >= 2132 && i < 2665)
          {
            stepPinB = 1;
            wait_us(3400);
            stepPinB = 0;
            wait_us(3400);
          }
          else if (i >= 2665 && i < 3200)
          {
            stepPinB = 1;
            wait_us(4000);
            stepPinB = 0;
            wait_us(4000);
          }
        }
        dirPinB = 0;
        for (int i = 0; i < 1600; i++)
        {
          stepPinB = 1;
          wait_us(1000);
          stepPinB = 0;
          wait_us(1000);
        }
        thread_sleep_for(750);
        ServoCoude.write(0.065);
        thread_sleep_for(500);
        dirPinC = 1;
        for (int i = 0; i < 750; i++)
        {
          if (i >= 0 && i < 133)
          {
            stepPinC = 1;
            wait_us(1200);
            stepPinC = 0;
            wait_us(1200);
          }
          else if (i >= 133 && i < 266)
          {
            stepPinC = 1;
            wait_us(1600);
            stepPinC = 0;
            wait_us(1600);
          }
          else if (i >= 266 && i < 399)
          {
            stepPinC = 1;
            wait_us(2200);
            stepPinC = 0;
            wait_us(2200);
          }
          else if (i >= 399 && i < 532)
          {
            stepPinC = 1;
            wait_us(2800);
            stepPinC = 0;
            wait_us(2800);
          }
          else if (i >= 532 && i < 665)
          {
            stepPinC = 1;
            wait_us(3400);
            stepPinC = 0;
            wait_us(3400);
          }
          else if (i >= 665 && i < 800)
          {
            stepPinC = 1;
            wait_us(4000);
            stepPinC = 0;
            wait_us(4000);
          }
        }
        dirPinC = 0;
        for (int i = 0; i < 750; i++)
        {
          if (i >= 0 && i < 133)
          {
            stepPinC = 1;
            wait_us(4000);
            stepPinC = 0;
            wait_us(4000);
          }
          else if (i >= 133 && i < 266)
          {
            stepPinC = 1;
            wait_us(3400);
            stepPinC = 0;
            wait_us(3400);
          }
          else if (i >= 266 && i < 399)
          {
            stepPinC = 1;
            wait_us(2800);
            stepPinC = 0;
            wait_us(2800);
          }
          else if (i >= 399 && i < 532)
          {
            stepPinC = 1;
            wait_us(2200);
            stepPinC = 0;
            wait_us(2200);
          }
          else if (i >= 532 && i < 665)
          {
            stepPinC = 1;
            wait_us(1600);
            stepPinC = 0;
            wait_us(1600);
          }
          else if (i >= 665 && i < 800)
          {
            stepPinC = 1;
            wait_us(1200);
            stepPinC = 0;
            wait_us(1200);
          }
        }
        ServoCoude.write(0.03);
        thread_sleep_for(500);
      }
      else if (data[3] == 2)
      {
        data[3] = 0;
        while (dutyCyclePoignet > 0.08)
        {
          wait_us(250);
          dutyCyclePoignet -= 0.00001;
          ServoPoignet.write(dutyCyclePoignet);
        }
        thread_sleep_for(500);
        dirPinC = 1;
        for (int i = 0; i < 200; i++)
        {
          stepPinC = 1;
          wait_us(1250);
          stepPinC = 0;
          wait_us(1250);
        }
        thread_sleep_for(500);
        while (dutyCycleCoude < 0.077)
        {
          wait_us(250);
          dutyCycleCoude += 0.00001;
          ServoCoude.write(dutyCycleCoude);
        }
        thread_sleep_for(500);
        while (dutyCycleCoude > 0.03)
        {
          wait_us(250);
          dutyCycleCoude -= 0.00001;
          ServoCoude.write(dutyCycleCoude);
        }
        thread_sleep_for(500);
        dirPinC = 0;
        for (int i = 0; i < 200; i++)
        {
          stepPinC = 1;
          wait_us(1250);
          stepPinC = 0;
          wait_us(1250);
        }
        thread_sleep_for(500);
        while (dutyCyclePoignet < 0.09)
        {
          wait_us(250);
          dutyCyclePoignet += 0.00001;
          ServoPoignet.write(dutyCyclePoignet);
        }
      }
      else if (data[3] == 3)
      {
        data[3] = 0;
        thread_sleep_for(1000);
        while (dutyCyclePoignet < 0.115)
        {
          wait_us(250);
          dutyCyclePoignet += 0.00001;
          ServoPoignet.write(dutyCyclePoignet);
        }
        thread_sleep_for(500);
        while (dutyCycleCoude < 0.05)
        {
          wait_us(250);
          dutyCycleCoude += 0.00001;
          ServoCoude.write(dutyCycleCoude);
        }
        thread_sleep_for(500);
        while (dutyCyclePoignet > 0.03)
        {
          wait_us(250);
          dutyCyclePoignet -= 0.00001;
          ServoPoignet.write(dutyCyclePoignet);
        }
        thread_sleep_for(500);
        while (dutyCyclePoignet < 0.09)
        {
          wait_us(250);
          dutyCyclePoignet += 0.00001;
          ServoPoignet.write(dutyCyclePoignet);
        }
        thread_sleep_for(500);
        while (dutyCycleCoude > 0.03)
        {
          wait_us(250);
          dutyCycleCoude -= 0.00001;
          ServoCoude.write(dutyCycleCoude);
        }
        thread_sleep_for(500);
      }
      else if (data[3] == 4)
      {
        data[3] = 0;
        thread_sleep_for(500);
        ServoPince.write(0.12);
        thread_sleep_for(500);
        ServoPince.write(0.08);
        thread_sleep_for(1500);
      }
      etat_actuel = lecture_trame;
      break;
    case rejouer_sequence:
      LED = !LED;
      Rejouer(data[1]);
      etat_actuel = lecture_trame;
      break;
    case retour_maison:
      // LED = 1;
      if (valeur_encodeur > 0)
      {
        dirPinC = 1;
      }
      else if (valeur_encodeur < 0)
      {
        dirPinC = 0;
      }
      resultat_encodeur = (abs(valeur_encodeur)) / 2;
      valeur_encodeur = 0;

      for (int i = 0; i < resultat_encodeur; i++)
      {
        stepPinC = 1;
        wait_us(2000);
        stepPinC = 0;
        wait_us(2000);
      }
      thread_sleep_for(750);
      ServoCoude.write(0.03);
      dutyCycleCoude = 0.03;
      thread_sleep_for(500);
      ServoPoignet.write(0.09);
      dutyCyclePoignet = 0.09;
      thread_sleep_for(500);
      ServoPince.write(0.12);
      thread_sleep_for(500);
      ServoPince.write(0.08);
      dutyCyclePince = 0.08;
      thread_sleep_for(500);
      if (data[2] == 2)
      {
        data[2] = 0;
        etat_actuel = rejouer_sequence;
      }
      else
      {
        etat_actuel = detection_mode;
      }
      if (dataDemo[4] == 2)
      {
        dataDemo[4] = 0;
        data[4] = 0;
        etat_actuel = lecture_trame;
      }
      if (data[0] == 0)
      {
        etat_actuel = lecture_trame;
        data[0] = 5;
      }
      // if (nouvelEnregistrement == 1)

      break;
    }
  }
}