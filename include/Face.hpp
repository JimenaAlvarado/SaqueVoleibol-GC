#ifndef FACE_H
#define FACE_H
#pragma once

#include <vector>
#include <armadillo>
#include "Vertex.hpp"

using namespace std;
	
class Face  
{
	private:
		double a, b, c, d; //Componentes de la ecuación del plano
		vector<int> id_verts; //Índices de vértices que forman una cara.
		vector<Vertex> verts; //Vértices que forman una cara
		arma::drowvec normal; //Vector normal al plano

	public:
		Face();
		Face(vector<int> _id_verts);
		Face(vector<Vertex> _verts);
		vector<int> GetIdVertices();
		vector<Vertex> GetVertices();	
		void SetNormal(arma::drowvec _NF);
		void SetA(double value);
		void SetB(double value);
		void SetC(double value);
		void SetD(double value);
		double A();
		double B();
		double C();
		double D();
		arma::drowvec GetNormal();
		arma::drowvec Normal();
		void EquationOfPlane();
		void PrintEquationOfPlane();
		
};
#endif