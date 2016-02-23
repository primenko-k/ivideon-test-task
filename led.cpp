#include "led.h"

Led::Led(STATE state, COLOR color, double rate_hz) :
    state(state, 0, STATES_COUNT-1),
    color(color, 0, COLORS_COUNT-1),
    rate_hz(rate_hz, LED_RATE_MIN, LED_RATE_MAX)
{
}
