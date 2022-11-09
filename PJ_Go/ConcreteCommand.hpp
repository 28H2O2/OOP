#ifndef CONCRETE_COMMAND_H_
#define CONCRETE_COMMAND_H_

#include <iostream>
#include <memory>
#include <vector>
#include <stack>
using namespace std;
#include "Command.hpp"
// #include "ScriptProcessor.hpp"
#include "View.hpp"

// class Command;
// class ScriptProcessor;
class text:public Command
{
public:
    // using View::View;
    text();
    text(int x, int y, string str):_x(x), _y(y), _str(str){}
    ~text(){}
    void execute(View* I) 
    {
        I->get()->printstr(_x, _y, _str, I->get()->color_num);
        I->get()->printresults();
    }
    void undo(View* I)
    {
        I->get()->printstr(_x, _y, _str, 0);
        I->get()->printresults();
    }

    void redo() override
    {

    }

private:
    int _x;
    int _y;
    int _color;
    string _str;

};

class color:public Command
{

public:
    color();
    color(int colornum):_colornum(colornum){}

    void execute(View* I) 
    {
        I->get()->color(_colornum);
        // I->get()->printresults();
        UndoColor.push(_colornum);
    }

    void undo(View* I) 
    {
        int ColorTop = UndoColor.top();
        RedoColor.push(ColorTop);
        UndoColor.pop();
        ColorTop = UndoColor.top();
        I->get()->color(ColorTop);
        I->get()->printresults();   
    }

    void redo() override
    {
        int ColorTop = RedoColor.top();
        UndoColor.push(ColorTop);
        RedoColor.pop();
    }

private:
    int _colornum;
    static stack<int> UndoColor;//可以使得所有color类都能够访问
    static stack<int> RedoColor;

};

stack<int> color::UndoColor;//在外部初始化
stack<int> color::RedoColor;

class line:public Command
{
public:
    line();
    line(int x1, int y1, int x2, int y2):_x1(x1), _y1(y1), _x2(x2), _y2(y2){}
    ~line(){}
    void execute(View* I) 
    {
        I->get()->line(_x1, _y1, _x2, _y2, I->get()->color_num);
        I->get()->printresults();
    }

    void undo(View* I) 
    {
        I->get()->line(_x1, _y1, _x2, _y2, 0);
        I->get()->printresults();
    }

    void redo() override
    {

    }

private:
    int _x1;
    int _y1;
    int _x2;
    int _y2;
    int _color;


};


class rect:public Command
{
public:
    rect();
    rect(int x1, int y1, int width, int height):_x1(x1), _y1(y1), _width(width), _height(height)
    {

    }
    void execute(View* I) 
    {
        I->get()->rect(_x1, _y1, _width, _height, I->get()->color_num);
        I->get()->printresults();
    }
    void undo(View* I) 
    {
        I->get()->rect(_x1, _y1, _width, _height, 0);
        I->get()->printresults();
    }
    void redo() override
    {

    }

private:
    int _x1;
    int _y1;
    int _width;
    int _height;
    int _color;
};


class showview:public Command
{
public:
    showview();
    showview(int x1, int y1, View* V):_x1(x1), _y1(y1), _V(V){}

    void execute(View* I)
    {
        I->get()->showViewAt(_x1, _y1, _V);
        I->get()->printresults();
    }
    void undo(View *I)
    {
        I->get()->remake(_x1, _y1, _V->get()->width, _V->get()->height);//清空View的整块矩形区域
        I->get()->printresults();
    }
    void redo()
    {
        
    }

private:
    int _x1;
    int _y1;
    int _color;
    View *_V;
};

#endif