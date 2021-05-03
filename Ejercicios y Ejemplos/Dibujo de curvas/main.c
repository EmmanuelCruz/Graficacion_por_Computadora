/* main.c
 */
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include <unistd.h>

float puntos[4][3]={{0.4,0.6,-1},{0,-0.5,-1},{0.5,0.5,-1},{-0.5,-0.5,-1}};

void myKeyboard(unsigned char key, int x, int y) {
	if (key == 27) exit(0);
}

void myUpdate() {

}

void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_MAP1_VERTEX_3);

	glLoadIdentity();
//	gluLookAt(0,3,3,0,0,0,0,1,0);

	glColor3f(1,0,0);
	glMap1f(GL_MAP1_VERTEX_3,0.0,1.0,3,4,&puntos[0][0]);

	glBegin(GL_LINE_STRIP);
	for(int i=0; i<30; i++){
		glEvalCoord1f((float)i/30);
	}
	glEnd();

	glutSwapBuffers();
	glDisable(GL_DEPTH_TEST);
}

void myReshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (double)w / (double)h, 0.1, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void myInit(const char *progname) {	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1000, 700);		// ancho y largo
	glutInitWindowPosition(100, 100); 	// origen de la ventana
	glutCreateWindow(progname);
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	myInit("Ejercicio 2");
	glutKeyboardFunc(myKeyboard);
	glutDisplayFunc(myDisplay);
	glutIdleFunc(myUpdate);
	glutReshapeFunc(myReshape);
	glutMainLoop();
	return 0;
}
