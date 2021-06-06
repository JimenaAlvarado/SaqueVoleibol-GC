#include "Hand.hpp"  
#include <GLFW/glfw3.h>
	
Hand::Hand()
{
	
}
	
Hand::Hand(float _x, float _y, float _z, float _red, float _green, float _blue, float _scale)
{
    xo = _x; yo = _y; zo = _z;
    val_scale = _scale; 
    red = _red; green = _green; blue = _blue;
    val_angle = -90.0;
    Object _obj("obj/hand.obj");
    obj = _obj;
    Mtr.eye(4,4);  
}

void Hand::draw()
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

void Hand::setPosInit(float _x, float _y, float _z)
{
     xo = _x; 
     yo = _y; 
     zo = _z;
}

void Hand::setColor(float _red, float _green, float _blue)
{
    red = _red;
    green = _green;
    blue = _blue;
}
void Hand::setScale(float _s)
{ val_scale = _s; }

void Hand::setangle(float _a)
{ val_angle = _a; }

void Hand::setMtr(arma::fmat _M)
{ Mtr = _M; }

vector<float> Hand::posInit(){ vector<float> pos = {xo, yo, zo}; return pos; }
vector<float> Hand::color(){ vector<float> colorRGB = {red, green, blue}; return colorRGB; }
float Hand::scale(){ return val_scale; }
float Hand::angle(){ return val_angle; }
arma::fmat Hand::mtr(){ return Mtr; } 