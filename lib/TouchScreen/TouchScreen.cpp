/*      Fichier .cpp de la librairie TouchScreen        */
/*Cette librarie controle le module tactile d'un        */
/*écran tactile                                         */
/*Créée par Mihai Stinga                                 */

#include "TouchScreen.h"
#include "mbed.h"

TouchScreen::TouchScreen(PinName Xp, PinName Xn, PinName Yp, PinName Yn) : _Xp(Xp), _Xn(Xn), _Yp(Yp), _Yn(Yn), _Ax(Xn), _Ay(Yp)
{
    xna = Xn;
    ypa = Yp;
}

bool TouchScreen::Touch_detect(void)
{
    _Xp.output();
    _Yn.output();

    _Xp = 0;
    _Yn = 1;

    _Xn.input();
    AnalogIn XNA(xna);
    wait_us(20);

    _Yp.input();
    AnalogIn YPA(ypa);
    wait_us(20);

    int adcz1 = XNA.read_u16();
    int adcz2 = YPA.read_u16();

    int touch = adcz2 - adcz1;

    if (touch < 55000)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int TouchScreen::getX(void)
{
    _Yp.output();
    _Yn.output();

    _Yp = 0;
    _Yn = 1;

    _Xp.input();
    _Xn.input();
    AnalogIn XNA(xna);

    wait_us(20);

    int Xraw = XNA.read_u16();
    //int Xvalue = Xraw * -0.006213592 + 357.2815534;
    int Xvalue = Xraw * -0.006349206 + 356.1904762;

    if (Xvalue < 0)
    {
        Xvalue = 0;
    }
    else if (Xvalue > 320)
    {
        Xvalue = 320;
    }

    return Xvalue ;
}

int TouchScreen::getY()
{
    _Xp.output();
    _Xn.output();

    _Xp = 1;
    _Xn = 0;

    _Yp.input();
    _Yn.input();
    AnalogIn YPA(ypa);

    wait_us(20);

    int Yraw = YPA.read_u16();
    //int Yvalue = Yraw * -0.004918033 + 282.7868852;
    int Yvalue = Yraw * -0.004968944 + 283.2298137;

    if (Yvalue < 0)
    {
        Yvalue = 0;
    }
    else if (Yvalue > 240)
    {
        Yvalue = 240;
    }
    return Yvalue;
}


