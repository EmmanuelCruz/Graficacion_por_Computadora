/* main.c
 */
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <unistd.h>

#define PI 3.14159265

// Globals.
static float R = 1.2; // Radius of hemisphere.
static int p = 15; // Number of longitudinal slices.
static int q = 15; // Number of latitudinal slices.
static float Xangle = 0.0, Yangle = 0.0, Zangle = 0.0; // Angles to rotate hemisphere.

float elemX=0;
float elemY=0;
float elemZ=-5;

void myReshape(int w, int h) {
  glViewport(0,0,w,h); // Especifica tamaño de la ventana.
  glMatrixMode(GL_PROJECTION); // Cambia la matriz para modificar.
  glLoadIdentity();
  float ar=(float) w/(float) h; // La razón
  gluPerspective(60.0, ar, 0.0, 20.0); // Perepectiva. Ángulo del punto más abajo y arriba.
  // Aspecto. zNear, zPlane.
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void drawRamp(){
	glColor3f(1,1,0);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(0,0,-5);
	glVertex3f(0,1.2,-5);
	glVertex3f(1.2,1.2,-5);
	glVertex3f(1.2,0,-5);
	glEnd();
}

void drawBall(){
	glPushMatrix();
	// Commands to turn the hemisphere.
	glRotatef(Zangle, 0.0, 0.0, 1.0);
	glRotatef(Yangle, 0.0, 1.0, 0.0);
	glRotatef(Xangle, 1.0, 0.0, 0.0);

	int  i, j;
	// Array of latitudinal triangle strips, each parallel to the equator, stacked one
	// above the other from the equator to the north pole.
	for (j = -q; j < q; j++){
		// One latitudinal triangle strip.
		glBegin(GL_TRIANGLE_STRIP);
		for (i = 0; i <= p; i++){
			if(j>=0)
				glColor3f(1,0,0);
			else
				glColor3f(0,1,0);
			
			glVertex3f((R * cos((float)(j + 1) / q * PI / 2.0) * cos(2.0 * (float)i / p * PI))+elemX,
				(R * sin((float)(j + 1) / q * PI / 2.0))+elemY,
				(-R * cos((float)(j + 1) / q * PI / 2.0) * sin(2.0 * (float)i / p * PI))+elemZ);
			glVertex3f((R * cos((float)j / q * PI / 2.0) * cos(2.0 * (float)i / p * PI))+elemX,
				(R * sin((float)j / q * PI / 2.0))+elemY,
				(-R * cos((float)j / q * PI / 2.0) * sin(2.0 * (float)i / p * PI))+elemZ);
		}
		glEnd();
		glPopMatrix();
	}

}

void myDisplay() {

	glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glLoadIdentity();

	drawBall();
	drawRamp();

	glutSwapBuffers();

}

void myUpdate() {

}

void myKeyboard(unsigned char key, int x, int y) {
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case 'P':
		p += 1;
		glutPostRedisplay();
		break;
	case 'p':
		if (p > 3) p -= 1;
		glutPostRedisplay();
		break;
	case 'Q':
		q += 1;
		glutPostRedisplay();
		break;
	case 'q':
		if (q > 3) q -= 1;
		glutPostRedisplay();
		break;
	case 'x':
		Xangle += 5.0;
		if (Xangle > 360.0) Xangle -= 360.0;
		glutPostRedisplay();
		break;
	case 'X':
		Xangle -= 5.0;
		if (Xangle < 0.0) Xangle += 360.0;
		glutPostRedisplay();
		break;
	case 'y':
		Yangle += 5.0;
		if (Yangle > 360.0) Yangle -= 360.0;
		glutPostRedisplay();
		break;
	case 'Y':
		Yangle -= 5.0;
		if (Yangle < 0.0) Yangle += 360.0;
		glutPostRedisplay();
		break;
	case 'z':
		Zangle += 5.0;
		if (Zangle > 360.0) Zangle -= 360.0;
		glutPostRedisplay();
		break;
	case 'Z':
		Zangle -= 5.0;
		if (Zangle < 0.0) Zangle += 360.0;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

void myInit(const char *progname) {
	glutInitDisplayMode(GLUT_RGBA);		// modo RGBA
	glutInitWindowSize(1000, 500);		// ancho y largo
	glutInitWindowPosition(100, 100); 	// origen de la ventana
	glutCreateWindow(progname);
	glClearColor(1, 1, 1, 1);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	myInit("Ejercicio 2");
	glutKeyboardFunc(myKeyboard);
	//glutIdleFunc(myUpdate);
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myReshape);
	glutMainLoop();
	return 0;
}
