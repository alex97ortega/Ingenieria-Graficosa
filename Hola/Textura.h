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
		glBindTexture(GL_TEXTURE_2D, id); glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	};

	void desactivar() { glBindTexture(GL_TEXTURE_2D, 0); };
	bool load(const std::string & BMP_Name); // cargar y transferir a openGL
	void save(const std::string & BMP_Name); // obtener de openGL y guardar

	bool load(const std::string & BMP_Name, GLubyte alpha);
	bool load(const std::string & BMP_Name, PixMap24RGB::rgb_color colorKey, GLubyte alpha);

public:
	GLuint w, h; // dimensiones de la imagen
	GLuint id; // identificador interno de la textura
	PixMap24RGB map;
	
};
