#include "mbed.h"

SPI spi(D11, D12, D13);
DigitalOut cs(D10);

//uint8_t X0, X1, Y0, Y1, Z0, Z1;
//uint16_t X, Y, Z;

int main()
{
  spi.format(8, 0);
    spi.frequency(500000);
  while (1)
  {
    

    cs = 0;
    int device_ID = spi.write(0x00);

    //printf("Device ID: 0x%X\r\n", device_ID);

    cs = 1;

    thread_sleep_for(500);

    cs = 0;
    spi.write(0x31);
    spi.write(0x0D);
    cs = 1;
      thread_sleep_for(500);
  }

  /*while (1)
  {
    cs = 0;
    X0 = spi.write(0x32);
    X1 = spi.write(0x33);
    Y0 = spi.write(0x34);
    Y1 = spi.write(0x35);
    Z0 = spi.write(0x36);
    Z1 = spi.write(0x37);
    cs = 1;

    X = (X0 << 8) | X1;
    Y = (Y0 << 8) | Y1;
    Z = (Z0 << 8) | Z1;

    printf("X = 0X%X\r\n",X0);
    printf("Y = 0X%X\r\n",Y);
    printf("Z = 0X%X\r\n",Z);
    printf("\r\n");

    thread_sleep_for(250);
  }*/
}