#ifndef BALL_H
#define BALL_H
#pragma once

#include "../objreader/Object.hpp"
#include <armadillo>
#include <vector>

using namespace std;
	
class Ball  
{
	private:
		float xo, yo, zo; // Posición inicial
		float val_scale; //	Valor de escalamiento
		float red, green, blue; // Color
		float vo; // Velocidad inicial
		float val_force; // Fuerza
		float val_angle; // Ángulo de rotación
		float xpeak, ypeak, zpeak;  // Punto más alto que alcanza
		float xend, yend, zend;  // Alcance máximo horizontal
		Object obj; // Modelo 3D
		arma::fmat Mtr; // Matriz de transformación


	public:

		Ball();
		Ball(float _x, float _y, float _z, float _red, float _green, float _blue, float _scale = 1);
		void draw();
		void setPosInit(float _x, float _y, float _z);
		void setPosPeak(float _x, float _y, float _z);
		void setPosEnd(float _x, float _y, float _z);
		void setColor(float _red, float _green, float _blue);
		void setScale(float _s);
		void setvo(float _vo);
		void setforce(float _f);
		void setangle(float _a);
		void setMtr(arma::fmat _M);
		vector<float> posInit();
		vector<float> posPeak();
		vector<float> posEnd();
		vector<float> color();
		float scale();
		float initVelocity();
		float force();
		float angle();
		arma::fmat mtr();
};
#endif