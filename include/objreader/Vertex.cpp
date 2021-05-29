#include "Vertex.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

/*  Constructor por defecto. */
Vertex::Vertex()
{
    x = y = z = 0.0;
    id = -1;
}

/*  Punto en el espacio definido por las coordenadas (x,y,z).
    @param _x Coordenada en el eje x.
    @param _y Coordenada en el eje y.
*/
Vertex::Vertex(float _x, float _y, float _z)
{
    x = _x;
    y = _y;
    z = _z;
    id = -1;
}

/*  Imprime las coordenada x, y, z.*/
void Vertex::Print()
{
    cout << x << " " << y << " " << z << endl;
}

/* Imprime el índice del vértice. */
void Vertex::PrintId()
{
    cout << id << " ";
}

/*  Asigna un índice al vértice. */
void Vertex::SetId(int _id) { id = _id; }

/*  Devuelve el índice del vértice. */
int Vertex::GetId() { return id; }

/*  Asigna un valor a la componente 'x' del vértice. */
void Vertex::SetX(float _x) { x = _x; }

/* Devuelve el valor de la componente 'x' del vértice. */
float Vertex::X() { return x; }

/*  Asigna un valor a la componente 'y' del vértice. */
void Vertex::SetY(float _y) { y = _y; }

/* Devuelve el valor de la componente 'y' del vértice. */
float Vertex::Y() { return y; }

/*  Asigna un valor a la componente 'z' del vértice. */
void Vertex::SetZ(float _z) { z = _z; }

/* Devuelve el valor de la componente 'z' del vértice. */
float Vertex::Z() { return z; }

/*  Comparar con un vértice.
    @param _v Vértice contra el cual se compara.
    @return True si son iguales.
*/
bool Vertex::CompareTo(Vertex _v)
{
    bool value = false;

    if (x == _v.X() && y == _v.Y() && z == _v.Z())
        value = true;

    return value;
}

/* Devuelve un vértice de coordenadas homogéneas */
arma::fcolvec Vertex::Homog()
{
    arma::fcolvec h = {this->x, this->y, this->z, 1};
    return h;
}