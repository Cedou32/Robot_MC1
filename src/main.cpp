#include "mbed.h"

BufferedSerial pc(PB_6, PA_10);
uint8_t buff[10];
uint8_t buff1[] = "AB";

AnalogIn joystickY(PA_0);
AnalogIn joystickX(PA_1);

uint8_t valueX;
uint8_t valueY;

uint8_t map(uint16_t raw_value){
    uint8_t value_8bit = uint8_t (raw_value * 0.00389105);
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

    while (1){

        buff[3] = map(joystickX.read_u16());
        buff[4] = map(joystickY.read_u16());

        
        //buff1[0] = valueX;
        //buff1[1] = valueY;

        //printf("X = %u\r\n", buff[3]);
        //printf("Y = %u\r\n", buff[4]);

        pc.write(buff, sizeof(buff));
        //pc.write(buff1, sizeof(buff1));

        //thread_sleep_for(500);
    }
}