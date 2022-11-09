#ifndef _MACROVEC_H_
#define _MACROVEC_H_


#include <vector>
#include <iostream>
#include <cstring>
using namespace std;
#include "View.hpp"
// #include "Observer.hpp"
class MacroVec  //储存宏    //当作ConcreteObserver
{
private:
    double line_length = 0;
    int func_num = 0;
    // vector<int> macro_height;
    ~MacroVec()//清除？
    {
        for(auto V:view_vec)
        {
            delete V;
        }
    }
public:
    void addLength(double length){
        line_length += length;
    }
    void addFuncNum(int n){
        func_num += n;
    }
    
    double getLength(){
        return line_length;
    }
    int getFuncNum(){
        return func_num;
    }

    void response(){
        return;
    }
    void drawtext(string name){
        text_name.push_back(name);
    }
    void drawline(double length){
        macro_line_length.push_back(length);
    }
    void drawcmd(int i){
        macro_func_num.push_back(i);
    }

    // void getView(){
    //     view_vec
    // }
    void getname();
    vector<int> macro_func_num;
    vector<double> macro_line_length;
    vector<string> text_name;
    vector<string> macro_name;
    vector<View *> view_vec;
    vector<string> func_text;
    // TODO vector 如何封装
};






#endif