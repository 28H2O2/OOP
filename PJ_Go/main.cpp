#include <vector>
#include <cstring>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
#include "ScriptProcessor.hpp"
#include "View.hpp"
#include "Coord_gray.cpp"
#include "Coord_mono.cpp"


int main()
{
    string script_in;
    cout << "Please input a script!" << endl;
    getline(cin, script_in);

    // script_in = "draw -g 256 -c world";
    View *I = new View(script_in);
    ScriptProcessor *P = new ScriptProcessor(I);
    if(strstr(script_in.c_str(), "txt") == NULL)//进入交互模式
    {

        cout << "Let's interact!" << endl;
        while(1)
        {
            string script_in;
            cout << "Please input a script!" << endl;
            getline(cin, script_in);
            if(script_in == "quit")//退出程序
            {
                cout << "Goodbye!" << endl;
                break;
            }
            else if(script_in == "stat")
            {
                P->log();//统计数据
            }
            P->read(script_in);
            
        }
        P->log();

    }
    else if(strstr(script_in.c_str(), "txt")) //进入读取文件模式
    {
        ifstream infile(script_in, ios::in | ios::binary);//打开文件
        if (!infile) // 打开失败
        {
            cout << "error opening source file." << endl;
            // return;
        }
        // int test = 0;
        char cmd[100];
        while(infile.getline(cmd, 100))//100是对一行内字符个数的上限
        {
            P->read(cmd);
        }
        P->log();
    }

    delete P;
    // delete I;
    // BUG Uknown Signal?
}