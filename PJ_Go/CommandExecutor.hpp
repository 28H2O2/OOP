#ifndef _COMMANDEXECUTOR_H_
#define _COMMANDEXECUTOR_H_

#include <iostream>
#include <stack>
#include <string>
using namespace std;
#include "Command.hpp"
#include "ConcreteCommand.hpp"
// #include "Coord.hpp"

// class Command;
// class color;
class CommandExecutor
{
public:
    CommandExecutor(View* I):_I(I){}
    ~CommandExecutor()
    {
        delete _I;

    }

    void ExecutorCommand(Command *pCmd)
    {
        pCmd->execute(_I);
        // pCmd->p_coord->printresults(); //打印画布
        UndoCmd.push(pCmd);
        // UndoCoord.push(*(pCmd->p_coord));//Canvas快照
    }
    void Undo()
    {
        if (UndoCmd.size() < 2)
        {
            cout << "undo failed." << endl; //无法后退撤销没有数据
            return;
        }
        cout << "undo: " << endl;

        auto pCmd = UndoCmd.top(); //当前命令

        pCmd->undo(_I); //当前命令undo执行

        RedoCmd.push(pCmd); //保存当前命令到Redo的stack中

        UndoCmd.pop(); //从undo的stack中弹出

        pCmd = UndoCmd.top(); //还原到上个命令
    }
    void Redo()
    {
        if (RedoCmd.empty())
        {
            //无法前进重做没有数据
            cout << "redo failed. " << endl;
            return;
        }

        cout << "redo: " << endl;

        auto pCmd = RedoCmd.top();//redo的stack顶部

        pCmd->execute(_I);//直接执行

        RedoCmd.pop();//弹回undo的stack

        UndoCmd.push(pCmd);
    }

private:
    View *_I;
    stack<Command *> UndoCmd;
    stack<Command *> RedoCmd;
    // TODO 如何清除栈里的指针
    // stack<Coord> UndoCoord;
    // stack<Coord> RedoCoord;
    stack<color> color_stack;
};

#endif