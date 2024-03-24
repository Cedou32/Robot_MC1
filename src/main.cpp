#include "mbed.h"

BufferedSerial pc(PB_6, PB_7); // USBTX et USBRX sont les broches de communication série sur la carte Nucleo STM32F072RB
uint8_t buffer[10];

DigitalOut LED(PC_13);

DigitalOut dirPinB(PC_0);
DigitalOut stepPinB(PC_1);

DigitalOut dirPinC(PB_9);
DigitalOut stepPinC(PB_8);

PwmOut ServoCoude(PC_8);
PwmOut ServoPoignet(PC_9);

Ticker InterruptionBT1;
Ticker InterruptionBT2;
Ticker InterruptionBT3;

char startMarker[] = "#@+";
char endMarker[] = "?%";
char currentChar;

uint8_t flagBT = 0;
int flag_protection = 0;
int flagStepper = 0;
int flagServo = 0;

float dutyCycleCoude = 0.125;
float dutyCyclePoignet = 0.125;

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
  InterruptionBT1.attach(&VerifServo, 0.002);
  InterruptionBT2.attach(&VerifStepper, 0.002);

  // ServoCoude.period_ms(1);
  buffer[3] = 100;
  buffer[4] = 100;
  buffer[5] = 100;
  buffer[6] = 100;
  pc.set_baud(115200);
  while (1)
  {

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
      LED = int(buffer[7]);
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
      if (buffer[5] >= 85 && buffer[5] <= 170)
      {
      }
      else if (buffer[5] >= 0 && buffer[5] < 85)
      {
        dutyCycleCoude -= 0.0001;
      }
      else if (buffer[5] >= 170 && buffer[5] <= 255)
      {
        dutyCycleCoude += 0.0001;
      }
      if (dutyCycleCoude < 0.05)
      {
        dutyCycleCoude = 0.05;
      }
      else if (dutyCycleCoude > 0.125)
      {
        dutyCycleCoude = 0.125;
      }
      ServoCoude.write(dutyCycleCoude);

      if (buffer[4] >= 85 && buffer[4] <= 170)
      {
      }
      else if (buffer[4] >= 0 && buffer[4] < 85)
      {
        dutyCyclePoignet -= 0.0001;
      }
      else if (buffer[4] >= 170 && buffer[4] <= 255)
      {
        dutyCyclePoignet += 0.0001;
      }
      if (dutyCyclePoignet < 0.05)
      {
        dutyCyclePoignet = 0.05;
      }
      else if (dutyCyclePoignet > 0.125)
      {
        dutyCyclePoignet = 0.125;
      }
      ServoPoignet.write(dutyCyclePoignet);
    }
  }
}