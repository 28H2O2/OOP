
#ifndef _VIEW_H_
#define _VIEW_H_

#include <vector>
#include <cstring>
#include <iostream>

#include "Coord.hpp"
#include "Coord_gray.hpp"
#include "Coord_mono.hpp"
#include "point.hpp"
// #include "View.hpp"

using namespace std;

class View;
class View
{
protected:

    enum type{grayscale, monochrome} flag_type;           //gray or mono
    enum coord{world_coord, screen_coord} flag_coord;
    point P;

public:
    const int height;
    const int width;  //Canvas 长度
    const int mono_width;//mono状态下的width
    int color_num;
    Coord* p_view;   //组合Coord类
    void printstr(const int, const int, const string&);
    void printresults();
    void showViewAt(const int, const int, const View&);
    void line(const int, const int, const int, const int);
    void color(int);
    // Canvas();       
    View(const string type, const int p_width, const int p_height, const string //构造函数
     coord): height(p_height), width(p_width), p_view(NULL), mono_width(p_width / 8 + 1), color_num(0)
    {
        if(type == "grayscale")     //调用子类中的一个
        {
            p_view = new Coord_gray(type, width, height, coord);
            flag_type = grayscale;       //type判断     
        }

        else   
        {
            p_view = new Coord_mono(type, width, height, coord);
            flag_type = monochrome;        //type判断
        }    
        if (coord == "world_coord") // coordinate
            flag_coord = world_coord;
        else
            flag_coord = screen_coord;
    }
    ~View()
    { //析构函数
        // cout << "This program sucessfully finished!" << endl;
        delete p_view;
    }
};

#endif