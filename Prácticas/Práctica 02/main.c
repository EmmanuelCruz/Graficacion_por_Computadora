/* main.c
 */
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include <unistd.h>

#define PI 3.14159265

/* Cantidad de tríangulos en longitud y nivel de las esferas.*/
static int q=30;
static int p=30;

/* Angulo de rotación de las esferas en cierto eje.*/
int rPlaneta=0;

/* Angulo de rotación de las lunas en cierto eje.*/
int rLunas=180;

/* Ancho de la caja de la animación 3.*/
int ancho=9;
/* Largo de la caja de la animación 3.*/
int largo=5;

/* Indicar para saber si una esfera se dirige a lado positivo sobre x.*/
bool der=true;
/* Indicar para saber si una esfera se dirige a lado negativo sobre z.*/
bool arriba=true;

/* Posición de la esfera de la animación 3.*/
double posX=1;
double posY=1;

/* Angulo de rotación de una esfera. */
double rBall=0;

/* Posición de la esfera de la animacion 1.*/
double posY1=8;
double posZ1=-ancho-7;

/* Opción para saber cuál animación mostrar.*/
int op=1;

/**
* Permite dibujar una esfera.
*/
void drawSphere(double x, double y, double z, double R, double r1, double g1, double b1, double r2, double g2, double b2){
	int  i, j;
	for (j = -q; j < q; j++){
		// One latitudinal triangle strip.
		if(j>0)
			glColor3f(r1,g1,b1);
		else
			glColor3f(r2,g2,b2);
		glBegin(GL_TRIANGLE_STRIP);
		for (i = 0; i <= p; i++){
			glVertex3f((R * cos((float)(j + 1) / q * PI / 2.0) * cos(2.0 * (float)i / p * PI))+x,
				(R * sin((float)(j + 1) / q * PI / 2.0))+y,
				(-R * cos((float)(j + 1) / q * PI / 2.0) * sin(2.0 * (float)i / p * PI))+z);
			glVertex3f((R * cos((float)j / q * PI / 2.0) * cos(2.0 * (float)i / p * PI))+x,
				(R * sin((float)j / q * PI / 2.0))+y,
				(-R * cos((float)j / q * PI / 2.0) * sin(2.0 * (float)i / p * PI))+z);
		}
		glEnd();
	}
}

/**
* Permite al usuario elegir la animación a ver.
*/
void myKeyboard(unsigned char key, int x, int y) {
	if (key == 27) exit(0);
	switch(key){
		case '1':
		op=1;
		break;
		case '2':
		op=2;
		break;
		case '3':
		op=3;
		break;
	}
}

/**
* Actualiza los valores de cada iteración.
*/
void myUpdate() {
	/* Mueve la esfera hacia abajo sobre y.*/
	posY1-=0.1;
	/* Si se llega a la base se deja de la posición de la esfera.*/
	if(posY1<=0)
		posY1=0;

	/* Mueve a la esfera hacia los valores positivos del espacio en z.*/
	posZ1+=0.15;
	/* Si la esfera terminó de recorrer la rampa la dejamos en el lugar de inicio. */
	if(posZ1>=largo*2){
		posZ1=-ancho-7;
		posY1=7;
	}

	/* Rotamos la esfera con valores incrementales en un intervalo de 0-360.*/
	rBall+=15;
	if(rBall>=360)
		rBall=0;

	/* Rotamos la esfera con valores incrementales en un intervalo de 0-360.*/
	rPlaneta+=1;
	if(rPlaneta>=360)
		rPlaneta=0;

	/* Rotamos la esfera con valores incrementales en un intervalo de 0-360.*/
	rLunas+=4;
	if(rLunas>=360)
		rLunas=0;
	
	/* Si la esfera de la animación 3 va hacia la derecha la movemos en valores positivos en x.
	 * De lo contrario la movemos en valores negativos en x*/
	if(der)
		posX+=0.2;
	else
		posX-=0.2;

	/* Si la esfera de la animación 3 va hacia la arriba la movemos en valores negativos en z.
	 * De lo contrario la movemos en valores positivos en z*/
	if(arriba)
		posY+=0.2;
	else
		posY-=0.2;

	/* Si la esfera toca el borde derecho hacemos el rebote y la mandamos a lado izquierdo.*/
	if(posX>ancho)
		der=false;

	/* Si la esfera toca el borde superior hacemos el rebote y la mandamos a lado inferior.*/
	if(posY>largo)
		arriba=false;

	/* Si la esfera toca el borde izquierdo hacemos el rebote y la mandamos a lado derecho.*/
	if(posX<(-ancho))
		der=true;

	/* Si la esfera toca el borde inferior hacemos el rebote y la mandamos a lado superior.*/
	if(posY<(-largo))
		arriba=true;
	glutPostRedisplay();
}

void animation1(){
	/* Movemos el espacio con centro en 0,0,-17*/
	glPushMatrix();
	glTranslatef(0,0,-17);
	
	/* Se dibuja la rampa.*/
	glColor3f(0,1,0);
	glBegin(GL_QUADS);

	/* Base de la rampa.*/
	glVertex3f(largo,-1,ancho);
	glVertex3f(largo,-1,-ancho);
	glVertex3f(-largo,-1,-ancho);
	glVertex3f(-largo,-1,ancho);

	/* Rampa.*/
	glColor3f(0,0,1);
	glVertex3f(largo,-1,-ancho);
	glVertex3f(largo,7,-ancho-7);
	glVertex3f(-largo,7,-ancho-7);
	glVertex3f(-largo,-1,-ancho);
	glEnd();

	/* Se dibuja la esfera.*/
	glPushMatrix();
	/* Primero se traslada a la posición actual de la esfera en la iteración n.*/
	glTranslatef(0,posY1,posZ1);
	/* Se rota para simular que la esfera está rondando sobre la rampa.*/
	glRotatef(rBall,1,0,0);
	drawSphere(0,0,0,1,1,0.5,0,0.2,0.6,0.8);
	glPopMatrix();
	
	/* Se vuelve al espacio original con centro en 0,0,0.*/
	glPopMatrix();

}

void animation2(){
	glPushMatrix();
	/* Se mueve a un espacio con centro en 0,0,-17.*/
	glTranslatef(0,0,-17);

	/* Se dibuja una esfera de color amarillo en el centro del espacio simulando el sol.*/
	drawSphere(0,0,0,1,1,1,0,1,1,0);

	/* Sobre el mismo origen se rota el espacio. La llamaremos ROTACIÓN1*/
	glRotatef(rPlaneta,0,1,0);

	/* Se traslada la siguiente esfera. (A estas se les aplica la rotación anterior).*/
	glTranslatef(9,0,0);

	/* Se dibuja una esfera que rota sobre su propio eje (Esta es afectada por la ROTACION1).*/
	glPushMatrix();
	glRotatef(rPlaneta,1,0,0);
	/* ESFERA1*/
	drawSphere(0,0,0,1,0,0,1,0,1,0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(rLunas,1,0,0);
	/* Se dibuja una esfera que rota al rededor de la ESFERA1 (Esta también es afectada por la ROTACION1).*/
	drawSphere(0,0,3,0.5,1,0,1,1,0,0);
	glPopMatrix();


	glPushMatrix();
	glRotatef(rPlaneta,0,1,0);
	glPushMatrix();
	glRotatef(rPlaneta,1,0,0);
	/* Se dibuja una esfera que rota sobre su propio eje y además al rededor de la ESFERA1
	(Esta también es afectada por la ROTACION1).*/
	drawSphere(3,0,0,0.5,1,0,1,1,0,0);
	glPopMatrix();
	glPopMatrix();

	/* Se regresa al espacio inicial con origen en 0,0,0.*/
	glPopMatrix();
}

void animation3(){
	glPushMatrix();
	/* Se traslada al espacio con origen en 0,0,-17.*/
	glTranslatef(0,0,-17);

	/* Se dibuja la caja en la cuál estará rebotando la esfera. */
	glColor3f(1,0,1);
	glBegin(GL_QUADS);
	/* Cara trasera de la caja.*/
	glVertex3f(ancho+1,-1,-largo-1);
	glVertex3f(ancho+1,1,-largo-1);
	glVertex3f(-ancho-1,1,-largo-1);
	glVertex3f(-ancho-1,-1,-largo-1);

	/* Cara derecha de la caja.*/
	glColor3f(1,0,0);
	glVertex3f(ancho+1,-1,-largo-1);
	glVertex3f(ancho+1,-1,largo+1.5);
	glVertex3f(ancho+1,1,largo+1.5);
	glVertex3f(ancho+1,1,-largo-1);

	/* Cara izquierda de la caja.*/
	glColor3f(0,1,1);
	glVertex3f(-ancho-1,-1,-largo-1);
	glVertex3f(-ancho-1,1,-largo-1);
	glVertex3f(-ancho-1,1,largo+1.5);
	glVertex3f(-ancho-1,-1,largo+1.5);

	/* Base de la caja.*/
	glColor3f(1,1,0);
	glVertex3f(ancho+1,-1,largo+1.5);
	glVertex3f(ancho+1,-1,-largo-1);
	glVertex3f(-ancho-1,-1,-largo-1);
	glVertex3f(-ancho-1,-1,largo+1.5);
	
	/* Cara frontal de la caja. */
	glColor3f(1,0.5,1);
	glVertex3f(ancho+1,-1,largo+1.5);
	glVertex3f(ancho+1,1,largo+1.5);
	glVertex3f(-ancho-1,1,largo+1.5);
	glVertex3f(-ancho-1,-1,largo+1.5);
	glEnd();

	glPushMatrix();
	/* Se dibuja la esfera afectando la posición X y Z pero Y nunca se modifica.*/
	glTranslatef(posX,0,posY);
	/* Se aplican las direcciones pertinentes para simular el efecto de giro.
	* (Arriba/abajo y derecha/izquierda en todas las combinaciones posibles).*/
	if(der)
		if(arriba)
			glRotatef(rBall,1,0,-1);
		else
			glRotatef(rBall,-1,0,-1);
	else
		if(arriba)
			glRotatef(rBall,1,0,1);
		else
			glRotatef(rBall,-1,0,1);
	/* Se subja la esfera.*/
	drawSphere(0,0,0,1,1,0,0,0,1,0);
	glPopMatrix();

	/* Se regresa al espacio inicial con origen en 0,0,0.*/
	glPopMatrix();
}

void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	/* Segun la opción se muestra la animación correspondiente.*/
	switch(op){
		case 1:
		glLoadIdentity();
		/* Se modifica la posición de la camara con ojo en 13,13,5.*/
		gluLookAt(13,13,5,0,0,-17,0,1,0);
		animation1();
		break;
		case 2:
		glLoadIdentity();
		/* Se modifica la posición de la camara con ojo en 0,0,0.
		(Esto por no verse afectado por otros cambios en LookAt en otras animaciones)*/
		gluLookAt(0,0,0,0,0,-17,0,1,0);
		animation2();
		break;
		case 3:
		glLoadIdentity();
		/* Se modifica la posición de la camara con ojo en 0,9,5.*/
		gluLookAt(0,9,5,0,0,-17,0,1,0);
		animation3();
	}
	
	glutSwapBuffers();
	glDisable(GL_DEPTH_TEST);
}

void myReshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (double)w / (double)h, 0.1, 40.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void myInit(const char *progname) {	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1000, 700);		// ancho y largo
	glutInitWindowPosition(100, 100); 	// origen de la ventana
	glutCreateWindow(progname);
	glClearColor(0, 0, 0, 0.0);
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
