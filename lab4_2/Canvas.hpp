#include <vector>
#include <cstring>
#ifndef _Canvas_H_
#define _Canvas_H_

class Canvas
{
protected:
    vector<vector<unsigned char>> dot_canvas;
    int height;                                            //高度(行数)
    int width;                                             //宽度(列数)
    int true_width;                                        // monochrome状态下的真实宽度
    int flag_Canvas;                                       // gray or mono
    void create_gray(const int, const int);                // grayscale
    void create_mono(const int, const int);                // monochrome
    void printchar_gray(const int, const int, const char); // private
    void printchar_mono(const int, const int, const char); // private
    void printcanvas_gray() const;
    void printcanvas_mono() const;
    void showViewAt_gray(const int, const int, View);
    void showViewAt_mono(const int, const int, View);

public:
    void printstr(const int, const int, const string);
    void showViewAt(const int, const int, View);
    void printcanvas() const;
    Canvas();                                   // default function
    Canvas(const string, const int, const int); // print dots
    ~Canvas()
    { //析构函数
        cout << "This program sucessfully finished!" << endl;
    }
};

#endif
