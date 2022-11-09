
using namespace std;
#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include "View.hpp"
// #include "Canvas.hpp"
#include "asciis.h"

void View::printstr(const int x, const int y, const string &str)
{
    p_view->printstr(x, y, str);
}

void View::printresults()
{
    p_view->printresults();
}

void View::color(int c)
{
    p_view->color(c);
}

void View::line(const int x0, const int y0, const int x1, const int y1)
{
    p_view->line(x0, y0, x1, y1);
}

void View::showViewAt(const int x, const int y, const View& V)
{
    // cout << "flag_coord=" << p_view->flag_coord << endl; // BUG  已解决
    const int y_pos = (p_view->flag_coord == world_coord ? p_view->height - y : y+1); //两种坐标系
    if (flag_type == grayscale)
    {
        for (int i = 0; i < V.height; i++)
        {
            for (int j = 0; j < V.width; j++)
            {
                // cout << "x+j=" << x + j;
                // cout << " V.p_view->dot_canvas[i][j]=" << (int)V.p_view->dot_canvas[i][j];
                // cout << "y_pos - V.p_view->height + i=" << y_pos - V.p_view->height  + i << endl;
                
                p_view->dot_canvas[y_pos - V.p_view->height + i][x + j] = V.p_view->dot_canvas[i][j];
            }
        }
    }
    else
    {
        const int x_pos = (x - 1) / 8; // canvas中的真实位置
        // const int y_pos = p_view->height - y;      // canvas中的真实位置
        const int right = (x - 1) % 8;               //右移的位数
        const int left = 8 - right;                  // 左移的位数
        for (int i = 0; i < V.p_view->height; i++) // 对一个char的8个二进制数进行循环（字符表从上到下）（char从下到上）
        {
            if (y_pos - i > p_view->height - 1 || y_pos - i < 0)
                continue;

            // unsigned char move_right = *(p_now)>>(right); // 右移之后
            // unsigned char move_left = *(p_now)<<(left); //左移之后
            for (int j = 0; j < V.p_view->width; j++)
            {
                if (x_pos + j > width - 1)
                    continue;

                p_view->dot_canvas[y_pos - i][x_pos + j] =
                    p_view->dot_canvas[y_pos - i][x_pos + j] | V.p_view->dot_canvas[V.p_view->height - i - 1][j] >> right; // 变换前面的部分
                if (x_pos + 1 + j > width - 1)
                    continue;
                p_view->dot_canvas[y_pos - i][x_pos + 1 + j] =
                    p_view->dot_canvas[y_pos - i][x_pos + 1 + j] | V.p_view->dot_canvas[V.p_view->height - i - 1][j] << left; // 变换后面的部分
            }
        }
    }
}