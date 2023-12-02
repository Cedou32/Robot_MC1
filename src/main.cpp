#include "stdio.h"
#include "mbed.h"
#include "SPI_TFT_ILI9341.h"
#include "string"
#include "TextDisplay.h"
#include "Arial12x12.h"
#include "Arial24x23.h"

// the TFT is connected to SPI pin 5-7 and IO's 8-10
SPI_TFT_ILI9341 TFT(D11, D12, D13, D10, D8, D9, "TFT"); // mosi, miso, sclk, cs, reset, dc
// If your display need a signal for switch the backlight use a aditional IO pin in your program

int main()
{
    TFT.claim(stdout); // send stderr to the TFT display
    TFT.background(Black); // set background to black
    TFT.cls();             // clear the screen
    TFT.set_orientation(3);

    TFT.rect(10, 10, 100, 50, Green);
    TFT.set_font((unsigned char *)Arial12x12); // select the font
    TFT.foreground(Blue);  // set chars to white
    TFT.locate(20, 15);
    TFT.printf("Salut");

    TFT.foreground(Red);  // set chars to white
    TFT.locate(40, 30);
    TFT.printf("Salut");


}