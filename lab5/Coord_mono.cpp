

using namespace std;
#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include "View.hpp"
#include "Coord_mono.hpp"
// #include "point.hpp"
// #include "Canvas5.hpp"
#include "asciis.h"

void Coord_mono::printstr(const int x, const int y, const string &str)
{
    for (int i = 0; i < str.length(); i++)
    {
        printchar(x + 8 * i, y, str[i]);
    }
}

void Coord_mono::printchar(const int x, const int y, const char c)
{

    const int int_c = (int)c;
    const int pos = (int_c * 8) - 256;
    // const int pos = position(c);                    //用内联函数
    const unsigned char *const p = nAsciiDot + pos;                 // 找到在字符表里的位置
    const int x_pos = (x - 1) / 8;                                  // canvas中的真实位置
    const int right = (x - 1) % 8;                                  //右移的位数
    const int left = 8 - right;                                     // 左移的位数
    const int y_pos = (flag_coord == world_coord ? height - y : y); //两种坐标系

    for (int i = 7; i >= 0; i--) // 对一个char的8个二进制数进行循环（字符表从上到下）（char从下到上）
    {
        if (y_pos + i - 7 > height - 1 || y_pos + i - 7 < 0) // 判断是否越界
            continue;
        const unsigned char *const p_now = p + i;

        const unsigned char move_right = *(p_now) >> (right);                             // 右移之后
        const unsigned char move_left = *(p_now) << (left);                               //左移之后
        dot_canvas[y_pos + i - 7][x_pos] = dot_canvas[y_pos + i - 7][x_pos] | move_right; // 变换前面的部分
        if (x_pos + 1 > width - 1)                                                        // 判断是否越界
            continue;
        dot_canvas[y_pos + i - 7][x_pos + 1] = dot_canvas[y_pos + i - 7][x_pos + 1] | move_left; // 变换后面的部分
    }
}

void Coord_mono::color(int c)
{
    color_num = P.setcolor_mono(c);
}

void Coord_mono::printresults() // 两种坐标系不同的输出方法
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < mono_width - 1; j++)
        {
            for (int k = 7; k >= 0; k--)
            {
                char out = ((unsigned char)pow(2, k) & dot_canvas[i][j]) == 0 ? ' ' : '1'; //输出0或1
                cout << out;
                // if (((unsigned char)pow(2, k) & dot_canvas[i][j]) == 0) // 输出
                //     cout << "o";
                // else
                //     cout << ".";
            }
        }
        // NOTE 注意mono_width or width
        for (int k = 7; k >= mono_width * 8 - width; k--)
        {
            char out = ((unsigned char)pow(2, k) & dot_canvas[i][mono_width - 1]) == 0 ? ' ' : '1';
            cout << out; //输出0或1
            // if (((unsigned char)pow(2, k) & dot_canvas[i][mono_width - 1]) == 0) // 输出
            //     cout << "o";
            // else
            //     cout << ".";
        }
        cout << endl;
    }
}

void Coord_mono::line(const int x0, const int y0, const int x1, const int y1)
{
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

            bit_change(x + 1, y);
            // FIXME    // dot_canvas[height+1-y][x] = 1;
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
            // FIXME    // dot_canvas[height+1-y][x] = 1;
            bit_change(x + 1, y);
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

void Coord_mono::bit_change(const int x, const int y) //两种存储方式的转化
{
    const int x_pos = (x - 1) / 8; // canvas中的真实位置
    // const int y_pos = height - 1 - y; // canvas中的真实位置
    const int y_pos = (flag_coord == world_coord ? height - y : y);                        //两种坐标系
    const int right = (x - 1) % 8;                                                         // 右移的位数
    const int left = 8 - right;                                                            // 左移的位数
    dot_canvas[y_pos][x_pos] = dot_canvas[y_pos][x_pos] | (unsigned char)pow(2, left - 1); //用位运算直接转化
}