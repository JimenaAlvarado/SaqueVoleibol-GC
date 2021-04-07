#include "Face.hpp"
	
Face::Face() //Constructor por defecto.
{ }

/* Crea una cara con los índices de sus vértices.
    @param _id_verts Arreglo de índices que forman una cara.
*/
Face::Face(vector<int> _id_verts){ id_verts = _id_verts; }

/*  Devuelve un arreglo dinámico con los índices de los vértices
    que forman una cara.
*/
vector<int> Face::GetVertices(){ return id_verts; }

void Face::SetNormal(arma::drowvec _NF){ this->normal = _NF; }

void Face::SetA(double value){ a = value; }
void Face::SetB(double value){ b = value; }
void Face::SetC(double value){ c = value; }
void Face::SetD(double value){ d = value; }

double Face::A(){ return a; }
double Face::B(){ return b; }
double Face::C(){ return c; }
double Face::D(){ return d; }

arma::drowvec Face::Normal(){ return normal;}


