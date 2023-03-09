#include <iostream>
#include "../libs/rapidxml.hpp"
#include "../libs/rapidxml_utils.hpp"
#include "../libs/rapidxml_print.hpp"
#include "../libs/rapidxml_iterators.hpp"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include "engine.h"


int width, height, size;
float Px, Py, Pz, Lx, Ly, Lz, Ux, Uy, Uz, fov, near, far;
float* buffer;
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
	gluPerspective(45.0f, ratio, 1.0f, 1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
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
	//EIXOS
	glBegin(GL_LINES);
	// X axis in red
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(
		-100.0f, 0.0f, 0.0f);
	glVertex3f(100.0f, 0.0f, 0.0f);
	// Y Axis in Green
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f,
		-100.0f, 0.0f);
	glVertex3f(0.0f, 100.0f, 0.0f);
	// Z Axis in Blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f,
		-100.0f);
	glVertex3f(0.0f, 0.0f, 100.0f);
	glEnd();
}



void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(Px, Py, Pz,
		Lx, Ly, Lz,
		Ux, Uy, Uz);
	//std::cout << aspect;

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	drawAxis();
	glColor3f(1.0f, 1.0f, 1.0f);
	drawTriangles(buffer,size);
	
	glutSwapBuffers();
}



using namespace rapidxml;
int main(int argc, char** argv) {
	xml_document<> doc;
	xml_node<>* world_node;

	// Read the XML file
	file<> xml_file("../config/test_files_phase_1/test_1_5.xml");
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

	// Get all <model> nodes and their attributes
	xml_node<>* models_node = world_node->first_node("group")->first_node("models");

	int num_coords = 0;
	for (xml_node<>* model_node = models_node->first_node("model"); model_node; model_node = model_node->next_sibling()) {
		std::string file_name = model_node->first_attribute("file")->value();

		// Open the model file
		std::ifstream model_file("../models/" + file_name);
		if (!model_file.is_open()) {
			std::cerr << "Error: Failed to open model file " << file_name << std::endl;
			return -1;
		}

		// Read the coordinates from the model file and update the total number of coordinates
		float coord;
		while (model_file >> coord) {
			++num_coords;
		}
	}
	size = num_coords;
	// Allocate a buffer to hold all the model coordinates as a simple array of floats
	buffer = new float[size];
	//std::cout << Px << " " << Py << " " << Pz << "\n";
	//std::cout << Lx << " " << Ly << " " << Lz << "\n";
	//std::cout << Ux << " " << Uy << " " << Uz << "\n";




	// Read the model coordinates and store them in the buffer
	int idx = 0;
	for (xml_node<>* model_node = models_node->first_node("model"); model_node; model_node = model_node->next_sibling()) {
		std::string file_name = model_node->first_attribute("file")->value();

		// Open the model file
		//std::cout << file_name;
		std::ifstream model_file("../models/"+file_name);
		if (!model_file.is_open()) {
			std::cerr << "Error: Failed to open model file " << file_name << std::endl;
			return -1;
		}
		float value;
		while (model_file >> value) {
			buffer[idx] = value;
			++idx;
		}
	}
	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height);
	glutCreateWindow("CG@DI-UM");

	// Set the projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
	gluPerspective(fov, aspectRatio, near, far);

	// Register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	// Enable depth testing and backface culling
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// Enter the main loop
	glutMainLoop();

	return 0;
}
