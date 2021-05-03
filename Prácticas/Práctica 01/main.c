/* main.c
 */
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <unistd.h>

float t=0.5;
int state=0;

void drawSquadLine(){
  glClear(GL_COLOR_BUFFER_BIT);

  glBegin(GL_LINE_LOOP);
  glColor3f(1-t,0.8,0);
  glVertex3f(-1,0,-2);
  glColor3f(0,1-t,0.8);
  glVertex3f(-0.5,0,-2);
  glColor3f(0.8,0,1-t);
  glVertex3f(-0.5,0.5,-2);
  glColor3f(1-t,0.8,0);
  glVertex3f(-1,0.5,-2);
  glEnd();

  glBegin(GL_TRIANGLE_FAN);
  glColor3f(0.3+t,0,0.8);
  glVertex3f(0,0,-2);
  glColor3f(0.1,1-t,0);
  glVertex3f(0.5,0,-2);
  glColor3f(0.2+t,0.8,1-t);
  glVertex3f(0.5,0.5,-2);
  glColor3f(0.8,1-t,0.2);
  glVertex3f(0,0.5,-2);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1-t,0.8,0);
  glVertex3f(1,0,-2);
  glColor3f(0.8,1-t,0.1);
  glVertex3f(1.5,0,-2);
  glColor3f(0.8,0,1-t);
  glVertex3f(1.5,0.5,-2);
  glColor3f(0.2,1-t,0.8);
  glVertex3f(1,0.5,-2);
  glEnd();

  glFlush();
}

void drawCircle(){
  glClear(GL_COLOR_BUFFER_BIT);
   
  float x, y, theta;
  double R=0.3,G=0.7,B=0.4;
  glBegin(GL_TRIANGLE_FAN);
  for(int i = 0; i < 200; i++) {
  	if (R>1 || G>1 || B>1)
  	{
  		R=0.2;
  		G=0.1;
  		B=0.4;
  	}
  	glColor3f(R,G,B);
  	R+=0.3;
  	G+=0.3;
  	B+=0.3;
    theta = 1.0f * 3.1415926f * float(i) / 100.0f;
    x = cos(theta);
    y = sin(theta);
    glVertex3f(x-1, y,-3);
  }
  glEnd();

  glBegin(GL_LINE_LOOP);
  for(int i = 0; i < 200; i++) { 
    if (R>1 || G>1 || B>1)
  	{
  		R=0.2;
  		G=0.1;
  		B=0.4;
  	}
  	glColor3f(R,G,B);
  	R+=0.3;
  	G+=0.3;
  	B+=0.3;
    theta = 1.0f * 3.1415926f * float(i) / 100.0f;
    x = cos(theta);
    y = sin(theta);
    glVertex3f(x+1.5, y,-3);
  }
  glEnd();

  glFlush();
}

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

void myDisplay() {
  glClear(GL_COLOR_BUFFER_BIT);
  
  glBegin(GL_TRIANGLES);
  glColor3f(1,0,0);
  glVertex3f(-t,t,-3);
  glColor3f(0,1,0);
  glVertex3f(1,1,-3);
  glColor3f(0,0,1);
  glVertex3f(-1,1,-3);

  glColor3f(0,1,0);
  glVertex3f(-t,t,-3);
  glColor3f(1,0,0);
  glVertex3f(t,t,-3);
  glColor3f(0,0,1);
  glVertex3f(1,1,-3);

  glColor3f(0,1,0);
  glVertex3f(t,t,-3);
  glColor3f(0,0,1);
  glVertex3f(1,-1,-3);
  glColor3f(1,0,0);
  glVertex3f(1,1,-3);

  glColor3f(1,0,0);
  glVertex3f(t,t,-3);
  glColor3f(0,0,1);
  glVertex3f(t,-t,-3);
  glColor3f(0,1,0);
  glVertex3f(1,-1,-3);

  glColor3f(1,0,0);
  glVertex3f(t,-t,-3);
  glColor3f(0,1,0);
  glVertex3f(-1,-1,-3);
  glColor3f(0,0,1);
  glVertex3f(1,-1,-3);

  glColor3f(0,0,1);
  glVertex3f(t,-t,-3);
  glColor3f(0,1,0);
  glVertex3f(-t,-t,-3);
  glColor3f(1,0,0);
  glVertex3f(-1,-1,-3);

  glColor3f(1,0,0);
  glVertex3f(-t,-t,-3);
  glColor3f(0,1,0);
  glVertex3f(-1,1,-3);
  glColor3f(0,0,1);
  glVertex3f(-1,-1,-3);

  glColor3f(0,1,0);
  glVertex3f(-t,-t,-3);
  glColor3f(0,0,1);
  glVertex3f(-t,t,-3);
  glColor3f(1,0,0);
  glVertex3f(-1,1,-3);

  glEnd();
  glFlush();
}

void myUpdate() {
  usleep(50000);
  if(state==0)
  	t=t-0.01;
  else
  	t=t+0.01;
  if(t>0.6)
  	state=0;
  if(t<0.15)
  	state=1;
  glutPostRedisplay();
}

void myKeyboard(unsigned char key, int x, int y) {
	switch(key){
		case '1':
		glutDisplayFunc(drawSquadLine);
		break;
		case '2':
		glutDisplayFunc(drawCircle);
		break;
		case '3':
		glutDisplayFunc(myDisplay);
		break;
		case '4':
		exit(0);
	}
}

void myInit(const char *progname) {
	glutInitDisplayMode(GLUT_RGBA);		// modo RGBA
	glutInitWindowSize(1000, 500);		// ancho y largo
	glutInitWindowPosition(100, 100); 	// origen de la ventana
	glutCreateWindow(progname);
	glClearColor(0, 0, 0, 0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	myInit("Ejercicio 1");
	glutKeyboardFunc(myKeyboard);
	glutIdleFunc(myUpdate);
	glutDisplayFunc(drawSquadLine);
	glutReshapeFunc(myReshape);
	glutMainLoop();
	return 0;
}
