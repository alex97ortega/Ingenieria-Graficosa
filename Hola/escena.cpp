#include "escena.h"
#include <GL/freeglut.h>
//-------------------------------------------------------------------------

void Escena::init(){
  // texturas
  // luces
}

//-------------------------------------------------------------------------
Escena::Escena() : ejes(200) {

	piramides.push_back(new PiramideTri(100, 100));
	piramides.push_back(new PiramideTri(100, 100));
	piramides.push_back(new PiramideTri(-100, -100));
	piramides.push_back(new PiramideTri(-100, -100));

}
Escena::~Escena(){
   // liberar memoria y recursos 
}

//-------------------------------------------------------------------------

void Escena::draw(){
  
  ejes.draw();
  //triangulo.draw();
  //piramide.draw();
  drawDiabolo();
}
void Escena::drawDiabolo() {
	glRotated(90.0, 1.0, 0.0, 0.0);
	glTranslated(0.0, 0.0, -100);
	piramides[0]->draw();
	
	glRotated(-180, 1.0, 0.0, 0.0);
	glTranslated(0.0, 0.0, -200);
	piramides[1]->draw();
	
	glRotated(180.0, 90.0, 0.0, 1.0);
	piramides[2]->draw();
	
	glTranslated(0.0, 0.0, -200);
	glRotated(180, 1.0, 0.0, 0.0);
	piramides[3]->draw();
}
//-------------------------------------------------------------------------
Triangulo::Triangulo(GLdouble r){


	GLdouble x = r * cos (var);
	GLdouble y = r * sin (var);



	vertices[0].set(r, 0, 0);
	vertices[1].set(x, y, 0);
	vertices[2].set(x, -y, 0);

	normales[0].set(0, 0, 1);
	normales[1].set(0, 0, 1);
	normales[2].set(0, 0, 1);

	colores[0].set(0, 0, 1);
	
}
void Triangulo::set(int n, GLdouble h) {
	Triangulo::vertices[n] = { 0, 0, h };
}
void Triangulo::draw(){
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // pa que pinta sin rellenar

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_DOUBLE, 0, vertices);
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(3, GL_DOUBLE, 0, colores);

	glLineWidth(2);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glLineWidth(1);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);


}

//-------------------------------------------------------------------------

PiramideTri::PiramideTri(GLdouble h, GLdouble r) {
	triangulos.push_back(new Triangulo(r));
	triangulos[0]->set(0, h);
	triangulos.push_back(new Triangulo(r));
	triangulos[1]->set(1, h);
	triangulos.push_back(new Triangulo(r));
	triangulos[2]->set(2, h);
}
void PiramideTri::draw(){
	for (int i = 2; i >= 0; i--) {
		triangulos[i]->draw();
	}
}



//-------------------------------------------------------------------------

Ejes::Ejes(GLdouble l) {
  vertices[0].set(0, 0, 0);
  vertices[1].set(l, 0, 0);
  vertices[2].set(0, 0, 0);
  vertices[3].set(0, l, 0);
  vertices[4].set(0, 0, 0);
  vertices[5].set(0, 0, l);

  colores[0].set(1, 0, 0);
  colores[1].set(1, 0, 0);
  colores[2].set(0, 1, 0);
  colores[3].set(0, 1, 0);
  colores[4].set(0, 0, 1);
  colores[5].set(0, 0, 1);
}

//-------------------------------------------------------------------------

void Ejes::draw(){
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_DOUBLE, 0, vertices);
  glEnableClientState(GL_COLOR_ARRAY);
  glColorPointer(3, GL_DOUBLE, 0, colores);

  glLineWidth(2);
  glDrawArrays(GL_LINES, 0, 6); 
  glLineWidth(1);

  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);

 
 /* glLineWidth(2);
  glBegin(GL_LINES);
     glColor3d(1.0, 0.0, 0.0); // red
     glVertex3d(vertices[0].x, vertices[0].y, vertices[0].z);   // origin
     glVertex3d(vertices[1].x, vertices[1].y, vertices[1].z);   // x   

     glColor3d(0.0, 1.0, 0.0); // green
     glVertex3d(vertices[2].x, vertices[2].y, vertices[2].z);   // origin
     glVertex3d(vertices[3].x, vertices[3].y, vertices[3].z);	  // y

     glColor3d(0.0, 0.0, 1.0); // blue
     glVertex3d(vertices[4].x, vertices[4].y, vertices[4].z);   // origin
     glVertex3d(vertices[5].x, vertices[5].y, vertices[5].z);	  // z   
  glEnd();
  glLineWidth(1);
  */
}




//-------------------------------------------------------------------------



