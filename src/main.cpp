#include "mbed.h"
#include "ADXL345.h"
//          LISTE DE REGISTRE POUR ADXL312         //
/*

*/
SPI spi(D11, D12, D13); // mosi, miso, sck
DigitalOut cs(D10);

int8_t x0, x1, w0, w1, z0, z1;
int16_t X, Y, Z;
int16_t memX, memY, memZ;

DigitalOut led(D9);

int main()
{
    spi.format(8, 3);
    spi.frequency(5000000);

    cs = 0;
    spi.write(0x2D);
    spi.write(0x00);
    cs = 1;

    cs = 0;
    spi.write(0x31);
    spi.write(0x0B);
    cs = 1;

    cs = 0;
    spi.write(0x2C);
    spi.write(0x0F);
    cs = 1;    

    cs = 0;
    spi.write(0x2D);
    spi.write(0x08);
    cs = 1;    
    while (1)
    {
      //ID = adxl.getDevId();
      //printf("ID: %x\r\n",ID);  
      /*adxl.getOutput(value);
      printf("X=%x\r\n",value[0]);
      printf("Y=%x\r\n",value[1]);
      printf("Z=%x\r\n",value[2]);*/

        
        cs= 0;
        spi.write(0xF2);
        x0 = spi.write(0x00);
        x1 = spi.write(0x00);
        w0 = spi.write(0x00);
        w1 = spi.write(0x00);
        z0 = spi.write(0x00);
        z1 = spi.write(0x00);
        cs = 1;

        X = x1 <<8 | x0;
        Y = w1 <<8 | w0;
        Z = z1 <<8 | z0;

        if((X - memX >= 50)  | (Y - memY >= 50) | (Z - memZ >= 50) ){
          led = !led;
          thread_sleep_for(1000);
        }
        memX = X;
        memY = Y;
        memZ = Z;
        
        printf("X= %d, Y= %d, Z= %d\r\n",X, Y, Z);



        //thread_sleep_for(100);
    }
}