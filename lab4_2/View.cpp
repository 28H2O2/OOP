#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>
#define G "grayscale"
#define M "monochrome"
#include "View.hpp"
#include "asciis.h"
#include "inline.hpp"
using namespace std;

View::View(const string option, const int p_width, const int p_height) //构造函数
{
    if (option == G)
    {
        flag_View = 1;
        height = p_height;

        width = p_width;
        create_gray(width, height);
    }
    else
    {
        true_width = p_width;
        flag_View = 0;
        height = p_height;
        width = p_width / 8 + 1;
        create_mono(width, height);
    }
}

void View::create_gray(const int w, const int h)
{
    dot_View.resize(h);
    for (int i = 0; i < h; i++)
    {
        dot_View[i].resize(w);
    }
}

void View::create_mono(const int w, const int h)
{
    dot_View.resize(h);
    for (int i = 0; i < h; i++)
    {
        dot_View[i].resize(w);
    }
}

void View::printstr(const int x, const int y, const string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        if (flag_View == 1)
            printchar_gray(x + 8 * i, y, str[i]);
        else
            printchar_mono(x + 8 * i, y, str[i]);
    }
}

void View::printchar_gray(const int x, const int y, const char c)
{
    // const int int_c = (int)c;
    // const int pos = (int_c * 8) - 256;
    const int pos = position(c);                        // inline 函数
    const unsigned char *const p = nAsciiDot + pos + 8; // 找到在字符表里的位置
    for (int i = 8; i > 0; i--)                         // 对一个char的8个二进制数进行循环              为什么是8?
    {
        const unsigned char *const p_now = p - i;
        for (int j = 0; j < 8; j++) // 对一个二进制数的八位进行循环
        {
            if (x + j - 1 > width || height - y - i + 1 < 0) //如果超出画布范围
                continue;
            dot_View[height - y - i + 1][x + j - 1] = (*p_now & (unsigned char)pow(2, 7 - j));
        }
    }
}

void View::printchar_mono(const int x, const int y, const char c)
{
    // const int int_c = (int)c;
    // const int pos = (int_c * 8) - 256;
    const int pos = position(c);                    // inline 函数
    const unsigned char *const p = nAsciiDot + pos; // 找到在字符表里的位置
    const int x_pos = (x - 1) / 8;                  // canvas中的真实位置
    const int y_pos = height - y;                   // canvas中的真实位置
    const int right = (x - 1) % 8;                  //右移的位数
    const int left = 8 - right;                     // 左移的位数

    for (int i = 7; i >= 0; i--) // 对一个char的8个二进制数进行循环（字符表从上到下）（char从下到上）
    {
        if (y_pos + i - 7 > height - 1 || y_pos + i - 7 < 0) // 判断是否越界
            continue;
        const unsigned char *const p_now = p + i;

        const unsigned char move_right = *(p_now) >> (right);                         // 右移之后
        const unsigned char move_left = *(p_now) << (left);                           //左移之后
        dot_View[y_pos + i - 7][x_pos] = dot_View[y_pos + i - 7][x_pos] | move_right; // 变换前面的部分
        if (x_pos + 1 > width - 1)                                                    // 判断是否越界
            continue;
        dot_View[y_pos + i - 7][x_pos + 1] = dot_View[y_pos + i - 7][x_pos + 1] | move_left; // 变换后面的部分
    }
}

void View::line(const int x0, const int y0, const int x1, const int y1)
{
    if (flag_View == 1)
        line_gray(x0, y0, x1, y1);
    else
        line_mono(x0, y0, x1, y1);
}

void View::line_gray(const int x0, const int y0, const int x1, const int y1) // lab1里的Bresenham画线算法
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
            dot_View[height - 1 - y][x] = 1;
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
            dot_View[height - 1 - y][x] = 1;
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

void View::line_mono(const int x0, const int y0, const int x1, const int y1)
{
    // NOTE 注释以下为直线版
    // int x0 = _x0 + 1;
    // int x1 = _x1 + 1;
    // int y0 = _y0 + 1;
    // int y1 = _y1 + 1;
    // int dx = x1 - x0;         // x偏移量
    // int dy = y1 - y0;         // y偏移量
    // int ux = dx > 0 ? 1 : -1; // x伸展方向
    // int uy = dy > 0 ? 1 : -1; // y伸展方向
    // int x = x0;               //起点x坐标
    // int y = y0;               //起点y坐标
    // if (x0 == x1)
    // {
    //     int x = x0 % 8;
    //     int pos_x = (x0 - 1) / 8;
    //     while (y != y1 + uy)
    //     {
    //         dot_View[height - y][pos_x] = dot_View[height - y][pos_x] | (unsigned char)pow(2, (8 - x) % 8);
    //         y += uy;
    //     }
    // }
    // if (y0 == y1)
    // {
    //     if (x0 > x1) //如果大小相反就互换
    //     {
    //         int temp = x0;
    //         x0 = x1;
    //         x1 = temp;
    //         ux = 1;
    //     }
    //     int pos_x0 = (x0 - 1) / 8;
    //     int pos_x1 = (x1 - 1) / 8;
    //     // int pos_x = pos_x0;
    //     dot_View[height - y][pos_x0] =
    //         dot_View[height - y0][pos_x0] | (unsigned char)(pow(2, (8 - x0) % 8) - 1);
    //     for (int i = 1; i < (pos_x1 - pos_x0); i++)
    //     {
    //         dot_View[height - y0][i + pos_x0] = (unsigned char)255;
    //     }
    //     dot_View[height - y0][pos_x1] =
    //         dot_View[height - y0][pos_x1] | (unsigned char)(255 << (8 - (x1-1) % 8));
    // }

    // NOTE 以下为完整版
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

void View::bit_change(const int x, const int y) //两种存储方式的转化
{
    const int x_pos = (x - 1) / 8;    // canvas中的真实位置
    const int y_pos = height - 1 - y; // canvas中的真实位置
    const int right = (x - 1) % 8;    // 右移的位数
    const int left = 8 - right;       // 左移的位数
    dot_View[y_pos][x_pos] =
        dot_View[y_pos][x_pos] | (unsigned char)pow(2, left - 1); //用位运算直接转化
}
