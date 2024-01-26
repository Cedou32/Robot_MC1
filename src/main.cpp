#include "mbed.h"

//          LISTE DE COMMANDE FOR AT25M01           //
/*
    Write Enable            =   0x06    
    Write Disable           =   0x04    **Default at power up 
    Read Status Register    =   0x05    
    Write Status Register   =   0x01    **Suivi des 8 bits du registre
    Read Sequence           =   0x03    **Suivi de l'adresse de 24 bits 
    Write sequence          =   0x02    **Suivi de l'adresse de 24 bits


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

        cs = 0;
        spi.write(0x05);            
        int x = spi.write(0x00);    
        cs = 1;

        /*cs = 0;
        spi.write(0x02);
        spi.write(0x00);
        spi.write(0x0A);
        spi.write(0xFF);
        spi.write(0x10);
        cs = 1;*/

        cs = 0;
        spi.write(0x03);
        spi.write(0x00);
        spi.write(0x0A);
        spi.write(0xFF);
        int y = spi.write(0x00);
        cs = 1;

        thread_sleep_for(1000);
    }
}