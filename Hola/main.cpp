//#include <Windows.h>
//#include <gl/GL.h>
//#include <gl/GLU.h>
//#include <GL/glut.h>

#include <GL/freeglut.h>

#include "tipos.h"
#include "escena.h"

#include <iostream>
using namespace std;

//-------------------------------------------------------------------------

// Window size
int winWidth = 800, winHeight = 600;

// Viewport 
PuertoVista viewPort(0, 0, winWidth, winHeight);

// Camera: Scene visible area size and projection
Camara camera(winWidth, winHeight);

// Scene variables
Escena escena;

bool mosaico = false;

//----------- Callbacks ----------------------------------------------------

void display();
void resize(int newWidth, int newHeight);
void key(unsigned char key, int x, int y);
void specialKey(int key, int x, int y);
void mouse(int button, int state, int x, int y);
void motion(int px, int py);
void tiling();

enum Estados { Collage, Recortar, Animar , Diabolo };
Estados e = Collage;
//-------------------------------------------------------------------------

void intitGL(){ //OpenGL basic setting

	//glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_POLYGON_SMOOTH);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glShadeModel(GL_SMOOTH);

	glClearColor(1.0, 1.0, 1.0, 1.0);  // color de fondo (alpha=1 -> opaco)

	// ViewPort
	viewPort.set(viewPort.x, viewPort.y, winWidth, winHeight);  // glViewport(0, 0, WIDTH, HEIGHT);

	// Camera position and orentation
	camera.setEZ();
	// Scene visible area and projection  
	camera.setVV();

	// Luz ambiente global
	//GLfloat amb[]={0.25, 0.25, 0.25, 1.0};
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
	// Light0  set up
	glEnable(GL_LIGHT0);
	GLfloat LuzDifusa[4] = { 1, 1, 1, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LuzDifusa);
	//GLfloat LuzSp[4] = { 1, 1, 1, 1 };
	//glLightfv(GL_LIGHT0, GL_SPECULAR, LuzSp);
	//GLfloat LuzAmbiente[4]={0.3f, 0.3f, 0.3f, 1.0f};
	//glLightfv(GL_LIGHT0, GL_AMBIENT, LuzAmbiente);
	GLfloat posLuz0[4] = { 100.0, 100.0, 100.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, posLuz0);

	cout << glGetString(GL_VERSION) << '\n';
	cout << glGetString(GL_VENDOR) << '\n';
}

//-------------------------------------------------------------------------

int main(int argc, char *argv[]){

	cout << "Starting console..." << '\n';

	// Initialization
	glutInitWindowSize(winWidth, winHeight);
	//glutInitWindowPosition (140, 140);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutInit(&argc, argv);

	// Window construction
	int win = glutCreateWindow("Freeglut-project");  // window's identifier

	// Callback registration
	glutReshapeFunc(resize);
	glutKeyboardFunc(key);
	glutSpecialFunc(specialKey);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);

	// OpenGL basic setting
	intitGL();
	escena.init();

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
	// after X-closing the window, continue execution
	glutMainLoop();

	cin.sync();
	cin.get();

	return 0;
}

//-------------------------------------------------------------------------

void display(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	switch (e)
	{
	case Collage:
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		escena.rect.textura.activar();
		escena.rect.draw();
		escena.rect.textura.desactivar();

		escena.rect2.textura.activar();
		glRotated(-45.0, 0.0, 0.0, 1.0);
		glTranslated(-50.0, -300.0, 0.0);
		escena.rect2.draw();
		glTranslated(50.0, 300.0, 0.0);
		glRotated(45.0, 0.0, 0.0, 1.0);
		escena.rect2.textura.desactivar();

		escena.rect3.textura.activar();
		glTranslated(200.0, 200.0, 0.0);
		escena.rect3.draw();
		glTranslated(-200.0, -200.0, 0.0);
		escena.rect3.textura.desactivar();
		break;

	case Recortar:
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
		escena.rect4.textura.activar();
		escena.rect4.draw();
		escena.t.draw();
		break;

	case Animar:
		glEnable(GL_DEPTH_TEST);
		escena.draw();
		escena.tri.draw();
		break;
	case Diabolo:
		glEnable(GL_DEPTH_TEST);
		if (!mosaico){
			escena.draw();
			escena.drawDiabolo();
		}
		break;
	default:
		break;
	}
	
	if (mosaico)
		tiling();
	
	glPopMatrix();

	glutSwapBuffers();  //glFlush();
}

//-------------------------------------------------------------------------

void resize(int newWidth, int newHeight){

	winWidth = newWidth;
	winHeight = newHeight;

	// Resize Viewport
	viewPort.set(viewPort.x, viewPort.y, winWidth, winHeight);  //glViewport(0, 0, WIDTH, HEIGHT);

	// Resize Scene Visible Area 
	camera.setVV(winWidth, winHeight);
}

//-------------------------------------------------------------------------

void key(unsigned char key, int x, int y){

	bool need_redisplay = true;


	switch (key) {
	case 27:  // Escape key 
		glutLeaveMainLoop(); // Freeglut's sentence for stopping glut's main loop 
		break;
	case '+':
		glScaled(1.1, 1.1, 1.1); // aumentar la escala 
		break;
	case '-':
		glScaled(0.9, 0.9, 0.9); // reducir la escala 
		break;
	case 'l':
		camera.set3D();
		break;
	case 'o':
		camera.setEZ();
		break;
	case 't':
		escena.tri.update();
		break;
	case 'x':
		glRotated(1, 1.0, 0.0, 0.0);
		break;
	case 'y':
		glRotated(1, 0.0, 1.0, 0.0);
		break;
	case 'z':
		glRotated(1, 0.0, 0.0, 1.0);
		break;
	case 'r':
		escena.t.rotar();
		break;
	case 'm':
		mosaico = !mosaico;
		if (mosaico == false)
			viewPort.set(0, 0, winWidth, winHeight);
		break;
	case '2':
		escena.capturar(winWidth, winHeight);
		escena.rect4.textura.init();
		escena.rect4.textura.load("../bmps/collage.bmp");
		escena.rect4.textura.desactivar();
		e = Recortar;
		break;
	case '3':
		escena.tri.tri.recortar(winHeight, winWidth, escena.t.vertices);
		escena.tri.tri.setAnimar();
		e = Animar;
		break;
	case '4':
		escena.tri.tri.recortar(winHeight, winWidth, escena.t.vertices);
		for (auto p : escena.piramides){
			p->añadirText(escena.tri.tri.texttri);
		}
		e = Diabolo;
		break;
	default:
		need_redisplay = false;
		break;
	}//switch

	if (need_redisplay)
		glutPostRedisplay();
}

//-------------------------------------------------------------------------

void specialKey(int key, int x, int y){

	bool need_redisplay = true;

	switch (key) {
	case GLUT_KEY_RIGHT:
		glTranslated(1, 0, 0);  // trasladar 1 en el eje X
		break;
	case GLUT_KEY_LEFT:
		glTranslated(-1, 0, 0);
		break;
	case GLUT_KEY_UP:
		glRotated(1, 0, 0, 1);  // girar 1 en el eje Z
		break;
	case GLUT_KEY_DOWN:
		glRotated(-1, 0, 0, 1);
		break;
	default:
		need_redisplay = false;
		break;
	}//switch

	if (need_redisplay)
		glutPostRedisplay();
}

//-------------------------------------------------------------------------

void mouse(int button, int state, int x, int y){
	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_UP)) { // DOWN

	}
	else {

	}
}

//-------------------------------------------------------------------------

GLdouble xWin2VV(int mx) {
	return mx - winWidth / 2.0;
}

GLdouble yWin2VV(int my) {
	return (winHeight - my) - winHeight / 2.0;
}



void motion(int px, int py) {
	GLdouble x;
	GLdouble y;

	x = xWin2VV(px);
	y = yWin2VV(py);

	if (escena.t.dentro(x, y)){
		escena.t.posicionar(x, y);
		glutPostRedisplay();
	}
}

//-------------------------------------------------------------------------

void tiling(){

	int x = 0;
	int y = 0;
	int ancho = winWidth / 4;
	int alto = winHeight / 3;

	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 4; j++){
			viewPort.set(x, y, ancho, alto);
			escena.drawDiabolo();
			x += ancho;
		}
		x = 0;
		y += alto;
	}
}