#include "objreader/Object.hpp"
#include "graphics/BezierCurve.hpp"
  
using namespace std;
 
int main()
{
    Object obj1("obj/figure1.obj");
    obj1.Print();
    obj1.PrintNormals();
    obj1.PrintEquationsOfPlane();

    BezierCurve curve(2.1, 13.40, 20.0, 0.05);
    cout << "P1 = " << curve.GetP1()[0] << "," <<  curve.GetP1()[1] << "," << curve.GetP1()[2] << endl;
    cout << "P2 = " << curve.GetP2()[0] << "," <<  curve.GetP2()[1] << "," << curve.GetP2()[2] << endl;
    cout << "P3 = " << curve.GetP3()[0] << "," <<  curve.GetP3()[1] << "," << curve.GetP3()[2] << endl;
    cout << "P4 = " << curve.GetP4()[0] << "," <<  curve.GetP4()[1] << "," << curve.GetP4()[2] << endl;
    cout << "ymax = " << curve.Getymax() << endl;
    cout << "xmax =  " << curve.Getxmax() << endl;

    return 0;
}   
 

 