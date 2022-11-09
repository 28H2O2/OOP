// #include <iostream>
// #include <vector>
// #include <cstring>
#ifndef _CANVASMONO_H_
#define _CANVASMONO_H_

#include "Coord.hpp"
#include "point.hpp"

using namespace std;

class Coord_mono : public Coord
{
private:
    point P;
    void printchar(const int, const int, const char);

public:
    Coord_mono();
    Coord_mono(const string type, int p_width, int p_height, const string coord)
    {
        height = p_height;
        width = p_width;
        mono_width = p_width / 8 + 1;
        flag_type = grayscale;
        color_num = 0;
        dot_canvas.resize(p_height); //创建
        for (int i = 0; i < p_height; i++)
        {
            dot_canvas[i].resize(p_width / 8 + 1);
        }

        if (coord == "world_coord") // coordinate
            flag_coord = world_coord;
        else
            flag_coord = screen_coord;
    }
    void line(const int x0, const int y0, const int x1, const int y1);
    void bit_change(const int, const int);
    void color(int c);
    void printstr(const int, const int, const string &);
    // void showViewAt(const int, const int, const View&);
    void printresults();
};

#endif