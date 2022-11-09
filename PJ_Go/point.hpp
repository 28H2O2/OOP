
#ifndef _POINT_H_
#define _POINT_H_
#include <vector>
#include <cstring>
using namespace std;

class point
{
private:
    int x;
    int y;

public:
    // point();
    // point(const int, const int){}
    void getpoint();
    void setpoint();
    int setcolor_gray(int);// 变换为0~9之间的数值
    int setcolor_mono(int);// 0 or 1
};
int point::setcolor_gray(int gray)
{
    int num = (int)(gray / 25.6);
    return num;
}

int point::setcolor_mono(int mono)
{
    if (mono > 0)
        return 1;
    else
        return 0;
}

#endif
