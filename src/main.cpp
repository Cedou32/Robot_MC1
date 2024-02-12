#include "mbed.h"

BufferedSerial pc(PB_6, PA_10);
uint8_t buff[10];
uint8_t buff1[] = "AB";

AnalogIn joystickY(PA_0);
AnalogIn joystickX(PA_1);

uint8_t valueX, saveX;
uint8_t valueY, saveY;

uint8_t map(uint16_t raw_value)
{
  uint8_t value_8bit = uint8_t(raw_value * 0.00389105);
  return value_8bit;
}

int main()
{
  buff[0] = '#';
  buff[1] = '@';
  buff[2] = '+';
  buff[8] = '?';
  buff[9] = '%';

  pc.set_baud(115200);

  while (1)
  {

    valueX = map(joystickX.read_u16());
    valueY = map(joystickY.read_u16());

    buff[3] = valueX;
    buff[4] = valueY;

    if ((valueX - saveX) > 5 || (saveX - valueX) > 5 || (valueY - saveY) > 5 || (saveY - valueY) > 5)
    {
      pc.write(buff, sizeof(buff));
      saveX = valueX;
      saveY = valueY;
    }

    // thread_sleep_for(500);
  }
}