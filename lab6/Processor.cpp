#include <vector>
#include <cstring>
#include <iostream>
#include <fstream>
#include <cmath>
// #include "stl_algo.h"
using namespace std;
// #include "Coord.hpp"
// #include "Coord_gray.hpp"
// #include "Coord_mono.hpp"
#include "Processor.hpp"
#include "point.hpp"

Processor::Processor(string script):filename(script)   //构造函数
{
    //判断坐标系
    if(strstr(script.c_str(), "world"))//注意strstr的参数是char*
        coord = "world_coord";
    else
        coord = "screen_coord";
    // cout << "coord = " << coord << endl;
    //NOTE 判断mono还是gray   简单注意一下下面的空格有没有问题
    if(strstr(script.c_str(), "-g 256"))     
        type = "grayscale";
    else
        type = "monochrome";
    
    //构造坐标系
    if(type == "grayscale")     //调用子类中的一个
    {
        p_coord = new Coord_gray(type, width, height, coord);
        // flag_type = grayscale;       //type判断     
    }

    else   
    {
        p_coord = new Coord_mono(type, width, height, coord);
        // flag_type = monochrome;        //type判断
    }

    //创建一个宏的容器
    p_macro = new Macro_vec();
    p_func = new Func_vec();
}


void Processor::read()
{
    ifstream infile(filename, ios::in | ios::binary);//打开文件
    if (!infile) // 打开失败
    {
        cout << "error opening source file." << endl;
        return;
    }
    int test = 0;
    while(infile.getline(cmd, 100))//100是对一行内字符个数的上限
    {
        if(strstr(cmd, "//"))
        {
            continue;
        }
        else if(strstr(cmd, "#"))
        {
            macro_def(cmd);
        }
        else if(strstr(cmd, "!"))
        {
            macro_use(cmd);
        }
        else if(strstr(cmd, "text"))
        {
            text(cmd);
        }
        else if(strstr(cmd, "color"))
        {
            color(cmd);
        }
        else if(strstr(cmd, "line"))
        {
            line(cmd);
        }
        else if(strstr(cmd, "}"))
        {
            // macro_end();
            flag_macro = 0;//重置，表示在宏定义之外
            // p_coord->printresults();
        }
        else
        {
            //空
        }
        // p_coord->printresults();
        // cout << "flag_macro = " << flag_macro << endl;
        // test++;
        // cout << "test = " << test << endl;
        // cout << "command = " << p_func->func_num << endl;
    }
    p_coord->printresults();//结束之后打印
    infile.close();
    // cout << "print sucessfully!" << endl;
}

void Processor::log()
{
    cout << "LOG : " << endl;
    cout << "number of commands : " << p_func->func_num << endl;
    cout << "length of lines : " << p_func->line_length << endl;
    cout << "output string : ";
    for (int i = 0; i < p_func->func_text.size(); i++)
    {
        if(p_func->func_text[i] == " ")
            continue;

        if(i == p_func->func_text.size() - 1)
        {
            cout << p_func->func_text[i];            
        }
        else
        {
            cout << p_func->func_text[i] << ",";
        }
    }

}

void Processor::text(char *cmd)//e.g. text(11, 0, "!")
{
    temp_width = 0;//清零初始化
    temp_height = 0;
    char *pos1 = strstr(cmd, "(") + 1;//找到text后面的位置
    char *pos2 = strstr(cmd, ",") + 1;//第一个","后面
    char *pos3 = strstr(pos2, ",") + 1;//第二个","后面 
    char *pos4 = strstr(pos3, "\"") + 1;//第一个引号
    char *pos5 = strstr(pos4, "\"");//第二个引号   
    string str2 = pos2;    
    string str1 = pos1;//转换为string

    // str.erase(remove(str.begin(), str.end(), ' '), str.end());
    // str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
    // BUG  WHY???
    // str1.erase(remove_if(str1.begin(), str1.end(), isspace), str1.end());


    while(pos2 - pos1 > 1 && *pos1 != ' ')//将char数组转化为int
    {
        if(*pos1 == ' ')
        {
            pos1++;
            continue;
        }
        // vector<int> a_int;
        // int sum;
        // cout << "temp_width = " << temp_width << endl;
        temp_width = temp_width * 10 + (int)*pos1 - 48;
        pos1++;//进一位
    }


    while(pos3 - pos2 > 1)
    {
        if(*pos2 == ' ')
        {
            pos2++;
            continue;
        }
        temp_height = temp_height * 10 + (int)*pos2 - 48;
        pos2++;
    }

    //将两个指针中间的部分转化为string(来源于lab3)
    char p_res[100] = {0};
    memcpy(p_res, pos4, pos5 - pos4);
    temp_string = string(p_res);
    if(flag_macro == 0)
    {
        p_coord->printstr(temp_width, temp_height, temp_string);
        p_func->func_num++;
        p_func->func_text.push_back(temp_string);
    }

    else   
    {
        view_vec[flag_macro-1]->printstr(temp_width, temp_height, temp_string);
        // //BUG
        //         cout << "color = " << view_vec[flag_macro - 1]->color_num << endl;
        p_macro->macro_func_num[flag_macro - 1]++;
        p_macro->text_name[flag_macro - 1]=temp_string;
    }
    // cout << "aaaa" << endl;
    // cout << "flag = " << flag_macro << endl;
    // view_vec[0]->printresults();
    // p_coord->printresults();
}

void Processor::color(char *cmd)//e.g. color(1)
{
    temp_color = 0;
    char *pos1 = strstr(cmd, "(") + 1;
    char *pos2 = strstr(cmd, ")");
    while (pos2 - pos1 > 0)
    {
        if(*pos1 == ' ')
        {
            pos1++;
            continue;
        }
        temp_color = temp_color * 10 + (int)*pos1 - 48;
        pos1++;
    }
    if(flag_macro == 0)
    {
        p_coord->color(temp_color);
        p_func->func_num++;
    }

    else
    {
        view_vec[flag_macro-1]->color(temp_color);
        p_macro->macro_func_num[flag_macro - 1]++;
    }
}

void Processor::line(char *cmd)//eg line(1, 2, 48, 47)
{
    temp_x1 = 0;
    temp_x2 = 0;
    temp_y1 = 0;
    temp_y2 = 0;
    char *pos1 = strstr(cmd, "(") + 1;
    char *pos2 = strstr(pos1, ",") + 1;
    char *pos3 = strstr(pos2, ",") + 1;
    char *pos4 = strstr(pos3, ",") + 1;
    char *pos5 = strstr(pos4, ")");
    while (pos2 - pos1 > 1)
    {
        if(*pos1 == ' ')
        {
            pos1++;
            continue;
        }
        temp_x1 = temp_x1 * 10 + (int)*pos1 - 48;
        pos1++;
    }
    while (pos3 - pos2 > 1)
    {
        if(*pos2 == ' ')
        {
            pos2++;
            continue;
        }
        temp_y1 = temp_y1 * 10 + (int)*pos2 - 48;
        pos2++;
    }
    while (pos4 - pos3 > 1)
    {
        if(*pos3 == ' ')
        {
            pos3++;
            continue;
        }
        temp_x2 = temp_x2 * 10 + (int)*pos3 - 48;
        pos3++;
    }
    while (pos5 - pos4 > 0)
    {
        if(*pos4 == ' ')
        {
            pos4++;
            continue;
        }
        temp_y2 = temp_y2 * 10 + (int)*pos4 - 48;
        pos4++;
    }
    // cout << "temp_x2 = " << temp_x2 << endl;
    double length = sqrt(pow(temp_x2 - temp_x1, 2) + pow(temp_y2 - temp_y1, 2));//line的长度
    if(flag_macro == 0)
    {
        p_coord->line(temp_x1, temp_y1, temp_x2, temp_y2);
        p_func->func_num++;
        p_func->line_length += length;
    }

    else
    {
        view_vec[flag_macro-1]->line(temp_x1, temp_y1, temp_x2, temp_y2);
        p_macro->macro_func_num[flag_macro - 1]++;
        p_macro->macro_line_length[flag_macro - 1] += length;
    }
}

void Processor::macro_def(char *cmd)//eg: #startTimeView(50,10){
{
    macro_num++;//宏定义数量加一
    flag_macro = macro_num;
    temp_width = 0;
    temp_height = 0;
    char *pos1 = strstr(cmd, "#") + 1;
    char *pos2 = strstr(cmd, "(") + 1;
    char *pos3 = strstr(cmd, ",") + 1;
    char *pos4 = strstr(cmd, ")") + 1;

    char p_res[100] = {0};
    memcpy(p_res, pos1, pos2 - pos1 - 1);
    temp_macro = string(p_res);

    while (pos3 - pos2 > 1)
    {
        if(*pos2 == ' ')
        {
            pos2++;
            continue;
        }
        temp_width = temp_width * 10 + (int)*pos2 - 48;
        pos2++;
    }
    while (pos4 - pos3 > 1)
    {
        if(*pos3 == ' ')
        {
            pos3++;
            continue;
        }
        temp_height = temp_height * 10 + (int)*pos3 - 48;
        pos3++;
    }
    //对宏集合的添加
    p_macro->macro_name.push_back(temp_macro);
    p_macro->macro_func_num.push_back(0);//存储宏定义的信息
    p_macro->macro_line_length.push_back(0);
    p_macro->text_name.push_back(" ");
    view_vec.push_back(new View(type, temp_width, temp_height, coord));//向View集合里初始化元素
    // p_macro->macro_width.push_back(temp_width);
    // p_macro->macro_height.push_back(temp_height);    
}

void Processor::macro_use(char *cmd)//eg: !startTimeView(5,30)
{
    temp_width = 0;
    temp_height = 0;
    char *pos1 = strstr(cmd, "!") + 1;
    char *pos2 = strstr(cmd, "(") + 1;
    char *pos3 = strstr(cmd, ",") + 1;
    char *pos4 = strstr(cmd, ")");
    
    while (pos3 - pos2 > 1)
    {
        if(*pos2 == ' ')
        {
            pos2++;
            continue;
        }
        temp_width = temp_width * 10 + (int)*pos2 - 48;
        pos2++;
    }
    while (pos4 - pos3 > 0)
    {
        if(*pos3 == ' ')
        {
            pos3++;
            continue;
        }
        temp_height = temp_height * 10 + (int)*pos3 - 48;
        pos3++;
    }
    string cmd_str = cmd;//转换为string为下面做准备
    for (int i = 0; i < macro_num; i++)//找到属于哪个宏
    {
        if(cmd_str.find(p_macro->macro_name[i]) != -1)//找到位置
        {
            if(flag_macro == 0)
                showViewAt(temp_width, temp_height, *view_vec[i]);
            else
            {
                // cout << "??" << endl;
                view_vec[flag_macro - 1]->showViewAt(temp_width, temp_height, *view_vec[i]);
                // cout << "!!" << endl;
            }
        //以下为统计数据
            p_func->func_num += p_macro->macro_func_num[i];
            p_func->line_length += p_macro->macro_line_length[i];
            p_func->func_text.push_back(p_macro->text_name[i]);
        }
    }


    // cout << "height = " << view_vec[1]->height << endl;
    // p_coord->printresults();
    // cout << "height = " << temp_height << endl;
}


void Processor::showViewAt(int x, int y, const View& V)
{
    // V.printresults();
    // p_coord->printresults();
    // cout << "flag_coord=" << p_view->flag_coord << endl; // BUG  已解决
    const int y_pos = (coord == "world_coord" ? p_coord->height - y : y); //两种坐标系
    if (type == "grayscale")
    {
        for (int i = 0; i < V.height; i++)
        {
            for (int j = 0; j < V.width; j++)
            {
                p_coord->dot_canvas[y_pos - V.p_view->height  + i][x  + j] = V.p_view->dot_canvas[i][j];
            }
        }
    }
    else
    {
        const int x_pos = (x - 1) / 8; // canvas中的真实位置
        // const int y_pos = p_view->height - y;      // canvas中的真实位置
        const int right = (x - 1) % 8;               //右移的位数
        const int left = 8 - right;                  // 左移的位数
        for (int i = 0; i < V.p_view->height; i++) // 对一个char的8个二进制数进行循环（字符表从上到下）（char从下到上）
        {
            if (y_pos - i > p_coord->height - 1 || y_pos - i < 0)
                continue;

            // unsigned char move_right = *(p_now)>>(right); // 右移之后
            // unsigned char move_left = *(p_now)<<(left); //左移之后
            for (int j = 0; j < V.p_view->width; j++)
            {
                if (x_pos + j > width - 1)
                    continue;

                p_coord->dot_canvas[y_pos - i][x_pos + j] =
                    p_coord->dot_canvas[y_pos - i][x_pos + j] | V.p_view->dot_canvas[V.p_view->height - i - 1][j] >> right; // 变换前面的部分
                if (x_pos + 1 + j > width - 1)
                    continue;
                p_coord->dot_canvas[y_pos - i][x_pos + 1 + j] =
                    p_coord->dot_canvas[y_pos - i][x_pos + 1 + j] | V.p_view->dot_canvas[V.p_view->height - i - 1][j] << left; // 变换后面的部分
            }
        }
    }
}

