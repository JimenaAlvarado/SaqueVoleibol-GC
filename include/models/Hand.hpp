#ifndef HAND_H
#define HAND_H
#pragma once

#include <armadillo>
#include <vector>
#include "../objreader/Object.hpp"

using namespace std;
	
class Hand  
{
	private:
		float xo, yo, zo; // Posición inicial
		float val_scale; //	Valor de escalamiento
		float red, green, blue; // Color
		float val_angle; // Ángulo de rotación
		Object obj; // Modelo 3D
		arma::fmat Mtr; // Matriz de transformación


	public:

		Hand();
		Hand(float _x, float _y, float _z, float _red, float _green, float _blue, float _scale = 1);
		void draw();
		void setPosInit(float _x, float _y, float _z);
		void setColor(float _red, float _green, float _blue);
		void setScale(float _s);
		void setangle(float _a);
		void setMtr(arma::fmat _M);
		vector<float> posInit();
		vector<float> color();
		float scale();
		float angle();
		arma::fmat mtr();

};
#endif