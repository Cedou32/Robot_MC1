#ifndef TOUCHSCREEN_H
#define TOUCHSCREEN_H

#include <mbed.h>

class TouchScreen {
public:
    TouchScreen(PinName Xp, PinName Xn, PinName Yp, PinName Yn);
    int getX();
    int getY();
    bool Touch_detect();

private:
    DigitalInOut _Xp;
    DigitalInOut _Xn;
    DigitalInOut _Yp;
    DigitalInOut _Yn;
    AnalogIn     _Ax;
    AnalogIn     _Ay;
    PinName xna;
    PinName ypa;
};

#endif
