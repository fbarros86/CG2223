#include "../libs/tiny_obj_loader.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "texture.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <IL/il.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

class Model {
public:
	unsigned int indexesCount;
	bool isObj, hadTex;
	GLuint vertices, indices, normals, texCoords;
	std::string file_name;
	Texture textura;
	int points_size;
	

	Model(std::string file_name, bool hadTex, std::string tex_name);

	void draw(bool hadtex);
};