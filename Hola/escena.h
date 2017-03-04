//#pragma once
#ifndef _H_escena_H_
#define _H_escena_H_
#include "tipos.h"
#include <vector>
//-------------------------------------------------------------------------
class Ejes {
public:
  Ejes(GLdouble l);
  ~Ejes(){};
  void draw();
public:
  PVec3 vertices[6];
  PVec3 colores[6];
};

//-------------------------------------------------------------------------
class Triangulo {
public:
	Triangulo(GLdouble l);
	~Triangulo(){};
	void draw(); // por ultimo dibujar los ejes desde el punto creado tope de molongui
	void set(int n, GLdouble h);
public:
	GLdouble var = (2 * 3.14) / 3; // rotar lo que nos diga este numero xdddd
	PVec3 vertices[3];
	PVec3 normales[3];
	PVec3 colores[1];
};

//-------------------------------------------------------------------------

class PiramideTri{
public:
	PiramideTri(GLdouble h, GLdouble radio);
	~PiramideTri(){};
	void draw();
public:
	
	std::vector<Triangulo*> triangulos;

};



//-------------------------------------------------------------------------

class Escena {
public:
  Escena();
  ~Escena();
  void init();
  void draw();
  void drawDiabolo();
public:
  Ejes ejes;
 // Triangulo triangulo;
 // PiramideTri piramide;
  std::vector<PiramideTri*> piramides;
};

//-------------------------------------------------------------------------


#endif  // _H_escena_H_
