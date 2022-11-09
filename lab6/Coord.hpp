#ifndef _COORD_H_
#define _COORD_H_
// coord.cpp为空 Coord类为抽象类 为interface

#include <vector>
#include <cstring>
#include <iostream>
using namespace std;

// #include "Coord_gray.hpp"
// #include "Coord_mono.hpp"

class Coord
{
protected:
    virtual void printchar(const int x, const int y, const char c) = 0; //纯虚函数
public:
    // Coord();
    // Coord(const string type, const int p_width, const int p_height, const string
    //  coord): height(p_height), width(p_width), p_canvas(NULL), mono_width(p_width / 8 + 1){}
    // NOTE 以下成员全部为public 确实需要直接访问 有没有办法避免
    int height;
    int width;      // Canvas 长度
    int mono_width; // mono状态下的width
     int color_num;
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
    virtual void printstr(const int x, const int y, const string &str) = 0; //以下为纯虚函数
    virtual void printresults() = 0;
    virtual void color(int c) = 0;
    virtual void line(const int x0, const int y0, const int x1, const int y1) = 0;
};

#endif