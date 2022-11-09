#include <iostream>
#include <cstring>
#include <vector>

using namespace std;
#include "View.cpp"
#include "Canvas.cpp"//Canvas5.cpp
#include "Coord_mono.cpp"
#include "Coord.cpp"
#include "Coord_gray.cpp"
#include "point.cpp"

int main()
{
    Canvas canvas("grayscale", 200, 80, "world_coord");
    canvas.color(70);
    canvas.printstr(20, 40, "HCYY FOREVER");
    canvas.printstr(20, 25, "A THOUSAND YEARS");
    canvas.printstr(100, 10, "2022.5.10");

    canvas.line(50, 0, 64, 6);
    canvas.line(64, 6, 64, 12);
    canvas.line(64, 12, 56, 16);
    canvas.line(56, 16, 50, 8);
    canvas.line(50, 8, 44, 16);
    canvas.line(44, 16, 36, 12);
    canvas.line(36, 12, 36, 6);
    canvas.line(36, 6, 50, 0);

    canvas.printresults();
}