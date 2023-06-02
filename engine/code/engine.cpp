#define TINYOBJLOADER_IMPLEMENTATION
#include <iostream>
#include <vector>
#include "../libs/rapidxml.hpp"
#include "../libs/rapidxml_utils.hpp"
#include "../libs/rapidxml_print.hpp"
#include "../libs/rapidxml_iterators.hpp"
#include "../libs/tiny_obj_loader.h"

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
#include "engine.h"

using namespace rapidxml;
using namespace tinyobj;
xml_node<>* LIGHT_NODE;
xml_node<>* groupNode;

//float camX = 0, camY, camZ = 5;
int startX, startY, tracking = 0;

float alpha = 0, beta = 0, r, mode = 1;

int width, height, size;
int startTime = glutGet(GLUT_ELAPSED_TIME);
float Px, Py, Pz, Lx, Ly, Lz, Ux, Uy, Uz, fov, near, far;
float lastToggleTime = 0.0f;
float* buffer;
std::vector<unsigned int> INDEXES;
GLuint INDICES;
std::vector<GLint> TEXTURE_IDS;
std::vector<float> MODEL_POINTS;
std::vector<float> TEXTURE_POINTS;
std::vector<float> NORMAL_POINTS;
std::vector<int> POINTS_COUNTER;
int GLOBAL_COUNTER = 0, COUNTER = 0, LIGHTS_COUNTER=0;
GLuint buffers[3];
bool AXIS_ENABLE;



void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if (h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set perspective
	float aspectRatio = (float)w / (float)h;
	gluPerspective(fov, aspectRatio, near, far);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}
void converte() {
	Px = r * cos(beta) * sin(alpha);
	Py = r * sin(beta);
	Pz = r * cos(beta) * cos(alpha);
	//printf("raio:%f, Px:%f, Py:%f, Pz:%f\n", r, Px, Py, Pz);
}
void multMatrixVector(float* m, float* v, float* res) {

	for (int j = 0; j < 4; ++j) {
		res[j] = 0;
		for (int k = 0; k < 4; ++k) {
			res[j] += v[k] * m[j * 4 + k];
		}
	}
}
void cross(float* a, float* b, float* res) {

	res[0] = a[1] * b[2] - a[2] * b[1];
	res[1] = a[2] * b[0] - a[0] * b[2];
	res[2] = a[0] * b[1] - a[1] * b[0];
}
void buildRotMatrix(float* x, float* y, float* z, float* m) {

	m[0] = x[0]; m[1] = x[1]; m[2] = x[2]; m[3] = 0;
	m[4] = y[0]; m[5] = y[1]; m[6] = y[2]; m[7] = 0;
	m[8] = z[0]; m[9] = z[1]; m[10] = z[2]; m[11] = 0;
	m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}
float length(float* v) {

	float res = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	return res;

}

void drawTriangles(float* triangulos, int N) {
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < (N-2);i += 3) {
		//std::cout << triangulos[i] << " " << triangulos[i + 1] << " " << triangulos[i + 2] << "\n";
		glVertex3f(triangulos[i], triangulos[i + 1], triangulos[i + 2]);
	}
	glEnd();
}

void drawAxis(void) {
	GLfloat red[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
	GLfloat green[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
	GLfloat blue[4] = { 0.0f, 0.0f, 1.0f, 1.0f };

	glDisable(GL_LIGHTING);  // Disable lighting to ensure the axis is not affected

	glBegin(GL_LINES);
	// X axis in red
	glColor4fv(red);  // Set the color for the X axis
	glVertex3f(-10000.0f, 0.0f, 0.0f);
	glVertex3f(10000.0f, 0.0f, 0.0f);

	// Y Axis in Green
	glColor4fv(green);  // Set the color for the Y axis
	glVertex3f(0.0f, -10000.0f, 0.0f);
	glVertex3f(0.0f, 10000.0f, 0.0f);

	// Z Axis in Blue
	glColor4fv(blue);  // Set the color for the Z axis
	glVertex3f(0.0f, 0.0f, -10000.0f);
	glVertex3f(0.0f, 0.0f, 10000.0f);
	glEnd();

	glEnable(GL_LIGHTING);
}

void getCatmullRomPoint(float t,
	float* p0, float* p1, float* p2, float* p3,
	float* pos, float* deriv) {
	// Catmull-Rom basis matrix
	float m[4][4] = { {-0.5f, 1.5f, -1.5f, 0.5f},
					 {1.0f, -2.5f, 2.0f, -0.5f},
					 {-0.5f, 0.0f, 0.5f, 0.0f},
					 {0.0f, 1.0f, 0.0f, 0.0f} };

	float T[4] = { t * t * t, t * t, t, 1 };

	// Compute A = M * P for each component (x, y, z)
	float A[3][4];
	for (int i = 0; i < 3; i++) {
		float P[4] = { p0[i], p1[i], p2[i], p3[i] };
		multMatrixVector(&m[0][0], P, A[i]);
	}

	// Compute pos = T * A for each component (x, y, z)
	for (int i = 0; i < 3; i++) {
		pos[i] = T[0] * A[i][0] + T[1] * A[i][1] + T[2] * A[i][2] + T[3] * A[i][3];
	}

	// Compute T' vector based on input t
	float Tp[4] = { 3 * t * t, 2 * t, 1, 0 };

	// Compute deriv = T' * A for each component (x, y, z)
	for (int i = 0; i < 3; i++) {
		deriv[i] = Tp[0] * A[i][0] + Tp[1] * A[i][1] + Tp[2] * A[i][2] + Tp[3] * A[i][3];
	}
}

void getGlobalCatmullRomPoint(float gt, float* pos, float* deriv, int point_count, std::vector<float> p) {

	float t = gt * point_count; // this is the real global t
	int index = floor(t);  // which segment
	t = t - index; // where within  the segment

	// indices store the points
	int indices[4];
	indices[0] = (index + point_count - 1) % point_count;
	indices[1] = (indices[0] + 1) % point_count;
	indices[2] = (indices[1] + 1) % point_count;
	indices[3] = (indices[2] + 1) % point_count;

	getCatmullRomPoint(t, &p[indices[0]*3], &p[indices[1]*3], &p[indices[2]*3], &p[indices[3]*3], pos, deriv);
}


void timedlights(float time, int light, GLenum pname, GLfloat* dirorpos) {
	float elapsedTime = (glutGet(GLUT_ELAPSED_TIME) - startTime) / 1000.0f;

	// Check if the time interval has passed since the last light toggle
	if (elapsedTime - lastToggleTime >= time) {
		// Toggle the light
		if (glIsEnabled(GL_LIGHT0 + light)) {
			glDisable(GL_LIGHT0 + light);
		}
		else {
			glEnable(GL_LIGHT0 + light);
			glLightfv(GL_LIGHT0 + light, pname, dirorpos);
		}

		// Update the last toggle time
		lastToggleTime = elapsedTime;
	}
}

void lights() {
	if (LIGHT_NODE) {
		LIGHTS_COUNTER = 0;
		for (xml_node<>* lights_node = LIGHT_NODE->first_node(); lights_node; lights_node = lights_node->next_sibling()) {
			std::string lightNodeName = lights_node->name();
			if (lightNodeName == "light") {
				float time=0;
				if (lights_node->first_attribute("time")) time = std::stof(lights_node->first_attribute("time")->value());
				std::string type = lights_node->first_attribute("type")->value();
				if (LIGHTS_COUNTER != 0) {
					glEnable(GL_LIGHT0 + LIGHTS_COUNTER);
					GLfloat defaultvalues[4] = { 1,1,1,1 };
					GLfloat defaultvalues2[4] = { 0,0,0,1 };
					glLightfv(GL_LIGHT0 + LIGHTS_COUNTER, GL_AMBIENT, defaultvalues2);
					glLightfv(GL_LIGHT0 + LIGHTS_COUNTER, GL_DIFFUSE, defaultvalues);
					glLightfv(GL_LIGHT0 + LIGHTS_COUNTER, GL_SPECULAR, defaultvalues);

				}
				if (type == "point") {
					float posX_light = std::stof(lights_node->first_attribute("posx")->value());
					float posY_light = std::stof(lights_node->first_attribute("posy")->value());
					float posZ_light = std::stof(lights_node->first_attribute("posz")->value());
					GLfloat lightPosition[4] = { posX_light, posY_light, posZ_light, 1.0f };
					if (time != 0) {
						timedlights(time,LIGHTS_COUNTER, GL_POSITION, lightPosition);
					}
					else {
						glLightfv(GL_LIGHT0 + LIGHTS_COUNTER, GL_POSITION, lightPosition);
					}
					LIGHTS_COUNTER++;

				}
				else if (type == "directional") {
					float dirX_light = std::stof(lights_node->first_attribute("dirx")->value());
					float dirY_light = std::stof(lights_node->first_attribute("diry")->value());
					float dirZ_light = std::stof(lights_node->first_attribute("dirz")->value());
					GLfloat lightDirection[4] = { dirX_light, dirY_light, dirZ_light, 0.0f };
					if (time != 0) {
						timedlights(time,LIGHTS_COUNTER, GL_POSITION, lightDirection);
					}
					else {

						glLightfv(GL_LIGHT0 + LIGHTS_COUNTER, GL_POSITION, lightDirection);
					}
					LIGHTS_COUNTER++;

				}
				else if (type == "spot") {
					float posX_light = std::stof(lights_node->first_attribute("posx")->value());
					float posY_light = std::stof(lights_node->first_attribute("posy")->value());
					float posZ_light = std::stof(lights_node->first_attribute("posz")->value());
					float dirX_light = std::stof(lights_node->first_attribute("dirx")->value());
					float dirY_light = std::stof(lights_node->first_attribute("diry")->value());
					float dirZ_light = std::stof(lights_node->first_attribute("dirz")->value());
					float cutoff = std::stof(lights_node->first_attribute("cutoff")->value());
					GLfloat lightPosition[4] = { posX_light, posY_light, posZ_light, 1.0f };
					GLfloat lightDirection[4] = { dirX_light, dirY_light, dirZ_light };
					if (time != 0) {
						timedlights(time,LIGHTS_COUNTER, GL_POSITION, lightPosition);
						timedlights(time,LIGHTS_COUNTER, GL_POSITION, lightPosition);
						timedlights(time,LIGHTS_COUNTER, GL_POSITION, lightPosition);
					}
					else {
						glLightfv(GL_LIGHT0 + LIGHTS_COUNTER, GL_POSITION, lightPosition);
						glLightfv(GL_LIGHT0 + LIGHTS_COUNTER, GL_SPOT_DIRECTION, lightDirection);
						glLightf(GL_LIGHT0 + LIGHTS_COUNTER, GL_SPOT_CUTOFF, cutoff);
					}
					LIGHTS_COUNTER++;
				}
			}

		}
	}
}

int loadTexture(std::string s) {

	unsigned int t, tw, th;
	unsigned char* texData;
	unsigned int texID;

	ilInit();
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

	ilGenImages(1, &t);
	ilBindImage(t);
	ilLoadImage((ILstring)s.c_str());

	tw = ilGetInteger(IL_IMAGE_WIDTH);
	th = ilGetInteger(IL_IMAGE_HEIGHT);

	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

	texData = ilGetData();

	// create a texture slot
	glGenTextures(1, &texID);
	// bind the slot
	glBindTexture(GL_TEXTURE_2D, texID);

	// define texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	// send texture data to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	return texID;

}

int isOBJFile(const std::string& file_name) {
	// Find the last occurrence of '.' in the file name
	std::size_t dot_index = file_name.find_last_of(".");

	// Check if a dot was found and it is not the first or last character
	if (dot_index != std::string::npos && dot_index != 0 && dot_index != file_name.length() - 1) {
		// Get the file extension by extracting the substring after the dot
		std::string file_extension = file_name.substr(dot_index + 1);

		// Compare the file extension with "obj" (case-insensitive)
		for (char& c : file_extension) {
			c = std::tolower(c);
		}
		return file_extension == "obj";
	}
	return false;
}



void storeFigure(std::string file_name) {
	bool isObj = isOBJFile(file_name);
	std::string full_path = "../models/" + file_name;

	std::ifstream model_file("../models/" + file_name);
	if (!model_file.is_open()) {
		std::cerr << "Error: Failed to open model file " << file_name << std::endl;
	}

	if (!isObj) {

		float value1, value2, value3, normal1, normal2, normal3, texture1, texture2;
		std::string line;

		std::getline(model_file, line);
		std::istringstream iss(line);

		while (iss >> value1 >> value2 >> value3 >> normal1 >> normal2 >> normal3 >> texture1 >> texture2) {


			MODEL_POINTS.push_back(value1);
			MODEL_POINTS.push_back(value2);
			MODEL_POINTS.push_back(value3);

			NORMAL_POINTS.push_back(normal1);
			NORMAL_POINTS.push_back(normal2);
			NORMAL_POINTS.push_back(normal3);

			TEXTURE_POINTS.push_back(texture1);
			TEXTURE_POINTS.push_back(texture2);
		}

		std::getline(model_file, line);
		std::istringstream iss2(line);

		while (iss2 >> value1) {
			INDEXES.push_back(value1);
			COUNTER++;
		}

		POINTS_COUNTER.push_back(COUNTER);
	}
	else {
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;

		std::string warn;
		std::string err;

		bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, full_path.c_str());

		if (!warn.empty()) {
			std::cout << warn << std::endl;
		}

		if (!err.empty()) {
			std::cerr << err << std::endl;
		}

		if (!ret) {
			exit(1);
		}

		// Loop over shapes
		for (size_t s = 0; s < shapes.size(); s++) {
			// Loop over faces(polygon)
			size_t index_offset = 0;
			for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
				size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

				// Loop over vertices in the face.
				for (size_t v = 0; v < fv; v++) {
					// access to vertex
					tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

					tinyobj::real_t vx = attrib.vertices[3 * size_t(idx.vertex_index) + 0];
					tinyobj::real_t vy = attrib.vertices[3 * size_t(idx.vertex_index) + 1];
					tinyobj::real_t vz = attrib.vertices[3 * size_t(idx.vertex_index) + 2];
					MODEL_POINTS.push_back(vx);
					MODEL_POINTS.push_back(vy);
					MODEL_POINTS.push_back(vz);
					// Check if `normal_index` is zero or positive. negative = no normal data
					if (idx.normal_index >= 0) {
						tinyobj::real_t nx = attrib.normals[3 * size_t(idx.normal_index) + 0];
						tinyobj::real_t ny = attrib.normals[3 * size_t(idx.normal_index) + 1];
						tinyobj::real_t nz = attrib.normals[3 * size_t(idx.normal_index) + 2];
						NORMAL_POINTS.push_back(nx);
						NORMAL_POINTS.push_back(ny);
						NORMAL_POINTS.push_back(nz);
					}

					// Check if `texcoord_index` is zero or positive. negative = no texcoord data
					if (idx.texcoord_index >= 0) {
						tinyobj::real_t tx = attrib.texcoords[2 * size_t(idx.texcoord_index) + 0];
						tinyobj::real_t ty = attrib.texcoords[2 * size_t(idx.texcoord_index) + 1];
						TEXTURE_POINTS.push_back(tx);
						TEXTURE_POINTS.push_back(ty);
					}
					// Optional: vertex colors
					// tinyobj::real_t red   = attrib.colors[3*size_t(idx.vertex_index)+0];
					// tinyobj::real_t green = attrib.colors[3*size_t(idx.vertex_index)+1];
					// tinyobj::real_t blue  = attrib.colors[3*size_t(idx.vertex_index)+2];
				}
				index_offset += fv;
				COUNTER+=fv;


				// per-face material
				shapes[s].mesh.material_ids[f];
			}
		}
	POINTS_COUNTER.push_back(COUNTER);
	}
}

void storeTexture(std::string texture_name) {
	std::string path = "../textures/" + texture_name;
	const char* c_path = path.c_str();
	/*
	std::ifstream model_file("../textures/" + texture_name);
	if (!model_file.is_open()) {
		std::cerr << "Error: Failed to open model file " << texture_name << std::endl;
	}
	*/
	GLuint texID = loadTexture(c_path);
	TEXTURE_IDS.push_back(texID);

}

void drawFigure(int i, bool hadtex) {
	if (hadtex) {
		glBindTexture(GL_TEXTURE_2D, TEXTURE_IDS[i]);
		glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
		glTexCoordPointer(2, GL_FLOAT, 0, 0);
	}
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glVertexPointer(3, GL_FLOAT, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
	glNormalPointer(GL_FLOAT, 0, 0);
	int inicio, fim;
	if (i == 0) {
		inicio = 0;
		fim = POINTS_COUNTER[i];
	}
	else {
		inicio = POINTS_COUNTER[i - 1];
		fim = POINTS_COUNTER[i];
	}
	int vertices = (fim - inicio);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, INDICES);
	glDrawElements(GL_TRIANGLES, vertices, GL_UNSIGNED_INT, 0);
}	

void animateRotate(float x, float y, float z, float time) {
	float elapsedTime = (glutGet(GLUT_ELAPSED_TIME) - startTime)/ 1000.0f;
	float rotation = 360.0f * fmod(elapsedTime,time) / time;
	glRotatef(rotation, x, y, z);
	
}

void animateTranslate(std::vector<float> points, float duration, bool isAligned) {
	static float lastY[3] = { 0,1.0f,0 };
	float elapsedTime = (glutGet(GLUT_ELAPSED_TIME) - startTime) / 1000.0f;
	float time_loop = fmod(elapsedTime, duration);
	float gt = time_loop/duration;
	int num_points = points.size()/3;
	float pos[3], deriv[3];
	glBegin(GL_LINE_LOOP);
	float j = 0;
	for (int i = 0; i < 100;i++) {
		j += 0.01f;
		getGlobalCatmullRomPoint(j, pos, deriv,num_points,points);
		glVertex3f(pos[0], pos[1], pos[2]);
	}
	glEnd();
	getGlobalCatmullRomPoint(gt, pos, deriv, num_points, points);
	glTranslatef(pos[0], pos[1], pos[2]);
	if (isAligned) {
		float X[3], Z[3];
		float moduloDeriv = length(deriv);
		X[0] = deriv[0] / moduloDeriv;
		X[1] = deriv[1] / moduloDeriv;
		X[2] = deriv[2] / moduloDeriv;

		cross(X, lastY, Z);
		cross(Z, X, lastY);
		float m[16];
		buildRotMatrix(X, lastY, Z, m);
		glMultMatrixf(m);
	}	
}

void parseGroup(xml_node<>* groupNode) {
	glPushMatrix();
	for (xml_node<>* node = groupNode->first_node(); node; node = node->next_sibling()) {
		std::string nodeName = node->name();
		if (nodeName == "transform") {
			// Process transform node
			for (xml_node<>* childNode = node->first_node(); childNode; childNode = childNode->next_sibling()) {
				std::string childNodeName = childNode->name();
				if (childNodeName == "translate") {
					// Process translate node
					if(childNode->first_attribute("x")){
						float x = std::stof(childNode->first_attribute("x")->value());
						float y = std::stof(childNode->first_attribute("y")->value());
						float z = std::stof(childNode->first_attribute("z")->value());
						glTranslatef(x, y, z);
					}
					else{
						float x = std::stof(childNode->first_attribute("time")->value());
						std::string align = childNode->first_attribute("align")->value();
						bool isAligned = (align=="True"||align=="true");
						std::vector<float> points;
						for (xml_node<>* point = childNode->first_node(); point; point = point->next_sibling()){
							float pointX = std::stof(point->first_attribute("x")->value());
    						float pointY = std::stof(point->first_attribute("y")->value());
							float pointZ = std::stof(point->first_attribute("z")->value());
							points.push_back(pointX);
							points.push_back(pointY);
							points.push_back(pointZ);

						}
						animateTranslate(points,x, isAligned);

					}
				}
				else if (childNodeName == "rotate") {
					// Process rotate node
					float angle = 0, time = 0;
					if (childNode->first_attribute("angle")) angle = std::stof(childNode->first_attribute("angle")->value());
					else if (childNode->first_attribute("time")) time = std::stof(childNode->first_attribute("time")->value());
					float x = std::stof(childNode->first_attribute("x")->value());
					float y = std::stof(childNode->first_attribute("y")->value());
					float z = std::stof(childNode->first_attribute("z")->value());
					if (angle != 0) glRotatef(angle, x, y, z);
					else if (time != 0) {
						animateRotate(x, y, z, time);
					}


				}
				else if (childNodeName == "scale") {
					// Process scale node
					float x = std::stof(childNode->first_attribute("x")->value());
					float y = std::stof(childNode->first_attribute("y")->value());
					float z = std::stof(childNode->first_attribute("z")->value());
					glScalef(x, y, z);
				}
			}
		}
		else if (nodeName == "models") {
			for (xml_node<>* childNode = node->first_node(); childNode; childNode = childNode->next_sibling()) {
				std::string childNodeName = childNode->name();
				bool hadtexture = false;
				if (childNodeName == "model") {
					bool hadColor = false;
					std::vector<float> color_diffuse_settings = { -1.0f,-1.0f,-1.0f,-1.0f };
					std::vector<float> color_ambient_settings = { -1.0f,-1.0f,-1.0f,-1.0f };
					std::vector<float> color_specular_settings = { -1.0f,-1.0f,-1.0f,-1.0f };
					std::vector<float> color_emissive_settings = { -1.0f,-1.0f,-1.0f,-1.0f };
					float color_shiny_settings = -1;

					
					for (xml_node<>* babyNode = childNode->first_node(); babyNode; babyNode = babyNode->next_sibling()) {
						std::string babyNodeName = babyNode->name();
						if (babyNodeName == "texture") {
							hadtexture = true;
						}
						else if (babyNodeName == "color") {
							hadColor = true;
							for (xml_node<>* color = babyNode->first_node(); color; color = color->next_sibling()) {
								std::string colorNodeName = color->name();
								if (colorNodeName == "diffuse") {
									float r = std::stof(color->first_attribute("R")->value());
									float g = std::stof(color->first_attribute("G")->value());
									float b = std::stof(color->first_attribute("B")->value());
									float lightcolor_difuse[4] = { r/255.0f,g / 255.0f,b / 255.0f,1.0f };
									color_diffuse_settings = { r / 255.0f,g / 255.0f,b / 255.0f,1.0f };
									//glLightfv(GL_LIGHT0, GL_DIFFUSE, lightcolor);
								}
								else if (colorNodeName == "ambient") {
									float r = std::stof(color->first_attribute("R")->value());
									float g = std::stof(color->first_attribute("G")->value());
									float b = std::stof(color->first_attribute("B")->value());
									float lightcolor_ambient[4] = { r / 255.0f,g / 255.0f,b / 255.0f,1.0f };
									color_ambient_settings = { r / 255.0f,g / 255.0f,b / 255.0f,1.0f };
									//glLightfv(GL_LIGHT0, GL_AMBIENT, lightcolor);
								}
								else if (colorNodeName == "specular") {
									float r = std::stof(color->first_attribute("R")->value());
									float g = std::stof(color->first_attribute("G")->value());
									float b = std::stof(color->first_attribute("B")->value());
									float lightcolor_specular[4] = { r,g,b,1.0f };
									color_specular_settings = { r / 255.0f,g / 255.0f,b / 255.0f,1.0f };
									//glLightfv(GL_LIGHT0, GL_SPECULAR, lightcolor);
								}
								else if (colorNodeName == "emissive") {
									float r = std::stof(color->first_attribute("R")->value());
									float g = std::stof(color->first_attribute("G")->value());
									float b = std::stof(color->first_attribute("B")->value());
									float lightcolor_emissive[4] = { r / 255.0f,g / 255.0f,b / 255.0f,1.0f };
									color_emissive_settings = { r / 255.0f,g / 255.0f,b / 255.0f,1.0f };
									//glLightfv(GL_LIGHT0, GL_EMISSION, lightcolor);

								}
								else if (colorNodeName == "shininess") {
									color_shiny_settings = std::stof(color->first_attribute("value")->value());
								}
						}
					}
					}
					//glPushAttrib(GL_LIGHTING_BIT);
					//glPushAttrib(GL_COLOR_BUFFER_BIT);
					if (!hadColor && !hadtexture) {
						float black[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
						float color1 = 200.0f / 255.0f;
						float color2 = 50.0f / 255.0f;
						float grey[4] = { color1,color1,color1 ,1.0f};
						float darkgrey[4] = { color2,color2,color2 , 1.0f};
						glMaterialfv(GL_FRONT, GL_AMBIENT, grey);
						glMaterialfv(GL_FRONT, GL_DIFFUSE, darkgrey);
						glMaterialfv(GL_FRONT, GL_SPECULAR, black);
						glMaterialfv(GL_FRONT, GL_EMISSION, black);
						glMaterialf(GL_FRONT, GL_SHININESS, 0);
					}
					else {
						GLfloat color_diffuse[4];
						GLfloat color_ambient[4];
						GLfloat color_specular[4];
						GLfloat color_emissive[4];
						GLfloat color_shininess;
						std::copy(color_diffuse_settings.begin(), color_diffuse_settings.end(), color_diffuse);
						std::copy(color_ambient_settings.begin(), color_ambient_settings.end(), color_ambient);
						std::copy(color_specular_settings.begin(), color_specular_settings.end(), color_specular);
						std::copy(color_emissive_settings.begin(), color_emissive_settings.end(), color_emissive);
						color_shininess = color_shiny_settings;
						
						if(color_diffuse_settings[0]!=-1.0f){
							glMaterialfv(GL_FRONT, GL_DIFFUSE, color_diffuse);
						}
						if (color_ambient_settings[0] != -1.0f) {
							glMaterialfv(GL_FRONT, GL_AMBIENT, color_ambient);
						}
						if (color_specular_settings[0] != -1.0f) {
							glMaterialfv(GL_FRONT, GL_SPECULAR, color_specular);
						}
						if (color_emissive_settings[0] != -1.0f) {
							glMaterialfv(GL_FRONT, GL_EMISSION, color_emissive);
						}
						if (color_shiny_settings != -1.0f) {
							glMaterialf(GL_FRONT, GL_SHININESS, color_shininess);
						}
					}
					//glPopAttrib();
					drawFigure(GLOBAL_COUNTER, hadtexture);
					GLOBAL_COUNTER++;

				}
			}
			//glPopAttrib();

				
		}
		else if (nodeName == "lights") {
			for (xml_node<>* lightNode = node->first_node(); lightNode; lightNode = lightNode->next_sibling()) {
				std::string lightNodeName = lightNode->name();
				if (lightNodeName == "light") {
					std::string type = lightNode->first_attribute("type")->value();
					if (LIGHTS_COUNTER != 0) {
						glEnable(GL_LIGHT0 + LIGHTS_COUNTER);
					}
					if (type == "point") {
						float posX = std::stof(lightNode->first_attribute("posx")->value());
						float posY = std::stof(lightNode->first_attribute("posy")->value());
						float posZ = std::stof(lightNode->first_attribute("posz")->value());
						GLfloat lightPosition[4] = { posX, posY, posZ, 1.0f };
						glLightfv(GL_LIGHT0+LIGHTS_COUNTER, GL_POSITION, lightPosition);
						LIGHTS_COUNTER++;

					}
					else if (type == "directional") {
						float dirX = std::stof(lightNode->first_attribute("dirx")->value());
						float dirY = std::stof(lightNode->first_attribute("diry")->value());
						float dirZ = std::stof(lightNode->first_attribute("dirz")->value());
						GLfloat lightDirection[4] = { dirX, dirY, dirZ, 0.0f };
						glLightfv(GL_LIGHT0+LIGHTS_COUNTER, GL_POSITION, lightDirection);
						LIGHTS_COUNTER++;

					}
					else if (type == "spotlight") {
						float posX = std::stof(lightNode->first_attribute("posx")->value());
						float posY = std::stof(lightNode->first_attribute("posy")->value());
						float posZ = std::stof(lightNode->first_attribute("posz")->value());
						float dirX = std::stof(lightNode->first_attribute("dirx")->value());
						float dirY = std::stof(lightNode->first_attribute("diry")->value());
						float dirZ = std::stof(lightNode->first_attribute("dirz")->value());
						float cutoff = std::stof(lightNode->first_attribute("cutoff")->value());
						GLfloat lightPosition[4] = { posX, posY, posZ, 1.0f };
						glLightfv(GL_LIGHT0+ LIGHTS_COUNTER, GL_POSITION, lightPosition);
						GLfloat lightDirection[4] = { dirX, dirY, dirZ };
						glLightfv(GL_LIGHT0+ LIGHTS_COUNTER, GL_SPOT_DIRECTION, lightDirection);
						glLightf(GL_LIGHT0+ LIGHTS_COUNTER, GL_SPOT_CUTOFF, cutoff);
						LIGHTS_COUNTER++;


					}
				}
			}
		}
		else if (nodeName == "group") {
			parseGroup(node);
		}
	}
	glPopMatrix();
}

void storeTextures(xml_node<>* groupNode) {
	for (xml_node<>* node = groupNode->first_node(); node; node = node->next_sibling()) {
		std::string nodeName = node->name();
		if (nodeName == "models") {
			// Process models node
			for (xml_node<>* childNode = node->first_node(); childNode; childNode = childNode->next_sibling()) {
				std::string childNodeName = childNode->name();
				if (childNodeName == "model") {
					// Process model node
					for (xml_node<>* babyNode = childNode->first_node(); babyNode; babyNode = babyNode->next_sibling()) {
						std::string babyNodeName = babyNode->name();
						if (babyNodeName == "texture") {
							std::string textureFile = babyNode->first_attribute("file")->value();
							storeTexture(textureFile);
						}
					}

				}
			}
		}
		else if (nodeName == "group") {
			storeTextures(node);
		}
	}

}

void storeModelFiles(xml_node<>* groupNode) {

	for (xml_node<>* node = groupNode->first_node(); node; node = node->next_sibling()) {
		std::string nodeName = node->name();
		if (nodeName == "models") {
			// Process models node
			for (xml_node<>* childNode = node->first_node(); childNode; childNode = childNode->next_sibling()) {
				std::string childNodeName = childNode->name();
				if (childNodeName == "model") {
					// Process model node

					std::string fileName = childNode->first_attribute("file")->value();
					storeFigure(fileName);

				}
			}
		}
		else if (nodeName == "group") {
			storeModelFiles(node);
		}
	}
}

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(Px, Py, Pz,Lx, Ly, Lz,Ux, Uy, Uz);
	lights();


	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (AXIS_ENABLE) {
		drawAxis();
	}
	//glColor3f(1.0f, 1.0f, 1.0f);
	parseGroup(groupNode);
	GLOBAL_COUNTER = 0;
	glutSwapBuffers();
}

void processKeys(unsigned char key, int xx, int yy) {
	switch (key) {
	case 't':
		if (AXIS_ENABLE) {
			AXIS_ENABLE = false;
		}
		else {
			AXIS_ENABLE = true;
		}
		break;
	case 'w':
		beta += 0.1f;
		if (beta > 1.5f)
			beta = 1.5f;
		break;
	case 's':
		beta -= 0.1f;
		if (beta < -1.5f)
			beta = -1.5f;
		break;
	case 'a':
		alpha -= 0.1; break;
		break;
	case 'd':
		alpha += 0.1; break;
		break;
	case ' ':
		Px += Ux /10.0f;
		Py += Uy / 10.0f;
		Pz += Uz / 10.0f;
		break;
	case 'c':
		Px -= Ux / 10.0f;
		Py -= Uy / 10.0f;
		Pz -= Uz / 10.0f;
		break;
	case 'z':
		r -= 0.1f;
		if (r < 0.1f)
			r = 0.1f;
		break;
	case 'x':
		r += 0.1f;
		break;
	}
	converte();
	glutPostRedisplay();
}

void processSpecial(int key, int xx, int yy)
{
	switch (key) {

	case GLUT_KEY_RIGHT:
		alpha -= 0.1; break;

	case GLUT_KEY_LEFT:
		alpha += 0.1; break;

	case GLUT_KEY_UP:
		beta += 0.1f;
		if (beta > 1.5f)
			beta = 1.5f;
		break;

	case GLUT_KEY_DOWN:
		beta -= 0.1f;
		if (beta < -1.5f)
			beta = -1.5f;
		break;

	case GLUT_KEY_PAGE_DOWN: r -= 0.1f;
		if (r < 0.1f)
			r = 0.1f;
		break;

	case GLUT_KEY_PAGE_UP: r += 0.1f; break;

	case GLUT_KEY_F1: mode = !mode;
		//printf("mode: %d\n", mode);
		break;

	}
	converte();
	glutPostRedisplay();

}


void processMouseButtons(int button, int state, int xx, int yy)
{
	if (state == GLUT_DOWN) {
		startX = xx;
		startY = yy;
		if (button == GLUT_LEFT_BUTTON)
			tracking = 1;
		else if (button == GLUT_RIGHT_BUTTON)
			tracking = 2;
		else
			tracking = 0;
	}
	else if (state == GLUT_UP) {
		if (tracking == 1) {
			alpha += (xx - startX);
			beta += (yy - startY);
		}
		else if (tracking == 2) {

			r -= yy - startY;
			if (r < 1.5f*near) {
				r = 1.5f*near;
			}
		}
		tracking = 0;
	}
}

void processMouseMotion(int xx, int yy)
{
	int deltaX, deltaY;
	int alphaAux, betaAux;
	int rAux;

	if (!tracking)
		return;

	deltaX = xx - startX;
	deltaY = yy - startY;

	if (tracking == 1) {

		alphaAux = alpha + deltaX;
		betaAux = beta + deltaY;

		if (betaAux > 85.0)
			betaAux = 85.0;
		else if (betaAux < -85.0)
			betaAux = -85.0;

		rAux = r;
	}
	else if (tracking == 2) {

		alphaAux = alpha;
		betaAux = beta;
		rAux = r - deltaY;
		if (rAux < 3)
			rAux = 3;
	}
	
	Px = rAux * sin(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	Pz = rAux * cos(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	Py = rAux * sin(betaAux * 3.14 / 180.0);
	
	//converte();
}

void initGL() {
	// OpenGL settings 
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glClearColor(0, 0, 0, 0);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_RESCALE_NORMAL);
	glEnable(GL_NORMALIZE);
	
	float amb[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);

	glGenBuffers(3, buffers);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * MODEL_POINTS.size(), MODEL_POINTS.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * NORMAL_POINTS.size(), NORMAL_POINTS.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * TEXTURE_POINTS.size(), TEXTURE_POINTS.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &INDICES);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, INDICES);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * INDEXES.size(), INDEXES.data(), GL_STATIC_DRAW);
}


int main(int argc, char** argv) {
	xml_document<> doc;
	xml_node<>* world_node;
	AXIS_ENABLE = true;

	// Read the XML file
	file<> xml_file("../config/test3.xml");
	doc.parse<0>(xml_file.data());

	// Get the <world> node
	world_node = doc.first_node("world");

	// Get the <window> node and its attributes
	xml_node<>* window_node = world_node->first_node("window");
	width = std::stoi(window_node->first_attribute("width")->value());
	height = std::stoi(window_node->first_attribute("height")->value());

	// Get the <camera> node and its child nodes
	xml_node<>* camera_node = world_node->first_node("camera");
	Px = std::stof(camera_node->first_node("position")->first_attribute("x")->value());
	Py = std::stof(camera_node->first_node("position")->first_attribute("y")->value());
	Pz = std::stof(camera_node->first_node("position")->first_attribute("z")->value());
	Lx = std::stof(camera_node->first_node("lookAt")->first_attribute("x")->value());
	Ly = std::stof(camera_node->first_node("lookAt")->first_attribute("y")->value());
	Lz = std::stof(camera_node->first_node("lookAt")->first_attribute("z")->value());
	Ux = std::stof(camera_node->first_node("up")->first_attribute("x")->value());
	Uy = std::stof(camera_node->first_node("up")->first_attribute("y")->value());
	Uz = std::stof(camera_node->first_node("up")->first_attribute("z")->value());
	fov = std::stof(camera_node->first_node("projection")->first_attribute("fov")->value());
	near = std::stof(camera_node->first_node("projection")->first_attribute("near")->value());
	far = std::stof(camera_node->first_node("projection")->first_attribute("far")->value());
	LIGHT_NODE = world_node->first_node("lights");

	r = sqrt(pow(Lx - Px, 2) + pow(Ly - Py, 2) + pow(Lz - Pz, 2));
	beta = asin(Py / r);
	alpha = asin(Px/(r*cos(beta)));
	//printf("raio:%f, Px:%f, Py:%f, Pz:%f\n", r,Px,Py,Pz);
	// Get the <group> main node and its child nodes
	groupNode = world_node->first_node("group");

	//fazer aqui models :))
	storeModelFiles(groupNode);

	
	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height);
	glutCreateWindow("CG@DI-UM");

	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecial);

	glutMouseFunc(processMouseButtons);
	glutMotionFunc(processMouseMotion);
	// Register callbacks
	glutIdleFunc(renderScene);
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	glewInit();
	initGL();
	

	storeTextures(groupNode);
	// Enter the main loop
	glutMainLoop();

	return 0;
}
