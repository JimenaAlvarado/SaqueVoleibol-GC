#ifndef VERTEX_H
#define VERTEX_H
#pragma once

#include <armadillo>

class Vertex  
{
	private:
		float x, y, z;
		int id;
	public:
		Vertex();
		Vertex (float _x, float _y, float _z);
		void Print();
		void PrintId();
		void SetId( int _id);
		int GetId();
		void SetX(float _x);
		float X();
		void SetY(float _y);
		float Y();
		void SetZ(float _z);
		float Z();
		bool CompareTo(Vertex _v);
		arma::fcolvec Homog();
};
#endif