//#pragma once
#ifndef _H_escena_H_
#define _H_escena_H_
#include "tipos.h"

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
	
	Triangulo  t1;
	Triangulo  t2;
	Triangulo t3;
	void altura(GLdouble h, Triangulo &t, int i);

};


//-------------------------------------------------------------------------

class Escena {
public:
  Escena(): ejes(200), triangulo(128) , piramide(200, 50){};
  ~Escena();
  void init();
  void draw();
public:
  Ejes ejes;
  Triangulo triangulo;
  PiramideTri piramide;
};

//-------------------------------------------------------------------------


#endif  // _H_escena_H_
