#include <iostream>
#include <cstring>
#include <vector>

using namespace std;
#include "Canvas.cpp"
#include "Coord_mono.cpp"
#include "Coord_gray.cpp"
#include "point.cpp"



void test1()
{
    Canvas canvas("monochrome", 100, 55, "screen_coord");
    canvas.color(1);
    canvas.printstr(10, 45, "OOP Lab5");
    canvas.printstr(50, 5, "boundary");
    canvas.printresults();

}

void test2()
{
    Canvas canvas("grayscale", 200, 90, "screen_coord");
    canvas.color(255);
    canvas.printstr(40, 20, "Weather System");

    View tempView("grayscale", 150, 20, "world_coord");
    tempView.color(33);
    tempView.printstr(5, 5, "temp:15~21");
    tempView.line(0, 0, 0, 19);
    tempView.line(0, 19, 149, 19);
    tempView.line(149, 19, 149, 0);
    tempView.line(0, 0, 149, 0);
    canvas.showViewAt(25, 50, tempView);

    View dataView("grayscale", 150, 20, "world_coord");
    dataView.color(70);
    dataView.printstr(5, 5, "date:020427");
    dataView.line(0, 0, 0, 19);
    dataView.line(0, 19, 149, 19);
    dataView.line(149, 19, 149, 0);
    dataView.line(0, 0, 149, 0);    
    canvas.showViewAt(25, 70, dataView);
    
    canvas.printstr(120, 80, "OOP 2022");

    canvas.printresults();
}

int main()
{
    cout<<"please input 1 or 2"<<endl;
    int a;
    cin>>a;

    if(a == 1)
        test1();
    else
        test2();
    
    return 0;
}