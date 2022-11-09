
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


#endif
