#include <limits>

template<typename T>
Param<T>::Param() : val()
{
    min = std::numeric_limits<T>::min();
    max = std::numeric_limits<T>::max();
}

template<typename T>
Param<T>::Param(T defVal) : val(defVal)
{
    min = std::numeric_limits<T>::min();
    max = std::numeric_limits<T>::max();
}

template<typename T>
Param<T>::Param(T defVal, T minVal, T maxVal) : min(minVal), max(maxVal)
{
    if (max < min)
        max = min;

    if (isValid(defVal))
        val = defVal;
    else
        val = min;
}

template<typename T>
bool Param<T>::set(T val)
{
    if (isValid(val))
    {
        this->val = val;
        return true;
    }
    else
    {
        return false;
    }
}
