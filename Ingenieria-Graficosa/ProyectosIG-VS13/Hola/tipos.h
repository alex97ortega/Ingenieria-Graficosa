//#pragma once
#ifndef _H_tipos_H_
#define _H_tipos_H_

#include <GL/freeglut.h>
#include <cmath>

//-------------------------------------------------------------------------

class PVec3 {
public:
  PVec3(GLdouble ax = 0.0, GLdouble ay = 0.0, GLdouble az = 0.0) : x(ax), y(ay), z(az) {};
  ~PVec3() {};
  void set(GLdouble px, GLdouble py, GLdouble pz){ x = px; y = py; z = pz; };
  void add(PVec3 v){ x = x + v.x; y = y + v.y; z = z + v.z; };
  void dot(GLdouble e){ x = x*e; y = y*e; z = z*e; };
  GLdouble dot(PVec3 v){ return x*v.x + y*v.y + z*v.z; }; //  para calcular el coseno del ángulo (= 0 -> perpendiculares)
  PVec3 cross(PVec3 v){ return PVec3(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x); }; // para calcular el vector normal (perpendicular)
  void normalize(){ GLdouble M = magnitude(); x = x / M; y = y / M; z = z / M; };
  GLdouble magnitude(){ return sqrt(x*x + y*y + z*z); };
public:
  GLdouble x, y, z;
};

//-------------------------------------------------------------------------

class Camara {
public:
  Camara(GLdouble aw, GLdouble ah) :eye(0.0, 0.0, 500.0), look(0.0, 0.0, 0.0), up(0.0, 1.0, 0.0),
                                    xRight(aw / 2.0), xLeft(-xRight), yTop(ah / 2.0), yBot(-yTop), nearVal(1), farVal(1000) {};
  ~Camara() {};

  void setPos(PVec3 ay, PVec3 al, PVec3 ap);
  void setPos();

  void setVV(GLdouble aw, GLdouble ah);
  void setVV();
  void setVV(GLdouble xL, GLdouble xR, GLdouble yT, GLdouble yB, GLdouble nV, GLdouble fV) { nearVal = nV; farVal = fV; setVV(xL, xR, yT, yB, nV, fV); };

  void setEZ();
  void set3D();
public:
  PVec3 eye, look, up;
  GLdouble xRight, xLeft, yTop, yBot, nearVal, farVal;
};

//-------------------------------------------------------------------------

class PuertoVista {
public:
  PuertoVista(GLuint ax, GLuint ay, GLsizei aw, GLsizei ah) : x(ax), y(ay), w(aw), h(ah) {};
  ~PuertoVista() {};
  void set(GLuint ax, GLuint ay, GLsizei aw, GLsizei ah){ x = ax; y = ay; w = aw; h = ah; set(); };
  void set();
public:
  GLint x, y;
  GLsizei w, h;
};

//-------------------------------------------------------------------------

#endif //_H_tipos_H_