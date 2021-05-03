#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <time.h>

GLfloat vertices[][3] = {{-5.0,-5.0,-8.0},{5.0,-5.0,-8.0},
{5.0,5.0,-8.0}, {-5.0,5.0,-8.0}, {-5.0,-5.0,8.0},
{5.0,-5.0,8.0}, {5.0,5.0,8.0}, {-5.0,5.0,8.0},
{-6.0,5.0,9.0}, {-6.0,5.0,-9.0}, {6.0,5.0,-9.0},{6.0,5.0,9.0},
{-3.0,8.0,8.0}, {3.0,8.0,8.0}, {3.0,8.0,-8.0},{-3.0,8.0,-8.0}};

GLfloat colors[][3] = {{0.4,0.32,0.08},{0.5,0.4,0.1},
{0.5,0.4,0.0}, {0.4,0.32,0.0}, {0.4,0.32,0.08},
{0.5,0.5,0.1}, {0.5,0.5,0.0}, {0.5,0.5,0.0},
{0.7,0.2,0.2},{0.7,0.3,0.2},{0.7,0.3,0.2},{0.7,0.2,0.2},
{0.7,0.2,0.1},{0.7,0.2,0.1},{0.7,0.3,0.1},{0.7,0.3,0.1}};

void polygon(int a, int b, int c , int d)
{
 glBegin(GL_POLYGON);
  glColor3fv(colors[a]);
  glVertex3fv(vertices[a]);
  glColor3fv(colors[b]);
  glVertex3fv(vertices[b]);
  glColor3fv(colors[c]);
  glVertex3fv(vertices[c]);
  glColor3fv(colors[d]);
  glVertex3fv(vertices[d]);
 glEnd();
}

void casita()
{
 //paredes
 polygon(0,3,2,1);
 polygon(2,3,7,6);
 polygon(0,4,7,3);
 polygon(1,2,6,5);
 polygon(4,5,6,7);
 polygon(0,1,5,4);
 //techo
 polygon(8,9,10,11);
 polygon(8,12,15,9);
 polygon(11,10,14,13);
 polygon(8,11,13,12);
 polygon(9,15,14,10);
 polygon(12,13,14,15);
}

int girando[] = {0,0,0};
static GLfloat theta[] = {0.0,0.0,0.0};

void display()
{

 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

/* update viewer position in model-view matrix */

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-10.0f,10.0f,-10.0f,10.0f,10.0f,30.0f);
	gluLookAt(0,0,-25, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

/* rotate cube */

 glRotatef(theta[0], 1.0, 0.0, 0.0);
 glRotatef(theta[1], 0.0, 1.0, 0.0);
 glRotatef(theta[2], 0.0, 0.0, 1.0);
 casita();

 glFlush();
 glutSwapBuffers();
}

void animate(int freq){
	if (girando[0]>0){
		theta[0]+=3.0;
		if (theta[0]>360)
			theta[0]-=360;
	}
	if (girando[0]<0){
		theta[0]-=3.0;
		if (theta[0]<0)
			theta[0]+=360;
	}
	if (girando[1]>0){
		theta[1]+=3.0;
		if (theta[1]>360)
			theta[1]-=360;
	}
	if (girando[1]<0){
		theta[1]-=3.0;
		if (theta[1]<0)
			theta[1]+=360;
	}
	if (girando[2]>0){
		theta[2]+=3.0;
		if (theta[2]>360)
			theta[2]-=360;
	}
	if (girando[2]<0){
		theta[2]-=3.0;
		if (theta[2]<0)
			theta[2]+=360;
	}
	glutPostRedisplay();
	glutTimerFunc(60,animate,0);
}

void reshape ( int w, int h){
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-10.0f,10.0f,-10.0f,10.0f,-15.0f,20.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void keyboard (unsigned char key, int x, int y){
	switch(key){
		case 27:
			exit(0);
			break;
		case 'q':
			girando[2]=-1;
			break;
		case 'e':
			girando[2]=1;
			break;
		default:
			break;
	}
}
void keyboard2 (int key, int x, int y){
	switch(key){
		case GLUT_KEY_UP:
			girando[0]=1;
			break;
		case GLUT_KEY_DOWN:
			girando[0]=-1;
			break;
		case GLUT_KEY_RIGHT:
			girando[1]=1;
			break;
		case GLUT_KEY_LEFT:
			girando[1]=-1;
			break;
		default:
			break;
	}
}
void keyboard3 (unsigned char key, int x, int y){
	switch(key){
		case 'q':
			if (girando[2]<0) girando[2]=0;
			break;
		case 'e':
			if (girando[2]>0) girando[2]=0;
			break;
		default:
			break;
	}
}
void keyboard4 (int key, int x, int y){
	switch(key){
		case GLUT_KEY_UP:
			if (girando[0]>0) girando[0]=0;
			break;
		case GLUT_KEY_DOWN:
			if (girando[0]<0) girando[0]=0;
			break;
		case GLUT_KEY_RIGHT:
			if (girando[1]>0) girando[1]=0;
			break;
		case GLUT_KEY_LEFT:
			if (girando[1]<0) girando[1]=0;
			break;
		default:
			break;
	}
}
int main ( int argc, char** argv ){
	srand(time(NULL));
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize (600,600);
	glutInitWindowPosition (250,50);
	glutCreateWindow ("Teclado con OpenGL");
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.1,0.1,0.2,1);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboard2);
	glutKeyboardUpFunc(keyboard3);
	glutSpecialUpFunc(keyboard4);
	glutDisplayFunc(display);
	glutTimerFunc(60,animate,0);
	glutMainLoop ();
	return 0;
}