#include <vector>
#include <cstring>
using namespace std;
#ifndef _VIEW_H_
#define _VIEW_H_

class View
{
private:
    void create_gray(const int, const int);                // grayscale
    void create_mono(const int, const int);                // monochrome
    void printchar_gray(const int, const int, const char); // private
    void printchar_mono(const int, const int, const char); // private
    void line_gray(const int, const int, const int, const int);
    void line_mono(const int, const int, const int, const int);
    void bit_change(const int, const int); //两种存储方式的转化(char变为bit)
    int flag_View;                         // gray or mono

public:
    vector<vector<unsigned char>> dot_View; //需要从View直接访问？
    void printstr(const int, const int, const string);
    void line(const int, const int, const int, const int);
    int height;     //高度(行数)
    int width;      //宽度(列数)
    int true_width; // monochrome状态下的真实宽度
    View();
    View(const string, const int, const int);
};

#endif