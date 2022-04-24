#include <iostream>
#include <cstring>
#include <vector>
#define G "grayscale"
#define M "monochrome"
using namespace std;
#include "View.cpp"
#include "Canvas.cpp"
// #include "View.hpp"
// #include "Canvas.hpp"

int main()
{

    Canvas canvas(M, 100, 80);
    View weatherView(M, 80, 60);
    weatherView.printstr(5, 15, "020322");
    weatherView.printstr(5, 35, "temp:-1~5");
    weatherView.line(0, 0, 0, 59);
    weatherView.line(0, 59, 79, 59);
    weatherView.line(79, 59, 79, 0);
    weatherView.line(0, 0, 79, 0);


    canvas.showViewAt(5, 5, weatherView);
    canvas.printcanvas();

    // Canvas canvas("grayscale", 100, 55);
    // canvas.printstr(10, 10, "OOP Lab4");
    // canvas.printstr(50, 50, "boundary");
    // canvas.printcanvas();
    
    return 0;
}
