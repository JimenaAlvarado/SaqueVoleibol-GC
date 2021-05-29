#ifndef TRAJECTORY_H
#define TRAJECTORY_H
#pragma once
	
#include <armadillo>
#include <vector>
#include "../objreader/Vertex.hpp"

using namespace std;
	
class Trajectory  
{
	private:

	public:

		Trajectory();
		~Trajectory();
		vector<Vertex> lineal(Vertex init, Vertex end, float dt);
		vector<Vertex> curve(Vertex p1, Vertex p2, Vertex p3, Vertex p4, float dt);
};
#endif