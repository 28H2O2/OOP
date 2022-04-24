using namespace std;
#define G "grayscale"
#define M "monochrome"
#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include "inline.hpp"
#include "View.hpp"
#include "Canvas.hpp"
#include "asciis.h"

Canvas::Canvas(string option, const int p_width, const int p_height)
{
    while (1)
    {
        if (option == G)
        {
            flag_Canvas = 1;
            height = p_height;

            width = p_width;
            create_gray(width, height);
            break;
        }
        if (option == M)
        {
            true_width = p_width;
            flag_Canvas = 0;
            height = p_height;
            width = p_width / 8 + 1;
            create_mono(width, height);
            break;
        }
        else
        {
            cout << "please input the model again!" << endl;
            return;
        }
    }
}

void Canvas::create_gray(int w, int h)
{
    dot_canvas.resize(h); //创建
    for (int i = 0; i < h; i++)
    {
        dot_canvas[i].resize(w);
    }
}

void Canvas::create_mono(int w, int h)
{
    dot_canvas.resize(h);
    for (int i = 0; i < h; i++)
    {
        dot_canvas[i].resize(w);
    }
}

void Canvas::printstr(const int x, const int y, const string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        if (flag_Canvas == 1)
            printchar_gray(x + 8 * i, y, str[i]); //转到真实位置
        else
            printchar_mono(x + 8 * i, y, str[i]);
    }
}

void Canvas::printchar_gray(const int x, const int y, const char c) //在(x,y)处打印字符c
{
    // const int int_c = (int)c;
    // const int pos = (int_c * 8) - 256;
    const int pos = position(c);                        // inline 函数替换
    const unsigned char *const p = nAsciiDot + pos + 8; // 找到在字符表里的位置
    for (int i = 8; i > 0; i--)                         // 对一个char的8个二进制数进行循环       为什么是8?
    {
        const unsigned char *const p_now = p - i; //指针当前位置
        for (int j = 0; j < 8; j++)               // 对一个二进制数的八位进行循环
        {
            if (x + j > width || height - y - i + 1 < 0) //如果超出画布范围
                continue;
            dot_canvas[height - y - i + 1][x + j] = (*p_now & (unsigned char)pow(2, 7 - j));
        }
    }
}

void Canvas::printchar_mono(const int x, const int y, const char c)
{
    // const int int_c = (int)c;
    // const int pos = (int_c * 8) - 256;
    const int pos = position(c);                    //用内联函数
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

        const unsigned char move_right = *(p_now) >> (right);                             // 右移之后
        const unsigned char move_left = *(p_now) << (left);                               //左移之后
        dot_canvas[y_pos + i - 7][x_pos] = dot_canvas[y_pos + i - 7][x_pos] | move_right; // 变换前面的部分
        if (x_pos + 1 > width - 1)                                                        // 判断是否越界
            continue;
        dot_canvas[y_pos + i - 7][x_pos + 1] = dot_canvas[y_pos + i - 7][x_pos + 1] | move_left; // 变换后面的部分
    }
}

void Canvas::printcanvas() const
{
    if (flag_Canvas == 1)
        printcanvas_gray();
    else
        printcanvas_mono();
}

void Canvas::printcanvas_gray() const
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (dot_canvas[i][j] == 0)
                cout << "o";
            else
                cout << ".";
        }
        cout << endl;
    }
}

void Canvas::printcanvas_mono() const
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width - 1; j++)
        {
            for (int k = 7; k >= 0; k--)
            {
                if (((unsigned char)pow(2, k) & dot_canvas[i][j]) == 0) // 输出
                    cout << "o";
                else
                    cout << ".";
            }
        }
        for (int k = 7; k >= width * 8 - true_width; k--)
        {
            if (((unsigned char)pow(2, k) & dot_canvas[i][width - 1]) == 0) // 输出
                cout << "o";
            else
                cout << ".";
        }
        cout << endl;
    }
}

void Canvas::showViewAt(const int x, const int y, View V)
{
    if (flag_Canvas == 1)
        showViewAt_gray(x, y, V);
    else
        showViewAt_mono(x, y, V);
}

void Canvas::showViewAt_gray(const int x, const int y, View V)
{
    for (int i = 0; i < V.height; i++)
    {
        for (int j = 0; j < V.width; j++)
        {
            dot_canvas[height - y - V.height + 1 + i][x - 1 + j] = V.dot_View[i][j];
        }
    }
}

void Canvas::showViewAt_mono(const int x, const int y, View V)
{
    const int x_pos = (x - 1) / 8;     // canvas中的真实位置
    const int y_pos = height - y;      // canvas中的真实位置
    const int right = (x - 1) % 8;     //右移的位数
    const int left = 8 - right;        // 左移的位数
    for (int i = 0; i < V.height; i++) // 对一个char的8个二进制数进行循环（字符表从上到下）（char从下到上）
    {
        if (y_pos - i > height - 1 || y_pos - i < 0)
            continue;

        // unsigned char move_right = *(p_now)>>(right); // 右移之后
        // unsigned char move_left = *(p_now)<<(left); //左移之后
        for (int j = 0; j < V.width; j++)
        {
            if (x_pos + j > width - 1)
                continue;

            dot_canvas[y_pos - i][x_pos + j] =
                dot_canvas[y_pos - i][x_pos + j] | V.dot_View[V.height - i - 1][j] >> right; // 变换前面的部分
            if (x_pos + 1 + j > width - 1)
                continue;
            dot_canvas[y_pos - i][x_pos + 1 + j] =
                dot_canvas[y_pos - i][x_pos + 1 + j] | V.dot_View[V.height - i - 1][j] << left; // 变换后面的部分
        }
    }
}
