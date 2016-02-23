#ifndef PARAM_H
#define PARAM_H

template <typename T> class Param
{
public:
    Param();
    Param(T defVal);

    T get() const { return val; }
    bool set(T val);

private:

private:
    T val;
};

#include "param_impl.h"

#endif // PARAM_H
