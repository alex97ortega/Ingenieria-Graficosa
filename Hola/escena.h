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
	void draw(); 
	void set(int n, GLdouble h);


	bool dentro(GLdouble x, GLdouble y);
	void posicionar(GLdouble x, GLdouble y);
	void rotar();
	void recortar(int ancho, int alto, PVec3 vt[3]);
	void setAnimar();
	void cambio();
	

public:
	GLdouble var = (2 * 3.14) / 3; 
	PVec3 vertices[3];
	PVec3 normales[3];
	Color4 colores;

	GLdouble x;
	GLdouble y;


	CTex2 texttri[3];

	//Textura textura;

	GLdouble rotacion;
	GLdouble radio;
	PVec3 centro;

	bool slinea = true;
};


//-------------------------------------------------------------------------

class TriAnimado {
public:
	TriAnimado(GLdouble rd, GLdouble tr, GLdouble rot);
	~TriAnimado(){};
	void draw();
	void update();

public:

	GLdouble posx;
	GLdouble posy;

	Triangulo tri;

	GLdouble radio;
	GLdouble rotacion;
	GLdouble trans;


	CTex2 texttri[3];

};

//-------------------------------------------------------------------------

class PiramideTri{
public:
	PiramideTri(GLdouble h, GLdouble radio);
	~PiramideTri(){};
	void draw();
	void añadirText(CTex2 coor[3]);
public:

	std::vector<Triangulo*> triangulos;

};


//-------------------------------------------------------------------------

class Rectangulo{
public :
	Rectangulo(GLdouble altoc, GLdouble anchoc);
	~Rectangulo(){};
	void draw();
	void set(GLdouble anchop, GLdouble altop);

public :
	
	PVec3 vertices[4];
	CTex2 vtext[4];
	PVec3 normal;
	Color4 color;
	Textura textura;

};



//-------------------------------------------------------------------------

class Escena {
public:
	Escena();
	~Escena();
	void init();
	void draw();
	void drawDiabolo();
	void capturar(int ancho, int alto);

public:
	Ejes ejes;

	Triangulo t;
	TriAnimado tri;

	std::vector<PiramideTri*> piramides;

	Rectangulo rect, rect2, rect3, rect4;
	GLdouble rotacion;


};

//-------------------------------------------------------------------------


#endif  // _H_escena_H_
