#ifndef OBJECT_H
#define OBJECT_H
#pragma once

#include <string>
#include <vector>
#include <armadillo>
#include "Vertex.hpp"
#include "Face.hpp"

using namespace std;

class Object  
{
	private:
		vector<Vertex> verts;
		vector<Face> faces;
		string name;

		vector<string> Split(const string& str, const string& delim);
		Vertex CreateVertex(vector<string> tokens);
		vector<int> ExtractIndexes(vector<string> tokens, int pos);
		
	public:
		Object();
		Object(string filename);
		vector<Vertex> GetVerts();
		vector<Face> GetFaces();
		string GetName();
		void Print();
		arma::frowvec CalculateNormal(Face _face);
		void CalculateAllNormals();
		void EquationPlane(Face &_face);
		void PrintNormals();
		void PrintEquationsOfPlane();

};
#endif