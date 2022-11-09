#ifndef _COORD_H_
#define _COORD_H_
// coord.cpp为空 Coord类为抽象类 为interface

#include <vector>
#include <cstring>
#include <iostream>
using namespace std;
#include "View.hpp"
// #include "Coord_gray.hpp"
// #include "Coord_mono.hpp"

class Coord
{
protected:
    virtual void printchar(const int x, const int y, const char c, int color ) = 0; //纯虚函数
public:

    // NOTE 以下成员全部为public 确实需要直接访问 有没有办法避免 //用函数调用
    int height;
    int width;      // Canvas 长度
    int mono_width; // mono状态下的width
    int color_num;
    int color_real;
    vector<vector<unsigned char>> dot_canvas;
    enum type
    {
        grayscale,
        monochrome
    } flag_type; // gray or mono
    enum coord
    {
        world_coord,
        screen_coord
    } flag_coord;
    virtual void printstr(const int x, const int y, const string &str, int color ) = 0; //以下为纯虚函数
    virtual void printresults() = 0;
    virtual void color(int c) = 0;
    virtual void line(const int x0, const int y0, const int x1, const int y1, int color ) = 0;
    virtual void rect(int x1, int y1, int width, int height, int color ) = 0;
    virtual void showViewAt(int x1, int y1, View* ) = 0;
    virtual void remake(int x1, int y1, int width, int height) = 0;//将一块矩形区域全部清空（颜色为0）
};

#endif