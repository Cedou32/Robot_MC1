#include "mbed.h"

//          LISTE DE REGISTRE POUR ADXL312         //
/*

*/
SPI spi(D11, D12, D13); // mosi, miso, sck
DigitalOut cs(D10);

int main()
{

    while (1)
    {

        spi.format(8, 3);
        spi.frequency(5000000);

        cs = 0;
        spi.write(0x00);
        int x = spi.write(0x00);
        cs = 1;
        printf("ID: %X\r\n",x);

        /*cs = 0;
        spi.write(0x00);
        int x = spi.write(0x00);
        cs = 1;*/

        thread_sleep_for(1000);
    }
}