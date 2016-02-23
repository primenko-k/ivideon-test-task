#ifndef PARAM_H
#define PARAM_H

template <typename T> class Param
{
public:
    Param();
    Param(T defVal);
    Param(T defVal, T minVal, T maxVal);

    T get() const { return val; }
    bool set(T val);
    void setValidRange(T minVal, T maxVal);

private:
    bool isValid(T val) const { return (val < min) || (val > max) ? false : true; }

private:
    T val;
    T min, max;
};

#include "param_impl.h"

#endif // PARAM_H
