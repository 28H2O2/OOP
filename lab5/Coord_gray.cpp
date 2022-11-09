
using namespace std;
#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include "View.hpp"
#include "Coord_gray.hpp"
// #include "Canvas5.hpp"
#include "asciis.h"

void Coord_gray::printstr(const int x, const int y, const string &str)
{
    for (int i = 0; i < str.length(); i++)
    {
        printchar(x + 8 * i, y, str[i]);
    }
}

void Coord_gray::printchar(const int x, const int y, const char c)
{
    const int int_c = (int)c;
    const int pos = (int_c * 8) - 256;

    // const int pos = position(c);                        // inline 函数替换
    // cout << "flag_coord=" << flag_coord << endl; // BUG 正确
    const int y_pos = (flag_coord == world_coord ? height - y : y); //两种坐标系

    const unsigned char *const p = nAsciiDot + pos + 8; // 找到在字符表里的位置
    for (int i = 8; i > 0; i--)                         // 对一个char的8个二进制数进行循环       为什么是8?
    {
        const unsigned char *const p_now = p - i; //指针当前位置
        for (int j = 0; j < 8; j++)               // 对一个二进制数的八位进行循环
        {
            if (x + j > width || y_pos - i + 1 < 0) //如果超出画布范围
                continue;
            unsigned char flag = *p_now & (unsigned char)pow(2, 7 - j); //判断这一位是否为0
            unsigned char boolean_canvas = (flag == 0 ? 0 : 1);
            // dot_canvas[height - y - i + 1][x + j] = color_num * (*p_now & (unsigned char)pow(2, 7 - j));
            dot_canvas[y_pos - i + 1][x + j] = color_num * boolean_canvas;
        }
    }
}

void Coord_gray::color(int c)
{
    color_num = P.setcolor_gray(c);
}

void Coord_gray::printresults()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // if (dot_canvas[i][j] == 0)
            //     cout << "o";
            // else
            //     cout << ".";
            dot_canvas[i][j] == 0 ? cout << ' ' : cout << (int)dot_canvas[i][j]; //输出为空或者一个数字
            // if (dot_canvas[i][j] == 0)
            //     cout<<' ';

            // cout<<(int)dot_canvas[i][j];
        }
        cout << endl;
    }
}

void Coord_gray::line(const int x0, const int y0, const int x1, const int y1)
{
    // cout << "yes" << endl;
    const int dx = x1 - x0;         // x偏移量
    const int dy = y1 - y0;         // y偏移量
    const int ux = dx > 0 ? 1 : -1; // x伸展方向
    const int uy = dy > 0 ? 1 : -1; // y伸展方向
    const int dx2 = abs(dx * 2);    // x偏移量乘2  （目的是出现整数）
    const int dy2 = abs(dy * 2);    // y偏移量乘2
    if (abs(dx) > abs(dy))          //以x为增量方向计算
    {
        int e = -dx;         // e = -0.5 * 2 * dx,定义初始值 （原来的e是-0.5）
        int x = x0;          //起点x坐标
        int y = y0;          //起点y坐标
        while (x != x1 + ux) //在x到达终点后结束循环
        {
            const int y_pos = (flag_coord == world_coord ? height - y : y); //两种坐标系

            dot_canvas[y_pos - 1][x] = color_num;
            // dot_canvas[height - 1 - y][x] = 1;
            e = e + dy2; //（原来是 e = e + k）
            if (e > 0)   // e大于0时表示要取右上的点（否则是右下的点）
            {
                if (y != y1) //如果未到终点则继续增加
                {
                    y += uy;
                }
                e = e - dx2; // (原来是 e = e -1)
            }
            x += ux; //继续移动
        }
    }
    else
    { //以y为增量方向计算，其余与上面类似
        int e = -dy;
        int x = x0;
        int y = y0;
        while (y != y1 + uy)
        {
            const int y_pos = (flag_coord == world_coord ? height - y : y); //两种坐标系
            dot_canvas[y_pos - 1][x] = color_num;
            // dot_canvas[height - 1 - y][x] = 1;
            e = e + dx2;
            if (e > 0)
            {
                if (x != x1)
                {
                    x += ux;
                }
                e = e - dy2;
            }
            y += uy;
        }
    }
}
