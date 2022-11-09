#ifndef _SCRIPTPROCESSOR_H_
#define _SCRIPTPROCESSOR_H_
//负责将脚本指令分解为各个部分（数据）

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;
// #include "Command.hpp"
// #include "ConcreteCommand.hpp"
#include "CommandExecutor.hpp"
#include "Coord.hpp"
#include "Coord_gray.hpp"
#include "Coord_mono.hpp"
#include "MacroVec.hpp"

class ScriptProcessor
{
 public:
     void read(const string &str);
     void log();
     // CommandExecutor* pExe = new CommandExecutor;
     ScriptProcessor(View* I):pI(I)
     {
         pExe = new CommandExecutor(I);
     }
     ~ScriptProcessor()//删除指针
     {
         delete pExe;
        //  delete pMacro;
     }

 private:
     CommandExecutor *pExe;
     MacroVec *pMacro = new MacroVec;
     View *pI;
     int macro_num = 0; //记录宏的数量
     int flag_macro = 0; //用于判断行是否在宏定义内部

};


// TODO 感觉可以拆成两个类来做 但是应该如何根据不同的类别传递不同的值？
void ScriptProcessor::read(const string& str)//将一行脚本分解   
{
    // char script[100] = str.c_str();
    if(strstr(str.c_str(), "//"))
    {
        return;
    }

    else if(strstr(str.c_str(), "using"))//e.g. using predef.txt
    {
        char *pos1 = strstr(str.c_str(), "\"") + 1;
        char *pos2 = strstr(pos1, "\"");
        char p_res[100] = {0};
        memcpy(p_res, pos1, pos2 - pos1);
        string filename = string(p_res);

        // ScriptProcessor S = ScriptProcessor(pI);
        // TODO ↓应当换一个地方？        
        ifstream infile(filename, ios::in | ios::binary);//打开文件
        if (!infile) // 打开失败
        {
            cout << "error opening source file." << endl;
            return;
        }
        char cmd[100];
        while(infile.getline(cmd, 100))
        {
            read(cmd);
        }

        // macro_read(str);
        // TODO
    }

    else if(strstr(str.c_str(), "#"))
    {
        macro_num++;//宏定义数量加一
        flag_macro = macro_num;
        int temp_width = 0;
        int temp_height = 0;
        char *pos1 = strstr(str.c_str(), "#") + 1;
        char *pos2 = strstr(str.c_str(), "(") + 1;
        char *pos3 = strstr(str.c_str(), ",") + 1;
        char *pos4 = strstr(str.c_str(), ")") + 1;

        char p_res[100] = {0};
        memcpy(p_res, pos1, pos2 - pos1 - 1);
        string temp_macro = string(p_res);//宏的名字

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
        // NOTE 以下为宏的操作
        pMacro->macro_name.push_back(temp_macro);
        pMacro->drawcmd(0);//存储宏定义的信息
        pMacro->drawline(0);
        pMacro->drawtext(" ");
        pMacro->view_vec.push_back(new View(pI->getType(), temp_width, temp_height, pI->getCoord()));//向View集合里初始化元素
    }

    else if(strstr(str.c_str(), "text"))
    {
        int temp_width = 0;//清零初始化
        int temp_height = 0;
        char *pos1 = strstr(str.c_str(), "(") + 1;//找到text后面的位置
        char *pos2 = strstr(str.c_str(), ",") + 1;//第一个","后面
        char *pos3 = strstr(pos2, ",") + 1;//第二个","后面 
        char *pos4 = strstr(pos3, "\"") + 1;//第一个引号
        char *pos5 = strstr(pos4, "\"");//第二个引号   
    
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
        string temp_string = string(p_res);

        if(flag_macro == 0)
        {
            pExe->ExecutorCommand(new text(temp_width, temp_height, temp_string));
            pMacro->addFuncNum(1);
            pMacro->func_text.push_back(temp_string);
        }

        else   
        {
            pMacro->view_vec[flag_macro-1]->get()->printstr(temp_width, 
             temp_height, temp_string, pMacro->view_vec[flag_macro-1]->get()->color_num);
            pMacro->macro_func_num[flag_macro - 1]++;
            pMacro->text_name[flag_macro - 1]=temp_string;
        }

    } 
    
    else if(strstr(str.c_str(), "!"))//showview打印宏
    {
        int temp_width = 0;
        int temp_height = 0;
        char *pos1 = strstr(str.c_str(), "!") + 1;
        char *pos2 = strstr(str.c_str(), "(") + 1;
        char *pos3 = strstr(str.c_str(), ",") + 1;
        char *pos4 = strstr(str.c_str(), ")");
        
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
        // string cmd_str = cmd;//转换为string为下面做准备
        for (int i = 0; i < macro_num; i++)//找到属于哪个宏
        {
            if(str.find(pMacro->macro_name[i]) != -1)//找到位置
            {
                if(flag_macro == 0)//直接执行
                    pExe->ExecutorCommand(new showview(temp_width, temp_height, pMacro->view_vec[i]));
                    // showViewAt(temp_width, temp_height, pMacro->view_vec[i]);
                else    //嵌套宏定义
                {
                    // cout << "??" << endl;
                    // TODO
                    pMacro->view_vec[flag_macro - 1]->get()->showViewAt(temp_width, temp_height, pMacro->view_vec[i]);
                    
                    // cout << "!!" << endl;
                }
            // 以下为统计数据
                pMacro->addFuncNum(pMacro->macro_func_num[i]);
                pMacro->addLength(pMacro->macro_line_length[i]);
                pMacro->func_text.push_back(pMacro->text_name[i]);
            }
        }
        // TODO

    }
    
    else if(strstr(str.c_str(), "color"))
    {
        int temp_color = 0;
        char *pos1 = strstr(str.c_str(), "(") + 1;
        char *pos2 = strstr(str.c_str(), ")");
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
            pExe->ExecutorCommand(new color(temp_color));
            // cout << "color_ = " << p_coord->color_num << endl;
            pMacro->addFuncNum(1);
        }

        else
        {
            pMacro->view_vec[flag_macro-1]->get()->color(temp_color);
            // BUG
            // cout << "color = " << view_vec[flag_macro - 1]->color_num << endl;
            pMacro->macro_func_num[flag_macro - 1]++;
        }
        // element = new color(temp_color);
        // element->execute();//执行
    }
    
    else if(strstr(str.c_str(), "line"))
    {
    int temp_x1 = 0;
    int temp_x2 = 0;
    int temp_y1 = 0;
    int temp_y2 = 0;
    char *pos1 = strstr(str.c_str(), "(") + 1;
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
            pExe->ExecutorCommand(new line(temp_x1, temp_y1, temp_x2, temp_y2));  
            pMacro->addFuncNum(1);
            pMacro->addLength(length);
        }

        else
        {
            pMacro->view_vec[flag_macro-1]->get()->line(temp_x1, temp_y1, 
                temp_x2, temp_y2, pMacro->view_vec[flag_macro-1]->get()->color_num);
            pMacro->macro_func_num[flag_macro - 1]++;
            pMacro->macro_line_length[flag_macro - 1] += length;
        }
    }
    
    else if(strstr(str.c_str(), "rect"))
    {
        int temp_x1 = 0;
        int temp_y1 = 0;
        int temp_width = 0;
        int temp_height = 0;
        char *pos1 = strstr(str.c_str(), "(") + 1;
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
            temp_width = temp_width * 10 + (int)*pos3 - 48;
            pos3++;
        }
        while (pos5 - pos4 > 0)
        {
            if(*pos4 == ' ')
            {
                pos4++;
                continue;
            }
            temp_height = temp_height * 10 + (int)*pos4 - 48;
            pos4++;
        }


        if(flag_macro == 0)
        {
            pExe->ExecutorCommand(new rect(temp_x1, temp_y1, temp_width, temp_height));  
            pMacro->addFuncNum(1);
    
        }

        else   
        {
            pMacro->view_vec[flag_macro - 1]->get()->rect(temp_x1, temp_y1, temp_width,
                temp_width, pMacro->view_vec[flag_macro - 1]->get()->color_num);
            pMacro->macro_func_num[flag_macro - 1]++;
        }


    }

    else if(strstr(str.c_str(), "show"))
    {
        pI->get()->printresults();//直接输出画布
        // pExe->ExecutorCommand(new show(1));
    }

    else if(strstr(str.c_str(), "undo"))
    {
        pExe->Undo();
        pMacro->addFuncNum(1);
    }
    
    else if(strstr(str.c_str(), "redo"))
    {
        pExe->Redo();
        pMacro->addFuncNum(1);
    }
    
    else if(strstr(str.c_str(), "}"))
    {
        flag_macro = 0;//重置，说明宏定义结束
    }
}
void ScriptProcessor::log()
{
    cout << "LOG : " << endl;
    cout << "number of commands : " << pMacro->getFuncNum() << endl;
    cout << "length of lines : " << pMacro->getLength() << endl;
    cout << "output string : ";
    for (int i = 0; i < pMacro->func_text.size(); i++)
    {
        if(pMacro->func_text[i] == " ")
            continue;

        if(i == pMacro->func_text.size() - 1)
        {
            cout << pMacro->func_text[i];            
        }
        else
        {
            cout << pMacro->func_text[i] << ",";
        }
    }
}
#endif