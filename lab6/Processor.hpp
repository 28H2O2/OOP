#ifndef _PROCESSOR_H_
#define _PROCESSOR_H_

#include <vector>
#include <cstring>
#include <iostream>
#include <fstream>
using namespace std;
#include "Coord.hpp"
#include "Coord_gray.hpp"
#include "Coord_mono.hpp"
#include "point.hpp"
#include "macro_vec.hpp"
#include "View.hpp"
#include "func_vec.hpp"

class Processor
{
private:
    Coord *p_coord;
    Macro_vec *p_macro;
    Func_vec *p_func;
    const string filename;
    string type;
    string coord;
    int width = 100;//默认画布大小
    int height = 60;
    int flag_macro = 0;//用于判断行是否在宏定义内部
    int macro_num = 0;
    //  NOTE ↓这样是否会出问题
    // ifstream infile;
    char cmd[100];//用于存储文件中每一行的指令
    void macro_def(char *cmd);
    void macro_use(char *cmd);
    void macro_end();//用于宏定义的结束
    void text(char *cmd);
    void color(char *cmd);
    void line(char *cmd);
    int temp_width;//用于传值的时候临时存储
    int temp_height;
    int temp_color;
    int temp_x1, temp_x2;
    int temp_y1, temp_y2;
    string temp_macro;//宏的名字
    string temp_string;
    vector<View *> view_vec;

public:
    Processor();
    Processor(string script);//构造函数：初始化颜色与坐标系，打开文件
    ~Processor()
    {
        delete p_coord;
        delete p_macro;
        delete p_func;
        for(auto vec:view_vec)//删除容器中的函数
            delete vec;
        // cout << "goodbye!" << endl;
    }
    void read();//开始读取每一行的操作
    void log();//输出日志
    void showViewAt(int x1, int y1, const View& V);
};

#endif