#include "tipos.h"

//-------------------------------------------------------------------------

void PuertoVista::set() {
  glViewport(x, y, w, h); 
}

//-------------------------------------------------------------------------

void Camara::setEZ() {
  eye.set(0, 0, 500);
  look.set(0, 0, 0);
  up.set(0, 1, 0);
  setPos();
}

//-------------------------------------------------------------------------

void Camara::set3D() {
  eye.set(500, 500, 500);
  look.set(0, 10, 0);
  up.set(0, 1, 0);
  setPos();
}

//-------------------------------------------------------------------------

void Camara::setPos(PVec3 ay, PVec3 al, PVec3 ap){
  eye = ay;
  look = al;
  up = ap;
  setPos();
}

//-------------------------------------------------------------------------

void Camara::setPos() {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();    
  gluLookAt(eye.x, eye.y, eye.z, look.x, look.y, look.z, up.x, up.y, up.z);  // eye, look, up
}

//-------------------------------------------------------------------------

void Camara::setVV(GLdouble aw, GLdouble ah) {
  xRight = aw / 2.0;
  xLeft = -xRight;
  yTop = ah / 2.0;
  yBot = -yTop;
  setVV();
}

//-------------------------------------------------------------------------

void Camara::setVV() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(xLeft, xRight, yBot, yTop, nearVal, farVal);
}

//-------------------------------------------------------------------------

