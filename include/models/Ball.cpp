#include "Ball.hpp"  
#include <GLFW/glfw3.h>
	
Ball::Ball()
{
	
}

Ball::Ball(float _x, float _y, float _z, float _red, float _green, float _blue, float _scale)
{
    xo = _x; yo = _y; zo = _z;
    val_scale = _scale; 
    red = _red; green = _green; blue = _blue;
    vo = 5.0;
    val_force = 5.0; 
    val_angle = 90.0;
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
{ val_scale = _s; }

void Ball::setvo(float _vo)
{ vo = _vo; }

void Ball::setforce(float _f)
{ val_force = _f; }

void Ball::setangle(float _a)
{ val_angle = _a; }

void Ball::setMtr(arma::fmat _M)
{ Mtr = _M; }

vector<float> Ball::posInit(){ vector<float> pos = {xo, yo, zo}; return pos; }
vector<float> Ball::posPeak(){ vector<float> pos = {xpeak, ypeak, zpeak}; return pos; }
vector<float> Ball::posEnd(){ vector<float> pos = {xend, yend, zend}; return pos; }
vector<float> Ball::color(){ vector<float> colorRGB = {red, green, blue}; return colorRGB; }
float Ball::scale(){ return val_scale; }
float Ball::initVelocity(){ return vo; }
float Ball::force(){ return val_force; }
float Ball::angle(){ return val_angle; }
arma::fmat Ball::mtr(){ return Mtr; } 