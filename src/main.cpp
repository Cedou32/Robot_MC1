#include "stdio.h"
#include "mbed.h"
#include "SPI_TFT_ILI9341.h"
#include "string"
#include "TextDisplay.h"
#include "Arial12x12.h"
#include "Arial24x23.h"
#include "touch_tft.h"
#include "SPI_TFT.h"

// the TFT is connected to SPI pin 5-7 and IO's 8-10
 SPI_TFT_ILI9341 TFT(D11, D12, D13, D10, D8, D9, "TFT"); // mosi, miso, sclk, cs, reset, dc
// If your display need a signal for switch the backlight use a aditional IO pin in your program

//touch_tft tt(A2, A4, A1, A3, D11, D12, D13, D10, D8, "TFT"); // x+,x-,y+,y-,mosi, miso, sclk, cs, reset

int main()
{

    /*point p;

    tt.claim(stdout);                         // send stdout to the TFT display
    tt.background(Black);                     // set background to black
    tt.foreground(White);                     // set chars to white
    tt.cls();                                 // clear the screen
    tt.set_font((unsigned char *)Arial12x12); // select the font
    tt.set_orientation(3 );

    tt.calibrate(); // calibrate the touch
    while (1)
    {
        p = tt.get_touch(); // read analog pos.
        if (tt.is_touched(p))
        {                                     // test if touched
            p = tt.to_pixel(p);               // convert to pixel pos
            tt.fillcircle(p.x, p.y, 3, Blue); // print a blue dot on the screen
        }
    }*/

    TFT.claim(stdout); // send stderr to the TFT display
    TFT.background(Black); // set background to black
    TFT.cls();             // clear the screen
    TFT.set_orientation(3);

    TFT.rect(0, 0, 320, 240, Blue);

    TFT.rect(10, 10, 110, 40, White);       //Menu
    TFT.set_font((unsigned char *)Arial24x23); // select the font
    TFT.foreground(Blue);  // set chars to white
    TFT.locate(20, 15);
    TFT.printf("Menu");

    TFT.rect(10, 50, 90, 70, White);       //Vitesse
    TFT.set_font((unsigned char *)Arial12x12); // select the font
    TFT.foreground(Green);  // set chars to white
    TFT.locate(25, 55);
    TFT.printf("Vitesse");

    TFT.rect(120, 50, 140, 70, White);       //V1
    TFT.set_font((unsigned char *)Arial12x12); // select the font
    TFT.foreground(Red);  // set chars to white
    TFT.locate(127, 57);
    TFT.printf("1");

    TFT.rect(150, 50, 170, 70, White);       //V2
    TFT.set_font((unsigned char *)Arial12x12); // select the font
    TFT.foreground(Red);  // set chars to white
    TFT.locate(157, 57);
    TFT.printf("2");

    TFT.rect(180, 50, 200, 70, White);       //V3
    TFT.set_font((unsigned char *)Arial12x12); // select the font
    TFT.foreground(Red);  // set chars to white
    TFT.locate(187, 57);
    TFT.printf("3");

    TFT.rect(240, 210, 310, 230, White);       //Close
    TFT.set_font((unsigned char *)Arial12x12); // select the font
    TFT.foreground(White);  // set chars to white
    TFT.locate(255, 215);
    TFT.printf("Close");
}