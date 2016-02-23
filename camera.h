#ifndef CAMERA_H
#define CAMERA_H

#include "led.h"
#include <boost/thread/mutex.hpp>   // needs to add -lboost_system to compiler options

class Camera
{
public:
    Camera();

public:
    Led main_led;
    boost::mutex cam_mutex; // externally controlled mutex
};

#endif // CAMERA_H
