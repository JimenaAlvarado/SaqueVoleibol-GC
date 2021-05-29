#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H
#pragma once
	
#include <armadillo>
#include "../objreader/Vertex.hpp"

class Transformation  
{
	private:

	public:

		Transformation();
		arma::fmat T(float _dx, float _dy, float _dz);
		arma::fmat S(float _sx, float _sy, float _sz);
		arma::fmat Rx(float _theta);
		arma::fmat Ry(float _theta);
		arma::fmat Rz(float _theta);

		arma::fmat Rp1p2(Vertex P1, Vertex P2, float theta);


};
#endif