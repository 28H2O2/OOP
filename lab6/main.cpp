#include <vector>
#include <cstring>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
#include "Processor.cpp"
#include "Coord_mono.cpp"
#include "Coord_gray.cpp"
#include "point.cpp"
#include "View.cpp"

int main()
{

    // cout << "Please input the script" << endl;
    string script_in;
    cout << "Please input a number!" << endl;
    int test;
    cin >> test;
    switch (test)
    {
        case 1:
            script_in = "draw -g 2 -c world script1.txt";
        break;
        case 2:
            script_in = "draw -g 256 -c world script2.txt";
        break;
        case 3:
            script_in = "draw -g 256 -c world script3.txt";
        break;
        case 4:
            script_in = "draw -g 256 -c screen script4.txt";
        break;
        default:
        break;
    }
    // getline(cin, script_in);
    cout << script_in << endl;
    Processor P(script_in);//创建处理器
    P.read();//读每一行
    P.log();//数据统计
    return 0;
}

