#include "include/objreader/Object.hpp"
#include "include/graphics/Trajectory.hpp"
#include <vector>

using namespace std;
 
int main()
{
    Object ball("obj/ball.obj");
    Object hand("obj/hand.obj");

    Trajectory tray;
    Vertex p1(-1, -1, 0.0);
    Vertex p2(-0.8, 0.5, 0.0);
    Vertex p3(-0.2, 0.5, 0.0);
    Vertex p4(0.0, -1, 0.0);
    vector <Vertex> curve = tray.curve(p1, p2, p3, p4, 0.1);

    cout << "Curva de Bezier" << endl;
    for(Vertex v : curve)
        cout << v.X() << " " << v.Y() << " " << v.Z() << endl;

    return 0;
}   
 

 