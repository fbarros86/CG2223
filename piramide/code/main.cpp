#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>

float TransobjX=0, TransobjY = 0, TransobjZ = 0, angleobj = 0, RotObjX = 0, RotObjY = 0, RotObjZ = 0, ScaObjX = 1, ScaObjY = 1, ScaObjZ = 1, colorR = 0, colorG = 0, colorB = 0, TransCamX = 5.0, TransCamY = 5.0, TransCamZ = 5.0, RotCamX = 0, RotCamY = 0, RotCamZ = 0;

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
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
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(5.0,5.0,5.0, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

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
	

	// put the geometric transformations here
	glTranslatef(TransobjX, TransobjY, TransobjZ);
	glRotatef(angleobj, RotObjX,RotObjY,RotObjZ);
	glScalef(ScaObjX, ScaObjY, ScaObjZ);

	//Triangle1
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, 1.0f);
	glEnd();
	//Triangle2
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glEnd();
	//Triangle3
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, -1.0f);
	glEnd();
	//Triangle4
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glEnd();
	//BASE
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(1.0f, 0.0f, -1.0f);
	glEnd();

	// End of frame
	glutSwapBuffers();
}



// write function to process keyboard events
void controls(unsigned char key, int x, int y) {
	switch (key) {
		case('w'):{
			TransobjY += 0.5;
			break;
		}
		case('a'): {
			TransobjX -= 0.5;
			break;
		}
		case('s'): {
			TransobjY -= 0.5;
			break;
		}
		case('d'): {
			TransobjX += 0.5;
			break;
		}
		case('z'): {
			ScaObjX += 0.1;
			ScaObjY += 0.1;
			ScaObjZ += 0.1;

			break;
		}
		case('x'): {
			ScaObjX -= 0.1;
			ScaObjY -= 0.1;
			ScaObjZ -= 0.1;
			break;
		}
		case('i'): {
			angleobj += 15;
			RotObjY += 1;
			break;
		}
		case('j'): {
			angleobj -= 15;
			RotObjX += 1;
			break;
		}
		case('k'): {
			angleobj -= 15;
			RotObjY -= 1;
			break;
		}
		case('l'): {
			angleobj += 15;
			RotObjX -= 1;
			break;
		}
	}

	glutPostRedisplay();
}

void arrowcontrols(int key_code, int x, int y) {
	
}





int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	
// put here the registration of the keyboard callbacks
	glutKeyboardFunc(controls);
	glutSpecialFunc(arrowcontrols);


//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
