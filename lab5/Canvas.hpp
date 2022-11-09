
#ifndef _CANVAS_H_
#define _CANVAS_H_

#include <vector>
#include <cstring>
#include <iostream>

#include "Coord.hpp"
#include "Coord_gray.hpp"
#include "Coord_mono.hpp"
#include "point.hpp"
#include "View.hpp"

using namespace std;

class View;
class Canvas
{
protected:
    const int height;
    const int width;  //Canvas 长度
    const int mono_width;//mono状态下的width
    int color_num;
    enum type{grayscale, monochrome} flag_type;           //gray or mono
    enum coord{world_coord, screen_coord} flag_coord;
    Coord* p_canvas;   //组合Coord类
    point P;

public:
    void printstr(const int, const int, const string&);
    void printresults();
    void showViewAt(const int, const int, const View&);
    void line(const int, const int, const int, const int);
    void color(int);
    Canvas();       
    Canvas(const string type, const int p_width, const int p_height, const string //构造函数
     coord): height(p_height), width(p_width), p_canvas(NULL), mono_width(p_width / 8 + 1), color_num(0)
    {
        if(type == "grayscale")     //调用子类中的一个
        {
            p_canvas = new Coord_gray(type, width, height, coord);
            flag_type = grayscale;       //type判断     
        }

        else   
        {
            p_canvas = new Coord_mono(type, width, height, coord);
            flag_type = monochrome;        //type判断
        }    

    }
    ~Canvas()
    { //析构函数
        // cout << "This program sucessfully finished!" << endl;
        delete p_canvas;
    }
};

#endif