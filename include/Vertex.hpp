#ifndef VERTEX_H
#define VERTEX_H
#pragma once
	
class Vertex  
{
	private:
		double x, y, z;
		int id;
	public:
		Vertex();
		Vertex(double _x, double _y, double _z);
		void Print();
		void PrintId();
		void SetId( int _id);
		int GetId();
		void SetX(double _x);
		double X();
		void SetY(double _y);
		double Y();
		void SetZ(double _z);
		double Z();
		bool CompareTo(Vertex _v);
};
#endif