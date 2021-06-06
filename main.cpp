#include "include/graphics/Graphic.hpp"

using namespace std;
 
int main()
{
    Graphic g;
    if(g.newWindow(800, 600, 0.8, 0.8, 0.8, 0.0) == -1)
        return -1; 
    g.openWindow();

    return 0;
}   