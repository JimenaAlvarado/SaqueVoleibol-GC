#include "Net.hpp"  
#include <GLFW/glfw3.h>
	
Net::Net()
{
	
}
	
Net::Net(float _x, float _y, float _z, float _red, float _green, float _blue, float _scale)
{
    xo = _x; yo = _y; zo = _z;
    val_scale = _scale; 
    red = _red; green = _green; blue = _blue;
    val_angle = 0.0;
    Object _obj("obj/net.obj");
    obj = _obj;
    Mtr.eye(4,4);  
}

void Net::draw()
{
    glBegin(GL_TRIANGLES);
    glColor3f(red, green, blue);
    for(Face f : obj.GetFaces())
    {   
        for(Vertex v : f.GetVertices())
        {
            arma::fcolvec v_tr = Mtr * v.Homog();
            v_tr = v_tr / v_tr[3];
            glVertex3f(v_tr[0], v_tr[1], v_tr[3]);
        }
    }
    glEnd();
}

void Net::setPosInit(float _x, float _y, float _z)
{
     xo = _x; 
     yo = _y; 
     zo = _z;
}

void Net::setColor(float _red, float _green, float _blue)
{
    red = _red;
    green = _green;
    blue = _blue;
}
void Net::setScale(float _s)
{ val_scale = _s; }

void Net::setangle(float _a)
{ val_angle = _a; }

void Net::setMtr(arma::fmat _M)
{ Mtr = _M; }

vector<float> Net::posInit(){ vector<float> pos = {xo, yo, zo}; return pos; }
vector<float> Net::color(){ vector<float> colorRGB = {red, green, blue}; return colorRGB; }
float Net::scale(){ return val_scale; }
float Net::angle(){ return val_angle; }
arma::fmat Net::mtr(){ return Mtr; }