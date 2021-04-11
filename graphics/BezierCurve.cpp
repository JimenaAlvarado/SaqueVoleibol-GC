#include "BezierCurve.hpp"
#include <iostream>
#include <math.h>

#define PI 3.14159265

using namespace std;

BezierCurve::BezierCurve() {}

/*  Crea una curva de Bezier.
    @param _yo Punto de control inicial

*/

BezierCurve::BezierCurve(float _yo, float _force, float angle, float _dt)
{
    vo = _force;
    th = angle;
    dt = _dt;
    P1 = {0.0, _yo, 0.0};
    P2 = {CalculateVox(), CalculateVoy(), CalculateVoz()};
    P4 = {CalculateMaxHorRange(), 0.0, 0.0};
    P3 = CalculateP3();

    //definir MB
    MB = {{-1, 3, -3, 1},
          {3, -6, 3, 0},
          {-3, 3, 0, 0},
          {1, 0, 0, 0}};

    //definir GB
    GB.resize(4,3);
    GB.row(0) = P1;
    GB.row(1) = P2;
    GB.row(2) = P3;
    GB.row(3) = P4;

    CreateQt();
    CalculateMaxVerRange();
    
}

arma::frowvec BezierCurve::CalculateP2()
{
    return P2 = {CalculateVox(), CalculateVoy(), CalculateVoz()};;
}

arma::frowvec BezierCurve::CalculateP3(){
    arma::frowvec dQ = {P4[0], P4[1], P4[2]};
    float magnitudedQ = sqrt( pow(P4[0], 2) + pow(P4[1], 2) + pow(P4[2], 2) );
    P3 = {dQ[0]/magnitudedQ, dQ[1]/magnitudedQ, dQ[2]/magnitudedQ};
    return P3;
}

void BezierCurve::CreateQt()
{
    //La función Q(t) son segmentos de curva con los valores x(t),y(t),z(t)
    //Q(t) representa los polinomios cúbicos que definen los segmentos de curva.
    for (float t = 0.0; t <= 1.0 + dt; t += dt)
    {
        //definir el vector T
        arma::frowvec T = {powf(t, 3), powf(t, 2), t, 1};

        /* Curvas de Bezier */
        Qt = T * MB * GB;
        cout << "t: " << t << " " << Qt << endl;
    }
}

float BezierCurve::CalculateVox(){
    return vox = vo * cos( th * PI / 180.0 );
}

float BezierCurve::CalculateVoy(){
    return voy = vo * sin( th * PI / 180.0 );
}

float BezierCurve::CalculateVoz(){
    return voz = 0.0;
}

float BezierCurve::CalculateMaxHorRange()
{
    return xmax = ( pow(vo, 2.0) * sin( (2 * th) * PI / 180) ) / G;
}

float BezierCurve::CalculateMaxVerRange()
{
    return ymax = ( ( pow(vo, 2.0) * pow(sin(th * PI / 180.0), 2.0)) / (2 * G) ) + P1[1];
  //return pow(-voy, 2.0) / (-2*G);
}

float BezierCurve::CalculateTimeRisePeak()
{
    return ts = ( vo * sin( th * PI / 180.0) ) / G;
}

float BezierCurve::CalculateTotalTime()
{
    return tt = 2 * ts;
}

arma::frowvec BezierCurve::GetP1(){ return P1; }
arma::frowvec BezierCurve::GetP2(){ return P2; }
arma::frowvec BezierCurve::GetP3(){ return P3; }
arma::frowvec BezierCurve::GetP4(){ return P4; }
float BezierCurve::Getvo(){ return vo; }
float BezierCurve::Getdt(){ return dt; }
float BezierCurve::Getth(){ return th; }
float BezierCurve::Getvox(){ return vox; }
float BezierCurve::Getvoy(){ return voy; }
float BezierCurve::Getvoz(){ return voz; }
float BezierCurve::Getts(){ return ts; }
float BezierCurve::Gettt(){ return tt; }
float BezierCurve::Getymax(){ return ymax; }
float BezierCurve::Getxmax(){ return xmax; }
		