#include "Face.hpp"
	
Face::Face() //Constructor por defecto.
{ }

/* Crea una cara con los índices de sus vértices.
    @param _id_verts Arreglo de índices que forman una cara.
*/
Face::Face(vector<int> _id_verts){  id_verts = _id_verts; }

/* Crea una cara (plano).
    @param _verts Arreglo de vértices que forman esta cara.
*/
Face::Face(vector<Vertex> _verts)
{  
    verts = _verts; 
    normal = Normal();
    EquationOfPlane();

}

/*  Devuelve un vector con los índices de los vértices
    que forman una cara.
*/
vector<int> Face::GetIdVertices(){ return id_verts; }

/*  Devuelve un vector con los vértices que forman una cara.  */
vector<Vertex> Face::GetVertices(){ return verts; }

void Face::SetNormal(arma::frowvec _NF){ this->normal = _NF; }

void Face::SetA(float value){ a = value; }
void Face::SetB(float value){ b = value; }
void Face::SetC(float value){ c = value; }
void Face::SetD(float value){ d = value; }

float Face::A(){ return a; }
float Face::B(){ return b; }
float Face::C(){ return c; }
float Face::D(){ return d; }

/*  Devuelve el vector normal al plano  */
arma::frowvec Face::GetNormal(){ return normal; }

/*  Calcular el vector normal al plano  */
arma::frowvec Face::Normal()
{
    vector<arma::frowvec> auxverts;
    arma::frowvec NF;

    //Convertir cada vértice a un objeto vectorial
    for (Vertex v : verts)
    {
        arma::frowvec vertex = {v.X(), v.Y(), v.Z()};
        auxverts.push_back(vertex);
    }

    //Producto cruz
    NF = arma::cross(auxverts[1] - auxverts[0], auxverts[2] - auxverts[0]);

    return NF;
}

/*  Obtiene el valor de los coeficientes A,B,C de la ecuación del plano. */
void Face::EquationOfPlane()
{
    a = normal[0];
    b = normal[1];
    c = normal[2];

    d = -(A() * verts[0].X() +
          B() * verts[0].Y() +
          C() * verts[0].Z());
}

/*  Imprime la ecuación del plano.  */
void Face::PrintEquationOfPlane()
{
    cout << A() << "x + " << B() << "y + " << C() << "z + " << D() << " = 0" << endl;
}




