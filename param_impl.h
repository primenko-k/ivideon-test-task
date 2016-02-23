
template<typename T>
Param<T>::Param() : val()
{
}

template<typename T>
Param<T>::Param(T defVal) : val(defVal)
{
}

template<typename T>
bool Param<T>::set(T val)
{
    this->val = val;
    return true;
}
