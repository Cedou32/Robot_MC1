#include "mbed.h"

//          LISTE DE COMMANDE FOR ADXL312         //
/*

*/
SPI spi(D11, D12, D13); // mosi, miso, sck
DigitalOut cs(D10);

int main()
{
    spi.format(8, 0);
    spi.frequency(5000000);

    while (1)
    {

        cs = 0;
        spi.write(0x06);    
        cs = 1;

        thread_sleep_for(1000);
    }
}