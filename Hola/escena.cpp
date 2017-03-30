#include "escena.h"
#include <GL/freeglut.h>
//-------------------------------------------------------------------------

void Escena::init(){

	glEnable(GL_TEXTURE_2D);
	rect.textura.init();
	rect2.textura.init();
	rect3.textura.init();
	//piramides[0]->triangulos[0]->textura.init();
	//piramides[0]->triangulos[0]->textura.load("../bmps/Zelda.bmp");

}

//-------------------------------------------------------------------------
Escena::Escena() : ejes(200), rect(600, 800), rect2(200, 400), rect3(50, 80), rect4 (1,1), tri(100, 0, 0), t(100) {

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
	//drawDiabolo();

	rect.textura.load("../bmps/Zelda.bmp");
	rect.draw();
	rect2.textura.load("../bmps/ray.bmp");
	rect2.draw();
	rect3.textura.load("../bmps/earth24.bmp", 1);
	rect3.draw();
}
void Escena::drawDiabolo() {
	glRotated(rotacion, 1.0, 0.0, 0.0);
	glRotated(90.0, 1.0, 0.0, 0.0);
	glTranslated(0.0, 0.0, -100);
	piramides[0]->draw();

	glRotated(180, 1.0, 0.0, 0.0);
	piramides[3]->draw();


	glTranslated(1.0, 0.0, -200);
	piramides[1]->draw();

	glRotated(180.0, 90.0, 0.0, 1.0);
	piramides[2]->draw();

	glRotated(-90.0, -90.0, 0.0, -1.0);
	glTranslated(0.0, -100.0, 0);

	glRotated(-rotacion, 1.0, 0.0, 0.0);
}


//-------------------------------------------------------------------------

Triangulo::Triangulo(GLdouble r){

	x = r * cos(var);
	y = r * sin(var);

	vertices[0].set(r, 0, 0);
	vertices[1].set(x, y, 0);
	vertices[2].set(x, -y, 0);

	normales[0].set(0, 0, 1);
	normales[1].set(0, 0, 1);
	normales[2].set(0, 0, 1);
	
	colores.a = 0;
	colores.b = 0;
	colores.g = 0;
	colores.r = 0;

	
	texttri[0].s = 0;
	texttri[0].t = 0;
	texttri[1].s = 0;
	texttri[1].t = 0;
	texttri[2].s = 0;
	texttri[2].t = 0;
	
	radio = r;

}


void Triangulo::set(int n, GLdouble h) {
	vertices[n] = { 0, 0, h };
}

void Triangulo::cambio(){
	slinea = false;
}

void Triangulo::draw(){

	if (slinea){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else 
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_TEXTURE_2D);

	glVertexPointer(3, GL_DOUBLE, 0, vertices);

	glTexCoordPointer(2, GL_DOUBLE, 0, texttri);

	glNormal3d(normales[0].x, normales[0].y, normales[0].z);

	glColor4d(colores.r, colores.g, colores.b, colores.a);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_TEXTURE_2D);
}

bool Triangulo::dentro(GLdouble x, GLdouble y){
	if (((vertices[0].x - x) * (vertices[1].y - y)) - ((vertices[0].y - y) * (vertices[1].x - x)) < 0){
		return false;
	}

	else if (((vertices[1].x - x) * (vertices[2].y - y)) - ((vertices[1].y - y) * (vertices[2].x - x)) < 0){
		return false;
	}

	else if (((vertices[2].x - x) * (vertices[0].y - y)) - ((vertices[2].y - y) * (vertices[0].x - x)) < 0){
		return false;
	}
	else return true;
}



void  Triangulo::posicionar(GLdouble x, GLdouble y){

	centro = { x, y, 0 }; 
	vertices[0] = { radio*cos(rotacion) + centro.x, radio * sin(rotacion) + centro.y, 0 };
	vertices[1] = { radio*cos(rotacion + 2.0 * 3.14 / 3.0) + centro.x, radio * sin(rotacion + 2.0 * 3.14 / 3.0) + centro.y, 0 };
	vertices[2] = { radio*cos(rotacion + 4.0 * 3.14 / 3.0) + centro.x, radio * sin(rotacion + 4.0 * 3.14 / 3.0) + centro.y, 0 };
	
}


void Triangulo::rotar(){
	rotacion += 0.1;
	vertices[0] = { radio*cos(rotacion) + centro.x, radio * sin(rotacion) + centro.y, 0 };
	vertices[1] = { radio*cos(rotacion + 2.0 * 3.14 / 3.0) + centro.x, radio * sin(rotacion + 2.0 * 3.14 / 3.0) + centro.y, 0 };
	vertices[2] = { radio*cos(rotacion + 4.0 * 3.14 / 3.0) + centro.x, radio * sin(rotacion + 4.0 * 3.14 / 3.0) + centro.y, 0 };
}


void  Triangulo::recortar(int ancho, int alto, PVec3 vt[3]){

	texttri[0].s = (vt[0].x + ancho / 2) / ancho;
	texttri[0].t = (vt[0].y + alto / 2) / alto;
	texttri[1].s = (vt[1].x + ancho / 2) / ancho;
	texttri[1].t = (vt[1].y + alto / 2) / alto;
	texttri[2].s = (vt[2].x + ancho / 2) / ancho;
	texttri[2].t = (vt[2].y + alto / 2) / alto;

}


void Triangulo::setAnimar(){
	centro = { 0, 0, 0 };
	rotacion = 0;
	vertices[0] = { radio*cos(rotacion) + centro.x, radio * sin(rotacion) + centro.y, 0 };
	vertices[1] = { radio*cos(rotacion + 2.0 * 3.14 / 3.0) + centro.x, radio * sin(rotacion + 2.0 * 3.14 / 3.0) + centro.y, 0 };
	vertices[2] = { radio*cos(rotacion + 4.0 * 3.14 / 3.0) + centro.x, radio * sin(rotacion + 4.0 * 3.14 / 3.0) + centro.y, 0 };
}
//-------------------------------------------------------------------------

TriAnimado::TriAnimado(GLdouble rd, GLdouble tr, GLdouble rot) : tri(rd){
	radio = rd;
	trans = tr;
	rotacion = rot;

}

void TriAnimado::draw(){

	posx = radio * cos(trans);
	posy = radio * sin(trans);

	glTranslated(posx, posy, 0);
	glRotated(rotacion, 0.0, 0.0, 1.0);

	tri.cambio();

	tri.draw();

	glRotated(-rotacion, 0.0, 0.0, 1.0);
	glTranslated(-posx, -posy, 0);

}

void TriAnimado::update(){

	rotacion += 15;
	trans += 0.2;

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
		triangulos[i]->cambio();
		triangulos[i]->draw();
	}
}

void PiramideTri::añadirText(CTex2 coor[3]){
	triangulos[0]->texttri[0] = coor[0];
	triangulos[0]->texttri[1] = coor[1];
	triangulos[0]->texttri[2] = coor[2];

	triangulos[1]->texttri[0] = coor[1];
	triangulos[1]->texttri[1] = coor[2];
	triangulos[1]->texttri[2] = coor[0];

	triangulos[2]->texttri[0] = coor[2];
	triangulos[2]->texttri[1] = coor[0];
	triangulos[2]->texttri[2] = coor[1];
	
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

Rectangulo::Rectangulo(GLdouble alto, GLdouble ancho){

	vertices[0].set(-ancho / 2, alto / 2, 0);  
	vertices[1].set(-ancho / 2, -alto / 2, 0);
	vertices[2].set(ancho / 2, alto / 2, 0);
	vertices[3].set(ancho / 2, -alto / 2, 0);

	vtext[0].s = 0;
	vtext[0].t = 1;
	vtext[1].s = 0;
	vtext[1].t = 0;
	vtext[2].s = 1;
	vtext[2].t = 1;
	vtext[3].s = 1;
	vtext[3].t = 0;
	
	normal.set(0, 0, 1);

	color.a = 1;
	color.b = 0;
	color.g = 0;
	color.r = 0;

}

void Rectangulo::draw(){

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_2D);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glColor4d(color.r, color.g, color.b, color.a);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glVertexPointer(3, GL_DOUBLE, 0, vertices);
	glNormal3d(normal.x, normal.y, normal.z);

	glTexCoordPointer(2, GL_DOUBLE, 0, vtext);

	glLineWidth(2);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glLineWidth(1);

	glDisableClientState(GL_TEXTURE_2D);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Rectangulo::set(GLdouble anchop, GLdouble altop){
	vertices[0].set(-anchop / 2, altop / 2, 0);
	vertices[1].set(-anchop / 2, -altop / 2, 0);
	vertices[2].set(anchop / 2, altop / 2, 0);
	vertices[3].set(anchop / 2, -altop / 2, 0);
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



