#ifndef _H_Textura_H
#define _H_Textura_H



#include <GL/freeglut.h>
#include <string>
#include "PixMap24RGB.h"


class Textura {
public:
	Textura() : w(0), h(0), id(0) {};
	~Textura() { glDeleteTextures(1, &id); };
	void init() {
		glGenTextures(1, &id); // generar un nombre
		activar(); glTexParameteri(GL_TEXTURE_2D,
			GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Parametros de glTex inventados
	}; // establecer filtros
	void activar() {
		glBindTexture(GL_TEXTURE_2D, id); glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,
			GL_MODULATE);
	}; // Parametros de glTex inventados
	void desactivar() { glBindTexture(GL_TEXTURE_2D, 0); };
	bool load(const std::string & BMP_Name); // cargar y transferir a openGL
	void save(const std::string & BMP_Name); // obtener de openGL y guardar
public:
	GLuint w, h; // dimensiones de la imagen
	GLuint id; // identificador interno de la textura
};


bool Textura::load(const std::string & BMP_Name) {
	// la textura debe estar inicializada -> escena::init()
	PixMap24RGB pixMap;
	pixMap.load_bmpBGR(BMP_Name); // cargar
								  // carga correcta??
	w = pixMap.width();
	h = pixMap.height();
	glBindTexture(GL_TEXTURE_2D, id); // transferir a openGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB,
		GL_UNSIGNED_BYTE, pixMap.map());

	return true;
}

void Textura::save(const std::string & BMP_Name) {
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, // obtener de openGL
		GL_UNSIGNED_BYTE, pA);

	// pA-> array donde guardar los datos (de tipo y tamaño adecuado)
	//… // y guardar
}

#endif
