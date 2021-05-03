#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

//dimensiones del "cuarto"
int ancho=650;
int alto=400;
//dmiensiones de las figuras
int radCir=60;
int ladoCua=110;
//posicion de las figuras
int xCua=150;
int yCua=200;
int xCir=510;
int yCir=160;
//movimiento de las figuras
float vxCua=6.25f;
float vyCua=-6.25f;
float vxCir=-6.25f;
float vyCir=6.25f;

void rebotaMuros(){
	//Circulo
	if (xCir<radCir){
		xCir=radCir;
		vxCir *= -1;
	}
	if (xCir>ancho-radCir){
		xCir=ancho-radCir;
		vxCir *= -1;
	}
	if (yCir<radCir){
		yCir=radCir;
		vyCir *= -1;
	}
	if (yCir>alto-radCir){
		yCir=alto-radCir;
		vyCir *= -1;
	}
	//cuadrado
	if (xCua<0){
		xCua=0;
		vxCua *= -1;
	}
	if (xCua>ancho-ladoCua){
		xCua=ancho-ladoCua;
		vxCua *= -1;
	}
	if (yCua<0){
		yCua=0;
		vyCua *= -1;
	}
	if (yCua>alto-ladoCua){
		yCua=alto-ladoCua;
		vyCua *= -1;
	}
}
void rebotaFiguras(){
	//traslape horizontal
	if (xCir>xCua-radCir && xCir<xCua+ladoCua+radCir){
		//traslape vertical
		if (yCir>yCua-radCir && yCir<yCua+ladoCua+radCir){
			//colision horizontal
			if ((xCir<xCua+(ladoCua/2) && vxCir>vxCua)||(xCir>xCua+(ladoCua/2) && vxCir<vxCua)){
				vxCua*=-1;
				vxCir*=-1;
			}
			//colision vertical
			if ((yCir<yCua+(ladoCua/2) && vyCir>vyCua)||(yCir>yCua+(ladoCua/2) && vyCir<vyCua)){
				vyCua*=-1;
				vyCir*=-1;
			}
		}
	}
}
void animate(int param){
	xCir+=vxCir;
	yCir+=vyCir;
	xCua+=vxCua;
	yCua+=vyCua;
	rebotaMuros();
	rebotaFiguras();
	glLoadIdentity();
	glutPostRedisplay();
	glutTimerFunc(33,animate,0);
}
void dibujaCir(float numSeg){
	glColor3f(1,0,0);
	glPushMatrix();
	glTranslatef(xCir,yCir,0);
	float x, y, theta;
    glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0, 0);
    for(int i = 0; i <= numSeg; i++) { 
		theta = 6.283185f * (float)i / numSeg;
		x = radCir*cos(theta);
		y = radCir*sin(theta);
		glVertex2f(x, y);
    }
	glEnd();
	glPopMatrix();
}
void dibujaCua(){
	glColor3f(0,1,0);
	glPushMatrix();
	glTranslatef(xCua,yCua,0);
    glBegin(GL_TRIANGLE_FAN);
		glVertex2f(0, 0);
		glVertex2f(ladoCua, 0);
		glVertex2f(ladoCua, ladoCua);
		glVertex2f(0, ladoCua);
	glEnd();
	glPopMatrix();
}
void display ( void ){
	glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glOrtho(0, ancho, 0, alto, -10, 10);
	
	dibujaCua();
	dibujaCir(30.0f);
    glutSwapBuffers();
}
void reshape ( int w, int h){
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
int main ( int argc, char** argv ){
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize (ancho,alto);
	glutInitWindowPosition (100,50);
	glutCreateWindow (" ");
	glClearColor(0.1,0.1,0.2,1);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutTimerFunc(33,animate,0);
	glutMainLoop ();
	return 0;
}