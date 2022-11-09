#ifndef _VIEW_H_
#define _VIEW_H_

#include "Canvas.hpp"
#include "Coord.hpp"

// View类的cpp文件为空

class View : public Canvas
{
private:
    int color_num;
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
    point P;

public:
    View();
    View(const string type, const int p_width, const int p_height, const string coord) : Canvas(type, p_width, p_height, coord), height(p_height), width(p_width), mono_width(p_width / 8 + 1), color_num(0) {}
    //直接使用Canvas的构造函数

    const int height;
    const int width;      // Canvas 长度
    const int mono_width; // mono状态下的width
    // Coord *p_view;
    // ~View()
    // {
    //     delete p_view;
    // }
};

#endif