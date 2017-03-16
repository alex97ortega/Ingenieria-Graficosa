//#pragma once
#ifndef _H_escena_H_
#define _H_escena_H_
#include "tipos.h"
#include <vector>
#include "Textura.h"
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
	Triangulo(GLdouble r);
	~Triangulo(){};
	void draw(); // por ultimo dibujar los ejes desde el punto creado tope de molongui
	void set(int n, GLdouble h);
public:
	GLdouble var = (2 * 3.14) / 3; // rotar lo que nos diga este numero xdddd
	PVec3 vertices[3];
	PVec3 normales[1];
	PVec3 colores[1];
};


//-------------------------------------------------------------------------

class TriAnimado {
public:
	TriAnimado(GLdouble rd, GLdouble tr, GLdouble rot);
	~TriAnimado(){};
	void draw();
	void update();

public:

	Triangulo tri;

	GLdouble radio;
	GLdouble rotacion;
	GLdouble trans;


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

class Rectangulo{
public :
	Rectangulo(GLdouble altoc, GLdouble anchoc);
	~Rectangulo(){};
	void draw();
	void set(GLdouble &anchop, GLdouble &altop);

public :
	GLdouble alto;
	GLdouble ancho;
	PVec3 vertices[4];
	PVec3 ptext[4];
	PVec3 normal;
	PVec3 color;

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
	std::vector<PiramideTri*> piramides;

	Textura textura;
	Rectangulo recTex;
};

//-------------------------------------------------------------------------


#endif  // _H_escena_H_
