#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// NOMBRE: EMMANUEL CRUZ HERNÁNDEZ.
// No. CUENTA: 314272588.
// TAREA 1: PONG.

// Dimensiones del espacio del Pong.
int ancho=1000;
int alto=600;

// Radio de la pelota.
int radCir=10;

// Centro de el espacio del tablero del Pong en x.
int centroX=ancho/2;
// Centro de el espacio del tablero del Pong en y.
int centroY=alto/2;

// Coordenada x de la raqueta1.
int xRaqueta1=50;
// Coordenada y de la raqueta1.
int yRaqueta1=centroY;

// Coordenada x de la raqueta2.
int xRaqueta2=ancho-xRaqueta1-xRaqueta1/2;
// Coordenada y de la raqueta2.
int yRaqueta2=centroY;

// Coordenada x de la pelota.
int xCir=centroX;
// Coordenada y de la pelota.
int yCir=centroY;

// Ancho de las raquetas.
float anchoR=radCir;
// Alto de las raquetas.
float altoR=xRaqueta1*2.8;

// Movimiento de las figuras
float velocidadBallX=-5.25f;
float velocidadBallY=5.25f;

// Cantidad de puntos del jugador 1.
int player1=0;
// Cantidad de puntos del jugador 2.
int player2=0;

// Indicador para saber si la raqueta1 está subiendo.
bool arriba1=false;
// Indicador para saber si la raqueta1 está bajando.
bool abajo1=false;

// Indicador para saber si la raqueta2 está subiendo.
bool arriba2=false;
// Indicador para saber si la raqueta2 está bajando.
bool abajo2=false;

void rebotaMuro(){
	// Caso del lado izquierdo.
	if(xCir<radCir){
		// Si la pelota llega al lado izquierdo la regreso al centro.
		xCir=centroX;
		yCir=centroY;
		// Cambio la dirección de la pelota en lado contrario respecto a x.
		velocidadBallX*=-1;
		// Como tocó la pared izquierda es punto para el jugador 2.
		player2+=1;
	}
	// Caso del lado derecho.
	if(xCir>ancho-radCir){
		// Si la pelota llega al lado izquierdo la regreso al centro.
		xCir=centroX;
		yCir=centroY;
		// Cambio la dirección de la pelota en lado contrario respecto a x.
		velocidadBallX*=-1;
		// Como tocó la pared derecha es punto para el jugador 1.
		player1+=1;
	}
	// Caso del lado inferior.
	if(yCir<radCir){
		// Si la pelota toca el lado inferior no dejo que se salga del espacio del Pong.
		yCir=radCir;
		// Cambio la dirección respecto a 'y' para que se mueva hacia arriba.
		velocidadBallY*=-1;
	}
	// Caso del lado superior.
	if(yCir>alto-radCir){
		// Si la pelota toca el lado superior no dejo que se salga del espacio del Pong.
		yCir=alto-radCir;
		// Cambio la dirección respecto a 'y' para que se mueva hacia abajo.
		velocidadBallY*=-1;
	}
}

void rebotaRaqueta(){
	// Verifico si la pelota toca el límite de la raqueta1 respecto a x. Lado derecho e izquierdo de la raqueta.
	if(xCir<xRaqueta1+radCir+anchoR && xCir>xRaqueta1-radCir){
		// Verifico si la pelota toca el límite de la raqueta1 respecto a y. Lado superior e inferior de la raqueta.
		if(yCir>yRaqueta1-radCir && yCir<yRaqueta1+altoR+radCir){
			// Si se cumplen ambas condiciones significa que la pelota interseca a la raqueta1 en algún punto
			// Entonces cambio la dirección tanto de 'x'. Para que se mueva de lado contrario.
			velocidadBallX*=-1;		
		}
	}
	// Verifico si la pelota toca el límite de la raqueta2 respecto a x. Lado derecho e izquierdo de la raqueta.
	if(xCir>xRaqueta2-radCir && xCir<xRaqueta2+radCir+anchoR){
		// Verifico si la pelota toca el límite de la raqueta1 respecto a y. Lado superior e inferior de la raqueta.
		if(yCir>yRaqueta2-radCir && yCir<yRaqueta2+altoR+radCir){
			// Si se cumplen ambas condiciones significa que la pelota interseca a la raqueta2 en algún punto
			// Entonces cambio la dirección tanto de 'x'. Para que se mueva de lado contrario.
			velocidadBallX*=-1;		
		}
	}
}

void moveRaqueta(){
	// Muevo la posición y de la raqueta1 hacia arriba (incrememtar en y). Siempre y cuando se cumpla que
	// No se pase del espacio del tablero y el identificador de dirección hacia arriba este activado.
	if(yRaqueta1<alto-altoR && arriba1)
		yRaqueta1+=15;

	// Muevo la posición y de la raqueta1 hacia abajo (decrememtar en y). Siempre y cuando se cumpla que
	// No se pase del espacio del tablero y el identificador de dirección hacia abajo este activado.
	if(yRaqueta1>0 && abajo1)
		yRaqueta1-=15;

	// Muevo la posición y de la raqueta2 hacia arriba (incrememtar en y). Siempre y cuando se cumpla que
	// No se pase del espacio del tablero y el identificador de dirección hacia arriba este activado.
	if(yRaqueta2<alto-altoR && arriba2)
		yRaqueta2+=15;

	// Muevo la posición y de la raqueta2 hacia arriba (incrememtar en y). Siempre y cuando se cumpla que
	// No se pase del espacio del tablero y el identificador de dirección hacia abajo este activado.
	if(yRaqueta2>0 && abajo2)
		yRaqueta2-=15;
}

void animate(int param){
	// En cada iteración actualizo la posición de la pelota.
	xCir+=velocidadBallX;
	yCir+=velocidadBallY;
	// Muevo las raquetas según los datos del estado actual.
	moveRaqueta();
	// Si la pelota toca un muro aplico esta función
	rebotaMuro();
	// Si la pelota toca una raqueta aplico esta función.
	rebotaRaqueta();
	glLoadIdentity();
	glutPostRedisplay();
	glutTimerFunc(33,animate,0);
}

void dibujaCir(float numSeg){
	// Se da un color rojo a la figura.
	glColor3f(1,0,0);
	glPushMatrix();
	// Se traslada la pelota según sus coordenadas.
	glTranslatef(xCir,yCir,0);
	float x, y, theta;
	// Se comienza a dibujar un triángulo.
    glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0, 0);
	// Con triángulo creamos una circunferencia que representa la pelota.
    for(int i = 0; i <= numSeg; i++) { 
		theta = 6.283185f * (float)i / numSeg;
		x = radCir*cos(theta);
		y = radCir*sin(theta);
		glVertex2f(x, y);
    }
    // Se termina de dibujar la pelota.
	glEnd();
	// Se saca de la matriz para que regrese a su estado inicial.
	glPopMatrix();
}

void dibujaRaquetas(){
	// Se usa el color verde para colorear las rectas.
	glColor3f(0,1,0);
	// Primero cada recta se mete a una matriz de transformación 
	glPushMatrix();
	// Se traslada a las coordenadas de la raqueta tanto en x como en y. z=0
	glTranslatef(xRaqueta1,yRaqueta1,0);
	// Se comienza a dibujar un polígono hecho a partir de triánguos.
    glBegin(GL_TRIANGLE_FAN);
		glVertex2f(0, 0);
		glVertex2f(anchoR,0);
		glVertex2f(anchoR, altoR);
		glVertex2f(0, altoR);
	glEnd();
	// Se saca de la matriz para que la figure regrese a las coordenadas originales.
	glPopMatrix();

	glPushMatrix();
	// Se traslada a las coordenadas de la raqueta tanto en x como en y. z=0
	glTranslatef(xRaqueta2,yRaqueta2,0);
	// Se comienza a dibujar un polígono hecho a partir de triánguos.
    glBegin(GL_TRIANGLE_FAN);
		glVertex2f(0, 0);
		glVertex2f(anchoR, 0);
		glVertex2f(anchoR, altoR);
		glVertex2f(0, altoR);
	glEnd();
	// Se saca de la matriz para que la figure regrese a las coordenadas originales.
	glPopMatrix();
}

void inline drawString (char *s){
 unsigned int i;
 // Recorremos el arreglo de chars para mostrar el texto en el tablero de Pong.
 for (i=0; i<strlen(s); i++)
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, s[i]);
}

void display ( void ){
	// Se limpia la pantalla antes de poder dibujar aglo.
	glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	// Se usará una proyección ortogonal.
	glOrtho(0, ancho, 0, alto, -10, 10);

	// Arreglo de chars donde se guarda el texto a mostrar en pantalla.
	char label[26];
	
	// Al texto se le asigna un color amarillo.
	glColor3f(1, 1, 0);
	// Se asigna al arreglo de chars el texto Player 1: %i.  Player 2: %i.
	sprintf(label,"Player 1: %i.  Player 2: %i.", player1,player2);
	glRasterPos2f(centroX-(anchoR*3), alto-(altoR/2));
	// Dibuja la leyenda en la pantalla.
	drawString (label);
	// Dibuja las raquetas a partir de la función para pintar raquetas.
	dibujaRaquetas();
	// Dibuja la pelota a partir de la función para pintar la pelota.
	dibujaCir(30.0f);
    glutSwapBuffers();
}

void reshape ( int w, int h){
	// Se especifica la transformación desde coordenadas del dispositivo.
	glViewport(0,0,w,h);
	// Se establece el modo de la matriz.
	glMatrixMode(GL_PROJECTION);
	// Se reemplaza la matriz actual por la identidad.
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard1(unsigned char key, int x, int y){
	switch(key){
		// Si se preciona la tecla 'w' o 'W', el identificador para moverse hacia arriba se activa en la raqueta1.
		case 'W':
		case 'w':
		arriba1=true;
		abajo1=false;
		break;
		// Si se preciona la tecla 'x' o 'X', el identificador para moverse hacia abajo se activa en la raqueta1.
		case 'X':
		case 'x':
		abajo1=true;
		arriba1=false;
		break;
	}
}

void keyboardArrow1(int key, int x, int y){
	switch(key){
		// Si se preciona la tecla de movimiento hacia arriba, el identificador para moverse hacia arriba se activa en la raqueta2.
		case GLUT_KEY_UP:
		arriba2=true;
		abajo2=false;
		break;
		// Si se preciona la tecla de movimiento hacia abajo, el identificador para moverse hacia abajo se activa en la raqueta2.
		case GLUT_KEY_DOWN:
		abajo2=true;
		arriba2=false;
		break;
	}
}

void keyboard2(unsigned char key, int x, int y){
	// Si se suelta la tecla 'w', 'W', 'x' o 'X' los identificadores de movimiento se apagan. No se mueve la raqueta1.
	if(key=='w' || key=='x' || key=='W' || key=='X'){
		arriba1=false;
		abajo1=false;
	}
}

void keyboardArrow2(int key, int x, int y){
	// Si se suelta la tecla de movimiento hacia arriba o movimiento hacia abajo, los identificadores de movimiento se
	// apagan. No se mueve la raqueta2.
	switch(key){
		case GLUT_KEY_UP:
		case GLUT_KEY_DOWN:
		arriba2=false;
		abajo2=false;	
	}
}

int main ( int argc, char** argv ){
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize (ancho,alto);
	glutInitWindowPosition (100,50);
	glutCreateWindow ("Pong");
	glClearColor(0.1,0.1,0.2,1);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard1);
	glutSpecialFunc(keyboardArrow1);
	glutKeyboardUpFunc(keyboard2);
	glutSpecialUpFunc(keyboardArrow2);
	glutTimerFunc(33,animate,0);
	glutMainLoop ();
	return 0;
}
