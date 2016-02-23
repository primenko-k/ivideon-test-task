#ifndef LED_H
#define LED_H

#include "param.h"

class Led
{
public:
    enum STATE { STATE_OFF = 0, STATE_ON, STATES_COUNT };
    enum COLOR { COLOR_RED = 0, COLOR_GREEN, COLOR_BLUE, COLORS_COUNT };
    static const double LED_RATE_MIN = 0.0, LED_RATE_MAX = 5.0;

    Led(STATE state = STATE_OFF, COLOR color = COLOR_GREEN, double rate_hz = 1.0);

public:
    Param<int> state;
    Param<int> color;
    Param<double> rate_hz;
};
#endif // LED_H
