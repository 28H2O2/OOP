#ifndef _INITIALIZE_H_
#define _INITIALIZE_H_
//可能纯粹是为了避免三个文件相互嵌套导致编译不通过
//但是为什么连接的时候总是出问题😂(和构造函数并且与相互的include有关)
#include "Coord.hpp"
#include "Coord_gray.hpp"
#include "Coord_mono.hpp"

class View
{
public:
    View(){};
    View(const string &script) //为初始化服务的构造函数
    {

        if (strstr(script.c_str(), "world")) //注意strstr的参数是char*
            _coord = "world_coord";
        else
            _coord = "screen_coord";
        if (strstr(script.c_str(), "-g 256"))
        {
            _type = "grayscale";
            p_coord = new Coord_gray(_type, 100, 60, _coord);
        }
        else
        {
            _type = "monochrome";
            p_coord = new Coord_mono(_type, 100, 60, _coord);
        }
    }
    View(const string type, const int p_width, const int p_height, const string coord) //为宏服务的构造函数
    {
        if (type == "grayscale") //调用子类中的一个
        {
            p_coord = new Coord_gray(type, p_width, p_height, coord);
            // flag_type = grayscale;       //type判断
        }

        else
        {
            p_coord = new Coord_mono(type, p_width, p_height, coord);
            // flag_type = monochrome;        //type判断
        }

    }
    // ~View();
    Coord *get()
    {
        return p_coord;
    }
    string getType()
    {
        return _type;
    }
    string getCoord()
    {
        return _coord;
    }
protected:
    Coord *p_coord; //关键是这个
    string _type;
    string _coord;
};

#endif
