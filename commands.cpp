#include "commands.h"
#include "camera.h"
#include <sstream>
#include <cstdlib>
#include <cmath>

std::string set_led_state(std::string &state, Camera *cam);
std::string get_led_state(std::string &unused, Camera *cam);
std::string set_led_color(std::string &color, Camera *cam);
std::string get_led_color(std::string &unused, Camera *cam);
std::string set_led_rate(std::string &rate_hz, Camera *cam);
std::string get_led_rate(std::string &unused, Camera *cam);

const Cmd supported_cmds[] = {

    {
    "set-led-state",
    "on,off",
    "OK,FAILED",
    "включить/выключить LED",
    &set_led_state
    },

    {
    "get-led-state",
    "",
    "OK on|off,FAILED",
    "запросить состояние LED",
    &get_led_state
    },

    {
    "set-led-color",
    "red,green,blue",
    "OK,FAILED",
    "изменить цвет LED",
    &set_led_color
    },

    {
    "get-led-color",
    "",
    "OK red|green|blue,FAILED",
    "запросить цвет LED",
    &get_led_color
    },

    {
    "set-led-rate",
    "0..5",
    "OK,FAILED",
    "изменить частоту мерцания LED (Гц)",
    &set_led_rate
    },

    {
    "get-led-rate",
    "",
    "OK 0..5,FAILED",
    "запросить частоту мерцания LED (Гц)",
    &get_led_rate
    },
};

const int supported_cmds_num = sizeof(supported_cmds)/sizeof(supported_cmds[0]);

std::string cmd_inval_func(std::string &, Camera *)
{
    return "FAILED";
}

int state_to_int(const std::string &state);
std::string state_from_int(int state_code);

std::string set_led_state(std::string &state, Camera *cam)
{

    if (cam->main_led.state.set(state_to_int(state)))
        return "OK";
    else
        return "FAILED";
}

std::string get_led_state(std::string &, Camera *cam)
{
    std::string cur_state = state_from_int(cam->main_led.state.get());
    if (!cur_state.empty())
        return "OK " +cur_state;
    else
        return "FAILED";
}

int state_to_int(const std::string &state)
{
    if (state.compare("on") == 0)
        return Led::STATE_ON;
    if (state.compare("off") == 0)
        return Led::STATE_OFF;

    return -1;
}

std::string state_from_int(int state_code)
{
    if (state_code == Led::STATE_ON)
        return "on";
    if (state_code == Led::STATE_OFF)
        return "off";

    return "";
}

int color_to_int(const std::string &color);
std::string color_from_int(int color_code);

std::string set_led_color(std::string &color, Camera *cam)
{

    if (cam->main_led.color.set(color_to_int(color)))
        return "OK";
    else
        return "FAILED";
}

std::string get_led_color(std::string &, Camera *cam)
{
    std::string cur_color = color_from_int(cam->main_led.color.get());
    if (!cur_color.empty())
        return "OK " +cur_color;
    else
        return "FAILED";
}

int color_to_int(const std::string &color)
{
    if (color.compare("red") == 0)
        return Led::COLOR_RED;
    if (color.compare("green") == 0)
        return Led::COLOR_GREEN;
    if (color.compare("blue") == 0)
        return Led::COLOR_BLUE;

    return -1;
}

std::string color_from_int(int color_code)
{
    if (color_code == Led::COLOR_RED)
        return "red";
    if (color_code == Led::COLOR_GREEN)
        return "green";
    if (color_code == Led::COLOR_BLUE)
        return "blue";

    return "";
}

double rate_to_double(const std::string &rate_hz);
std::string rate_from_double(double rate_hz);

std::string set_led_rate(std::string &rate_hz, Camera *cam)
{

    if (cam->main_led.rate_hz.set(rate_to_double(rate_hz)))
        return "OK";
    else
        return "FAILED";
}

std::string get_led_rate(std::string &, Camera *cam)
{
    std::string cur_rate_hz = rate_from_double(cam->main_led.rate_hz.get());
    if (!cur_rate_hz.empty())
        return "OK " + cur_rate_hz;
    else
        return "FAILED";
}

double rate_to_double(const std::string &rate_hz)
{
    char *end;
    double t = strtod(rate_hz.c_str(), &end);
    if (rate_hz.empty() || *end != '\0')
        return HUGE_VAL;
    else
        return t;
}

std::string rate_from_double(double rate_hz)
{
    std::ostringstream ss;
    ss << rate_hz;
    return ss.str();
}
