#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

float r = 5, alpha = M_PI / 4, beta = M_PI / 4;
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

void drawPlane(float size, int divs){
	float x = -size / 2;
	float z;
	for (int i = 0; i < divs; i++) {
		z=size / 2;
		for (int j = 0; j < divs; j++){
			glBegin(GL_TRIANGLES);
			glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3f(x, 0.0f, z);
			glVertex3f(x+size/divs, 0.0f, z);
			glVertex3f(x, 0.0f, z-size/divs);
			glEnd();
			glBegin(GL_TRIANGLES);
			glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3f(x+size/divs, 0.0f, z-size/divs);
			glVertex3f(x, 0.0f, z - size / divs);
			glVertex3f(x + size / divs, 0.0f, z);
			glEnd();
			z -= size / divs;
		}
		x += size / divs;
	}
	
}

void drawBox(float x, float divperedge) {
	// draw bottom face
	glPushMatrix();
	glTranslatef(0, -x / 2,0);
	glRotatef(180, 1, 0, 0);
	drawPlane(x, divperedge);
	glPopMatrix();

	// draw front face
	glPushMatrix();
	glTranslatef(0, 0, -x / 2);
	glRotatef(90, 1, 0, 0);
	glRotatef(180, 0, 0, 1);
	drawPlane(x, divperedge);
	glPopMatrix();

	// draw back face
	glPushMatrix();
	glTranslatef(0, 0, x / 2);
	glRotatef(90, 1, 0, 0);
	drawPlane(x, divperedge);
	glPopMatrix();

	// draw left face
	glPushMatrix();
	glTranslatef(-x / 2, 0, 0);
	glRotatef(90, 0, 0, 1);
	drawPlane(x, divperedge);
	glPopMatrix();

	// draw right face
	glPushMatrix();
	glTranslatef(x / 2, 0, 0);
	glRotatef(90, 0, 0, 1);
	glRotatef(180, 0, 0, 1);
	drawPlane(x, divperedge);
	glPopMatrix();

	// draw top face
	glPushMatrix();
	glTranslatef(0, x/ 2, 0);
	drawPlane(x, divperedge);
	glPopMatrix();
}

void drawSphere(float radius, int slices, int stacks) {
	float x1, x2, z1, z2, r=radius, y=0, next_r, next_x1, next_x2, next_z1, next_z2, next_y, alpha=0, beta=0, next_alpha, next_beta;
	for (int i = 0; i < stacks/2; i++) {
		next_r = r - radius / (stacks / 2);
		//next_y = sqrt(radius* radius - next_r *next_r);
		alpha = 0;
		next_beta = beta + ((2 * M_PI) / stacks);
		//next_y = r * sin(beta + ((2 * M_PI) / stacks));
		next_y = y + radius/stacks;
		//r* cos(beta)* sin(alpha), r* sin(beta), r* cos(beta)* cos(alpha)
		for (int j = 0; j < slices; j++) {
			next_alpha = alpha + ((2 * M_PI) / slices);
			//x1 = r * sin(j * 2 * M_PI / slices);
			//x2 = r * sin((j + 1) * 2 * M_PI / slices);
			x1 = r * cos(beta) * sin(alpha);
			x2 = r * cos(beta) * sin(next_alpha);
			//z1 = r * cos(j * 2 * M_PI / slices);
			//z2 = r * cos((j + 1) * 2 * M_PI / slices);
			z1 = r * cos(beta) * cos(alpha);
			z2 = r * cos(beta) * cos(next_alpha);
			//next_x1 = next_r * sin(j * 2 * M_PI / slices);
			//next_x2 = next_r * sin((j + 1) * 2 * M_PI / slices);
			next_x1 = r * cos(next_beta) * sin(alpha);
			next_x2 = r * cos(next_beta) * sin(next_alpha);

			//next_z1 = next_r * cos(j * 2 * M_PI / slices);
			//next_z2 = next_r * cos((j + 1) * 2 * M_PI / slices);

			next_z1 = r * cos(next_beta) * cos(alpha);
			next_z2 = r * cos(next_beta) * cos(next_alpha);

			glBegin(GL_TRIANGLES);
			glVertex3f(x1, y, z1);
			glVertex3f(x2, y, z2);
			glVertex3f(next_x1, next_y, next_z1);
			glEnd();

			glBegin(GL_TRIANGLES);
			glVertex3f(x2, y, z2);
			glVertex3f(next_x2, next_y, next_z2);
			glVertex3f(next_x1, next_y, next_z1);
			glEnd();

			glBegin(GL_TRIANGLES);
			glVertex3f(x2, -y, z2);
			glVertex3f(x1, -y, z1);
			glVertex3f(next_x1, -next_y, next_z1);
			glEnd();

			glBegin(GL_TRIANGLES);
			glVertex3f(next_x1, -next_y, next_z1);
			glVertex3f(next_x2, -next_y, next_z2);
			glVertex3f(x2, -y, z2);
			glEnd();
			alpha = alpha + ((2 * M_PI) / slices);
		}
			beta = beta + ((2 * M_PI) / stacks);
		y = next_y;
		//r = next_r;
	}
		

}

void drawSphere2(float radius, int slices, int stacks) {
	float x1, x2, z1, z2, r = radius, y = 0, next_r, next_x1, next_x2, next_z1, next_z2, next_y, alpha = 0, beta = 0, next_alpha, next_beta;
	for (int i = 0; i < stacks / 2; i++) {
		next_r = r - radius / (stacks / 2);
		next_y = sqrt(radius* radius - next_r *next_r);
		alpha = 0;
		//next_beta =
			next_y = r * sin(beta + ((2 * M_PI) / stacks));
		//r* cos(beta)* sin(alpha), r* sin(beta), r* cos(beta)* cos(alpha)
		for (int j = 0; j < slices; j++) {
			next_alpha = alpha + ((2 * M_PI) / slices);
			x1 = r * sin(j * 2 * M_PI / slices);
			x2 = r * sin((j + 1) * 2 * M_PI / slices);
			//x1 = r * cos(beta) * sin(alpha);
			//x2 = r * cos(beta) * sin(next_alpha);
			z1 = r * cos(j * 2 * M_PI / slices);
			z2 = r * cos((j + 1) * 2 * M_PI / slices);
			//z1 = r * cos(beta) * cos(alpha);
			//z2 = r * cos(beta) * cos(next_alpha);
			next_x1 = next_r * sin(j * 2 * M_PI / slices);
			next_x2 = next_r * sin((j + 1) * 2 * M_PI / slices);
			//next_x1 = r * cos(next_beta) * sin(alpha);
			//next_x2 = r * cos(next_beta) * sin(next_alpha);

			//next_z1 = next_r * cos(j * 2 * M_PI / slices);
			//next_z2 = next_r * cos((j + 1) * 2 * M_PI / slices);

			next_z1 = r * cos(next_beta) * cos(alpha);
			next_z2 = r * cos(next_beta) * cos(next_alpha);

			glBegin(GL_TRIANGLES);
			glVertex3f(x1, y, z1);
			glVertex3f(x2, y, z2);
			glVertex3f(next_x1, next_y, next_z1);
			glEnd();

			glBegin(GL_TRIANGLES);
			glVertex3f(x2, y, z2);
			glVertex3f(next_x2, next_y, next_z2);
			glVertex3f(next_x1, next_y, next_z1);
			glEnd();

			glBegin(GL_TRIANGLES);
			glVertex3f(x2, -y, z2);
			glVertex3f(x1, -y, z1);
			glVertex3f(next_x1, -next_y, next_z1);
			glEnd();

			glBegin(GL_TRIANGLES);
			glVertex3f(next_x1, -next_y, next_z1);
			glVertex3f(next_x2, -next_y, next_z2);
			glVertex3f(x2, -y, z2);
			glEnd();
			alpha = alpha + ((2 * M_PI) / slices);
		}
		beta = beta + ((2 * M_PI) / stacks);
		y = next_y;
		//r = next_r;
	}


}


void drawCylinder(float radius, float height, int slices) {
	float x1, z1, x2, z2, h;
	// put code to draw cylinder in here
	for (int i = 0; i < slices; i++)
	{
		x1 = radius * sin(i * 2 * M_PI / slices);
		x2 = radius * sin((i + 1) * 2 * M_PI / slices);
		z1 = radius * cos(i * 2 * M_PI / slices);
		z2 = radius * cos((i + 1) * 2 * M_PI / slices);
		h = height / 2;

		glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, -h, 0.0f);
		glVertex3f(x2, -h, z2);
		glVertex3f(x1, -h, z1);
		glEnd();

		glBegin(GL_TRIANGLES);
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(x1, h, z1);
		glVertex3f(x2, h, z2);
		glVertex3f(0.0f, h, 0.0f);
		glEnd();

		glBegin(GL_TRIANGLES);
		glColor3f(1.0f * (i % 2), 0.0f, 1.0f);
		glVertex3f(x1, h, z1);
		glVertex3f(x1, -h, z1);
		glVertex3f(x2, -h, z2);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex3f(x1, h, z1);
		glVertex3f(x2, -h, z2);
		glVertex3f(x2, h, z2);
		glEnd();
	}
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
	gluLookAt(r * cos(beta) * sin(alpha), r * sin(beta), r * cos(beta) * cos(alpha),
		0.0, 0.0, 0.0,
		0.0f, 1.0f, 0.0f);


	drawAxis();
	glPolygonMode(GL_FRONT, GL_LINE);
	glColor3f(1.0f, 1.0f, 1.0f);

	//drawCylinder(1, 3, 3000);
	//drawPlane(2,30);
	//drawBox(2, 3);
	drawSphere(1,10,10);

	// End of frame
	glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {

	switch (c) {
	case('w'): {
		if (beta <= 1.5){
			beta += 0.1;
		}
		break;
	}
	case('a'): {
		alpha -= 0.1;
		break;
	}
	case('s'): {
		if (-1.5 <= beta) {
			beta -= 0.1;
		}
		break;
	}
	case('d'): {
		alpha += 0.1;
		break;
	}
	case('z'): {
		r -= 0.1;
		break;
	}
	case('x'): {
		r += 0.1;
		break;
	}
	}

	glutPostRedisplay();

}


void processSpecialKeys(int key, int xx, int yy) {

	// put code to process special keys in here

}


int main(int argc, char** argv) {

	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("CG@DI-UM");

	// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

	//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}
