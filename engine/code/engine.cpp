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
#include <cmath>
#include "engine.h"


int width, height, size;
int startTime = glutGet(GLUT_ELAPSED_TIME);
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
	float aspectRatio = (float)w / (float)h;
	gluPerspective(fov, aspectRatio, near, far);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void multMatrixVector(float* m, float* v, float* res) {

	for (int j = 0; j < 4; ++j) {
		res[j] = 0;
		for (int k = 0; k < 4; ++k) {
			res[j] += v[k] * m[j * 4 + k];
		}
	}
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
		-10000.0f, 0.0f, 0.0f);
	glVertex3f(10000.0f, 0.0f, 0.0f);
	// Y Axis in Green
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f,
		-10000.0f, 0.0f);
	glVertex3f(0.0f, 10000.0f, 0.0f);
	// Z Axis in Blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f,
		-10000.0f);
	glVertex3f(0.0f, 0.0f, 10000.0f);
	glEnd();
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

void getGlobalCatmullRomPoint(float gt, float* pos, float* deriv, int point_count, std::vector<float*> p) {

	float t = gt * point_count; // this is the real global t
	int index = floor(t);  // which segment
	t = t - index; // where within  the segment

	// indices store the points
	int indices[4];
	indices[0] = (index + point_count - 1) % point_count;
	indices[1] = (indices[0] + 1) % point_count;
	indices[2] = (indices[1] + 1) % point_count;
	indices[3] = (indices[2] + 1) % point_count;

	getCatmullRomPoint(t, p[indices[0]], p[indices[1]], p[indices[2]], p[indices[3]], pos, deriv);
}

using namespace rapidxml;
xml_node<>* groupNode;

void drawFigure(std::string file_name) {
	std::ifstream model_file("../models/" + file_name);
	if (!model_file.is_open()) {
		std::cerr << "Error: Failed to open model file " << file_name << std::endl;
	}
	float value1, value2, value3;
	glBegin(GL_TRIANGLES);
	while (model_file >> value1 >> value2 >> value3) {
		glVertex3f(value1, value2, value3);
	}
	glEnd();
}

void animateRotate(float x, float y, float z, float time) {
	float elapsedTime = (glutGet(GLUT_ELAPSED_TIME) - startTime)/ 1000.0f;
	float rotation = 360.0f * fmod(elapsedTime,time) / time;
	glRotatef(rotation, x, y, z);
	
}

void animateTranslate(std::vector<float*> points, float duration, bool isAligned) {
	float elapsedTime = (glutGet(GLUT_ELAPSED_TIME) - startTime) / 1000.0f;
	float time_loop = fmod(elapsedTime, duration);
	float gt = time_loop/duration;
	int num_points = points.size();
	float pos[3], deriv[3];
	getGlobalCatmullRomPoint(gt, pos, deriv, num_points, points);
	glTranslatef(pos[0], pos[1], pos[2]);
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
						bool isAligned = (align=="True");
						std::vector<float*> points;
						for (xml_node<>* point = childNode->first_node(); point; point = point->next_sibling()){
							float pointX = std::stof(point->first_attribute("x")->value());
    						float pointY = std::stof(point->first_attribute("y")->value());
    						float pointZ = std::stof(point->first_attribute("z")->value());
							float ps[3] = { pointX,pointY,pointZ };
							points.push_back(ps);
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
			// Process models node
			for (xml_node<>* childNode = node->first_node(); childNode; childNode = childNode->next_sibling()) {
				std::string childNodeName = childNode->name();
				if (childNodeName == "model") {
					// Process model node
					std::string fileName = childNode->first_attribute("file")->value();
					drawFigure(fileName);
				}
			}
		}
		else if (nodeName == "group") {
			parseGroup(node);
		}
	}
	glPopMatrix();
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
	parseGroup(groupNode);
	
	glutSwapBuffers();
}





int main(int argc, char** argv) {
	xml_document<> doc;
	xml_node<>* world_node;

	// Read the XML file
	file<> xml_file("../config/test_files_phase_3/test_3_1.xml");
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

	// Get the <group> main node and its child nodes
	groupNode = world_node->first_node("group");
	
	
	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height);
	glutCreateWindow("CG@DI-UM");

	// Register callbacks
	glutIdleFunc(renderScene);
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	// Enable depth testing and backface culling
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// Enter the main loop
	glutMainLoop();

	return 0;
}
