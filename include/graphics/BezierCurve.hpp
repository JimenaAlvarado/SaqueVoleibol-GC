#ifndef CURVASBEZIER_H
#define CURVASBEZIER_H
#pragma once

#include <armadillo>
#include <vector>
#include "../objreader/Vertex.hpp"

using namespace std;

const float G = 9.81; //aceleración
	
class BezierCurve 
{
	private:
		/* Puntos de control */
		arma::frowvec P1;	//Punto inicial. Posición (x,y,z) - Punto inicial
		arma::frowvec P2;   //Punto de la tangente. Posición (x,y,z) - Punto inicial
		arma::frowvec P3;   //Punto de la tangente. Posición (x,y,z) - Punto final
		arma::frowvec P4; 	// Punto final.
		arma::fmat MB;		//Matriz base de Bezier
		arma::fmat GB; 		//Vector de geometría de Bezier
		vector<arma::frowvec> curve;	//Vector de polinomios cúbicos que definen los segmentos de curva.
		float vo; 			//Fuerza inicial
		float dt;			//Paso en el parametro t 
		float theta;			//Ángulo theta del vector P1P2 con respecto a la horizontal
		float vox, voy, voz;		//Componentes del vector tangente a P1 (Fuerza)
		float ts; 			//Tiempo de subida
		float tt; 			//Tiempo total
		float ymax;  //Alcance máximo vertical
		float xmax;  //Alcance máximo horizontal	

		arma::frowvec CalculateP2();
		arma::frowvec CalculateP3();
		void CreateQt();
		float CalculateVox();
		float CalculateVoy();
		float CalculateVoz();
		float CalculateMaxHorRange();
		float CalculateMaxVerRange();
		float CalculateTimeRisePeak();
		float CalculateTotalTime();
		

	public:

		BezierCurve();
		BezierCurve(float _yo, float _force, float angle, float _dt);
		BezierCurve(Vertex _p1, Vertex _p2, Vertex _p3, Vertex _p4, float _dt);
		arma::frowvec GetP1();
		arma::frowvec GetP2();
		arma::frowvec GetP3();
		arma::frowvec GetP4();
		float Getvo();
		float Getdt();
		float Getth();
		float Getvox();
		float Getvoy();
		float Getvoz();
		float Getts();
		float Gettt();
		float Getymax();
		float Getxmax();
		vector<arma::frowvec> GetCurve();

};
#endif