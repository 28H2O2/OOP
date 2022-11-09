// #include <vector>
// #include <cstring>
// #include <iostream>
// #include "Canvas_gray.hpp"
// #include "Canvas_mono.hpp"
// using namespace std;

// #ifndef _Canvas_H_
// #define _Canvas_H_
// // class Canvas_gray;
// // class Canvas_mono;
// class Canvas
// {
// protected:
//     int height;
//     int width;  //Canvas 长度
//     int mono_width;//mono状态下的width
//     Canvas* p_canvas;   //指针
//     vector<vector<unsigned char> > dot_canvas;
//     enum type{grayscale, monochrome} flag_type;           //gray or mono
//     enum coord{world_coord, screen_coord} flag_coord;

// public:

//     void printstr(const int, const int, const string&);
//     void printcanvas();
//     Canvas();       //构造函数
//     Canvas(const string type, const int p_width, const int p_height,
//      const string coord): height(p_height), width(p_width), p_canvas(NULL)
//     {
//         if(type == "grayscale")
//             p_canvas = new Canvas_gray(p_width, p_height);
//         else   
//         {
//             p_canvas = new Canvas_mono(p_width, p_height);
//             mono_width = width / 8 + 1;//mono widthS
//         }    
//         if(coord == "world_coord")//coordinate
//             flag_coord = world_coord;
//         else
//             flag_coord = screen_coord;
//     }
//     ~Canvas()
//     { //析构函数
//         cout << "This program sucessfully finished!" << endl;
//         delete p_canvas;
//     }
// };


// #endif