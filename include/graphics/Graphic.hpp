#ifndef GRAPHIC_H
#define GRAPHIC_H
#pragma once

#include <GLFW/glfw3.h>
#include <armadillo>
#include "../objreader/Object.hpp"

class Graphic  
{
	private:
		GLFWwindow* window; 
		float yo = -0.5;

	public:

		Graphic();
		int newWindow(int _width, int _height, float _red, float _green, float _blue, float _alpha);
		void openWindow();
		void drawObject(Object _obj, arma::fmat _Mtr, float _red, float _green, float _blue);
		float getyo();
};
#endif