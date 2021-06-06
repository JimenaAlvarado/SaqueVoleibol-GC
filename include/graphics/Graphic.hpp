#ifndef GRAPHIC_H
#define GRAPHIC_H
#pragma once

#include <GLFW/glfw3.h>
#include <armadillo>
#include <vector>
#include "../objreader/Object.hpp"

class Graphic  
{
	private:
		GLFWwindow* window; 
		float yo = -0.5;
		int index_curve = 0;
		int keyenter_press = 0;

	public:

		Graphic();
		int newWindow(int _width, int _height, float _red, float _green, float _blue, float _alpha);
		void openWindow();
		float getyo();
		void reset();
};
#endif