#include "Transformation.hpp"  
#define PI 3.14159265 

Transformation::Transformation()
{
	
}

arma::fmat Transformation::T(float _dx, float _dy, float _dz)
{
    arma::fmat Tt = {{1, 0, 0, _dx},
                     {0, 1, 0, _dy},
                     {0, 0, 1, _dz},
                     {0, 0, 0, 1}};
    return Tt;
}

arma::fmat Transformation::S(float _sx, float _sy, float _sz)
{
    arma::fmat St = {{_sx, 0, 0, 0},
                     {0, _sy, 0, 0},
                     {0, 0, _sz, 0},
                     {0, 0, 0, 1}};
    return St;
}

arma::fmat Transformation::Rx(float _theta)
{
    float theta = _theta * PI / 180;
    arma::fmat Rx = {{1, 0, 0, 0},
                     {0, cosf(theta), -sinf(theta), 0},
                     {0, sinf(theta), cosf(theta), 0},
                     {0, 0, 0, 1}};
    return Rx;
}

arma::fmat Transformation::Ry(float _theta)
{
    float theta = _theta * PI / 180;
    arma::fmat Ry = {{cosf(theta), 0, sinf(theta), 0},
                      {0, 1, 0, 0},
                      {-sinf(theta), 0, cosf(theta), 0},
                      {0, 0, 0, 1}}; 
    return Ry;
}

arma::fmat Transformation::Rz(float _theta)
{
    float theta = _theta * PI / 180;
    arma::fmat Rz = {{cosf(theta), -sinf(theta), 0, 0},
                      {sinf(theta), cosf(theta), 0, 0},
                      {0, 0, 1, 0},
                      {0, 0, 0, 1}}; 
    return Rz;
}

arma::fmat Transformation::Rp1p2(Vertex P1, Vertex P2, float theta)
{
     /* Para llevar al eje z positivo */
    //Paso 1 
    arma::fmat T = {{1, 0, 0, -P1.X()},
                    {0, 1, 0, -P1.Y()},
                    {0, 0, 1, -P1.Z()},
                    {0, 0, 0, 1}};
    

    //Paso 2
    float D1 = sqrt(powf(P2.X()-P1.X(),2) + powf(P2.Z()-P1.Z(),2));

    arma::fmat Ry = {{(P2.Z()-P1.Z())/D1, 0, -(P2.X()-P1.X())/D1, 0},
                     {0, 1, 0, 0},
                     {(P2.X()-P1.X())/D1, 0, (P2.Z()-P1.Z())/D1, 0},
                     {0, 0, 0, 1}};

    //Paso 3
    float D2 = sqrt(powf(P2.X()-P1.X(),2) + powf(P2.Y()-P1.Y(),2) + powf(P2.Z()-P1.Z(),2));
   
    arma::fmat Rx = {{1, 0, 0, 0},
                     {0, D1/D2, -(P2.Y()-P1.Y())/D2, 0},
                     {0, (P2.Y()-P1.Y())/D2, D1/D2, 0},
                     {0, 0, 0, 1}};



    //Rz
    Transformation tr;
    arma::fmat Rz_tr = tr.Rz(theta);

    //Regresar al punto original
    //Paso 4 : Rx(-ang2)
    arma::fmat Rxi = Rx.i();
    
    //Paso 5 : Ry(-(90-ang))
    arma::fmat Ryi = Ry.i();

    //Paso 6 : T(x1, y1, -z1)
    arma::fmat Ti = T.i();

    //Se obtiene la matriz compuesta:
    arma::fmat MC = Ti * Ryi * Rxi * Rx * Ry * T; 

    return MC;

}