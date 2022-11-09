#ifndef COMMANDER_H_
#define COMMANDER_H_

#include <iostream>
using namespace std;
// #include "Coord.hpp"
// #include "CommandExecutor.hpp"
class View;
class Command
{
public:
    // friend class CommandExecutor;//友元类，使得每次执行后可以直接打印
    virtual void execute(View*) = 0;
    virtual void undo(View* ) = 0;
    virtual void redo() = 0;

protected:
    // Coord *p_coord;
};


#endif
