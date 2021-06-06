#include "Ball.hpp"  
#include <GLFW/glfw3.h>
	
Ball::Ball()
{
	
}

Ball::Ball(float _x, float _y, float _z, float _red, float _green, float _blue, float _scale)
{
    xo = _x; yo = _y; zo = _z;
    scale = _scale; 
    red = _red; green = _green; blue = _blue;
    vo = 5.0;
    force = 5.0; 
    angle = 90.0;
    xpeak = xo, ypeak = xo, zpeak = zo;  
    xend = 0.0; yend = 0.0; zend = 0.0;
    Object _obj("obj/ball.obj");
    obj = _obj;
    Mtr.eye(4,4);  
}

void Ball::draw()
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

void Ball::setPosInit(float _x, float _y, float _z)
{
     xo = _x; 
     yo = _y; 
     zo = _z;
}
void Ball::setPosPeak(float _x, float _y, float _z)
{  
    xpeak = _x; 
    ypeak = _y; 
    zpeak = _z; 
}

void Ball::setPosEnd(float _x, float _y, float _z)
{
     xend = _x; 
     yend = _y; 
     zend = _z;
}

void Ball::setColor(float _red, float _green, float _blue)
{
    red = _red;
    green = _green;
    blue = _blue;
}
void Ball::setScale(float _s)
{ scale = _s; }

void Ball::setvo(float _vo)
{ vo = _vo; }

void Ball::setforce(float _f)
{ force = _f; }

void Ball::setangle(float _a)
{ angle = _a; }

void Ball::setMtr(arma::fmat _M)
{ Mtr = _M; }

vector<float> Ball::getPosInit(){ vector<float> pos = {xo, yo, zo}; return pos; }
vector<float> Ball::getPosPeak(){ vector<float> pos = {xpeak, ypeak, zpeak}; return pos; }
vector<float> Ball::getPosEnd(){ vector<float> pos = {xend, yend, zend}; return pos; }
vector<float> Ball::getColor(){ vector<float> colorRGB = {red, green, blue}; return colorRGB; }
float Ball::getScale(){ return scale; }
float Ball::getvo(){ return vo; }
float Ball::getforce(){ return force; }
float Ball::getangle(){ return angle; }
arma::fmat Ball::getMtr(){ return Mtr; } 