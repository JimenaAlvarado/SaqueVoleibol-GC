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
		float a, b, c, d; 	//Componentes de la ecuación del plano
		vector<int> id_verts; //Índices de vértices que forman una cara.
		vector<Vertex> verts; //Vértices que forman una cara
		arma::frowvec normal; //Vector normal al plano
		
	public:
		Face();
		Face(vector<int> _id_verts);
		Face(vector<Vertex> _verts);
		vector<int> GetIdVertices();
		vector<Vertex> GetVertices();	
		void SetNormal(arma::frowvec _NF);
		void SetA(float value);
		void SetB(float value);
		void SetC(float value);
		void SetD(float value);
		float A();
		float B();
		float C();
		float D();
		arma::frowvec GetNormal();
		arma::frowvec Normal();
		void EquationOfPlane();
		void PrintEquationOfPlane();
		
};
#endif