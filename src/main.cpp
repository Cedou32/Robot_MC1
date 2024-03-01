#include "mbed.h"
#include "stdio.h"

AnalogIn Y1(PC_5);
AnalogIn Y2(PA_1);
AnalogIn X1(PB_1);
AnalogIn X2(PA_0);

DigitalIn CTRL(PB_15);
DigitalIn Pince(PA_3);

DigitalOut led(PC_13);

BufferedSerial pc(PB_6, PB_7);

uint8_t buff[10];
uint8_t value;

uint8_t map(uint16_t raw_value)
{
  uint8_t value_8bit = uint8_t(raw_value * 0.00389105);
  return value_8bit;
}

int main()
{
  pc.set_baud(9600);

  while (1)
  {
    if (CTRL == 1)
    {
      led = 1;
    }
    else
    {
      led = 0;
    }
    /*value = map(X2.read_u16());
    buff[0] = value;
    pc.write(buff, 1);*/
  }
}