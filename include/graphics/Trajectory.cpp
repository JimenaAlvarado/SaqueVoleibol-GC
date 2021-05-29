#include "Trajectory.hpp"
#include "BezierCurve.hpp"
#include <vector>

using namespace std; 
	
Trajectory::Trajectory()
{
	
}
	
Trajectory::~Trajectory()
{
	
}

vector<Vertex> Trajectory::lineal(Vertex init, Vertex end, float dt)
{  
    vector<Vertex> line;

    for(float t = 0.0; t <= 1.0 + dt; t += dt)
    {
        Vertex point;
        point.SetX(init.X() + (t*(end.X()-init.X())));
        point.SetY(init.Y() + (t*(end.Y()-init.Y())));
        point.SetZ(init.Z() + (t*(end.Z()-init.Z())));
        line.push_back(point);
    }

    return line;
}

vector<Vertex> Trajectory::curve(Vertex p1, Vertex p2, Vertex p3, Vertex p4, float dt)
{
    BezierCurve bc(p1, p2, p3, p4, dt);
    vector<Vertex> curve;

    for(arma::frowvec v : bc.GetCurve())
    {
        Vertex vertex(v[0], v[1], v[2]);
        curve.push_back(vertex);
    }
    
    return curve;
}