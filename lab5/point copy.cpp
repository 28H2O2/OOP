#include <iostream>
#include <cmath>
#include <cstring>
#include "point.hpp"
using namespace std;

int point::setcolor_grey(int grey)
{
    int num = (int) (grey/25.6);
    return num;
}

int point::setcolor_mono(int mono)
{
    if(mono > 0)
        return 1;
    else
        return 0;
}