/* main.c
 */
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include "stb_image.h"
#include <fstream>

#define PI 3.14159265

// Ancho del campo de tierra,
static float ancho=28;

/* Cantidad de tríangulos en longitud y nivel de las esferas.*/
static int q=30;
static int p=30;

// Grados en los que se mueven los petalos de las flores.
// Comienza con los pétalos extendidos.
static double movePosition1=80;
// Comienza con los pétalos cerrados.
static double movePosition2=15;
// Comienza con los pétalos en un ángulo medio.
static double movePosition3=45;
static double movePosition4=45;

// Identificador de que los pétalos van hacia arriba o abajo.
// 4 identificadores para cada caso de movimiento.
bool move1=false;
bool move2=true;
bool move3=false;
bool move4=true;

// Cantidad de traslación en X para simular el viento.
static double moveX=0;
// Cantidad de traslación en Z para simular el viento.
static double moveZ=0;
// Cantidad de traslación en XZ positivo para simular el viento.
static double moveXZMas=0;

// Identificador para saber si la flor se mueve a la derecha o izquierda.
bool moveBoolX=true;
// Identificador para saber si la flor se mueve hacia adelante o atras,
bool moveBoolZ=true;
// Identificador para saber si la flor se mueve hacia adelante.
bool moveBoolXZMas=true;

// Ángulo en el que se rota la camara.
static double cameraRotator=0;

// Variables que permiten el movimiento hacia arriba y abajo de cada una de las flores.
static double downUp1=6;
static double downUp2=2;
static double downUp3=4;
static double downUp4=4;

// Identificadores para saber si las flores están subiendo o bajando.
bool up1=false;
bool up2=true;
bool up3=false;
bool up4=true;

// Identificador para saber si la animación está en curso o no.
bool continua=false;

// Componentes del ambiente para iluminación.
float ambient[]  = {1.0, 1.0, 1.0, 1.0};
float diffuse[]  = {1.0, 1.0, 1.0, 1.0};
float specular[] = {1.0, 1.0, 1.0, 1.0};

/**
* Permite cargar una textura de una imagen.
*/
void loadMyTexture(const char * imageName){
  unsigned int texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  int width, height, nrChannels;
  unsigned char *data = stbi_load(imageName, &width, &height, &nrChannels, 0);
  if (data)
    {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    }
  else
    {
      std::cout << "Falla al cargar la textura" << std::endl;
    }
  stbi_image_free(data);
}

/**
* Rutina para dibujar medio circulo.
*/
void drawCircle(float radius, int numVertices){
	int i;
	float t;
	glBegin(GL_POLYGON);
	for (i = 0; i < numVertices; ++i){
		t = 2 * PI * i / numVertices;
		glVertex3f(radius * cos(t), radius * sin(t), 0.0);
	}
	glEnd();
}

/**
* Permite dibujar una esfera.
*/
void drawSphere(double R, double r, double g, double b){
	int  i, j;
	glColor3f(r,g,b);
	for (j = 0; j < q; j++){
		glBegin(GL_TRIANGLE_STRIP);
		for (i = 0; i <= p; i++){
			glVertex3f(R * cos((float)(j + 1) / q * PI / 2.0) * cos(2.0 * (float)i / p * PI),
				R * sin((float)(j + 1) / q * PI / 2.0),
				-R * cos((float)(j + 1) / q * PI / 2.0) * sin(2.0 * (float)i / p * PI));
			glVertex3f(R * cos((float)j / q * PI / 2.0) * cos(2.0 * (float)i / p * PI),
				R * sin((float)j / q * PI / 2.0),
				-R * cos((float)j / q * PI / 2.0) * sin(2.0 * (float)i / p * PI));
		}
		glEnd();
	}
}

/**
* Permite al usuario detener o seguir la rotación.
*/
void myKeyboard(unsigned char key, int x, int y) {
	if (key == 27) exit(0);
	switch(key){
		case 's':
		case 'S':
		continua=false;
		break;
		case 'c':
		case 'C':
		continua=true;
		break;
	}
}

/**
* Actualiza los valores de cada iteración.
*/
void myUpdate() {
	// Mueve los petalos en la forma 1.
	if(move1){
		if(movePosition1>80){
			movePosition1=85;
			move1=false;
		} else
			movePosition1+=1;
	} else{
		if(movePosition1<10){
			movePosition1=5;
			move1=true;
		} else
			movePosition1-=1;
	}
	// Mueve los petalos en la forma 2.
	if(move2){
		if(movePosition2>80){
			movePosition2=85;
			move2=false;
		} else
			movePosition2+=1;
	} else{
		if(movePosition2<10){
			movePosition2=5;
			move2=true;
		} else
			movePosition2-=1;
	}
	// Mueve los petalos en la forma 3.
	if(move3){
		if(movePosition3>80){
			movePosition3=85;
			move3=false;
		} else
			movePosition3+=1;
	} else{
		if(movePosition3<10){
			movePosition3=5;
			move3=true;
		} else
			movePosition3-=1;
	}
	// Mueve los petalos en la forma 4.
	if(move4){
		if(movePosition4>80){
			movePosition4=85;
			move4=false;
		} else
			movePosition4+=1;
	} else{
		if(movePosition4<10){
			movePosition4=5;
			move4=true;
		} else
			movePosition4-=1;
	}
	// Mueve la flor en el eje X.
	if(moveBoolX){
		if(moveX>1){
			moveX=1.2;
			moveBoolX=false;
		} else
			moveX+=0.05;
	} else
		if(moveX<-1){
			moveX=-1.2;
			moveBoolX=true;
		} else
			moveX-=0.05;
	// Mueve la flor en el eje Z.
	if(moveBoolZ){
		if(moveZ>1){
			moveZ=1.2;
			moveBoolZ=false;
		} else
			moveZ+=0.05;
	} else
		if(moveZ<-1){
			moveZ=-1.2;
			moveBoolZ=true;
		} else
			moveZ-=0.05;
	if(moveBoolXZMas){
		if(moveXZMas>1){
			moveXZMas=1.2;
			moveBoolXZMas=false;
		} else
			moveXZMas+=0.05;
	} else
		if(moveXZMas<-1){
			moveXZMas=-1.2;
			moveBoolXZMas=true;
		} else
			moveXZMas-=0.05;
	// Si la animación etá en curso hace cambios.
	if(continua){
		if(cameraRotator>=360)
			cameraRotator=1;
		else
			cameraRotator+=2;
	}
	if(up1){
		if(downUp1>5.7){
			downUp1=6;
			up1=false;
		} else
			downUp1+=0.05;
	} else{
		if(downUp1<2.3){
			downUp1=2;
			up1=true;
		} else
			downUp1-=0.05;
	}
	if(up2){
		if(downUp2>5.7){
			downUp2=6;
			up2=false;
		} else
			downUp2+=0.05;
	} else{
		if(downUp2<2.3){
			downUp2=2;
			up2=true;
		} else
			downUp2-=0.05;
	}
	if(up3){
		if(downUp3>5.7){
			downUp3=6;
			up3=false;
		} else
			downUp3+=0.05;
	} else{
		if(downUp3<2.3){
			downUp3=2;
			up3=true;
		} else
			downUp3-=0.05;
	}
	if(up4){
		if(downUp4>5.7){
			downUp4=6;
			up4=false;
		} else
			downUp4+=0.05;
	} else{
		if(downUp4<2.3){
			downUp4=2;
			up4=true;
		} else
			downUp4-=0.05;
	}

	// Sube y baja las flores según su caso.
	glutPostRedisplay();
}

/**
* Permite dibujar el tallo de la flor. Este también se puede ver como la rutina para dibujar pasto.
*/
void drawStem(double lado, double alto, int optionMove){
	
	// Se da color verde a todas las componentes para cada vertice del tallo.	
	float stem[]  = {0.0, 1.0, 0.0, 1.0};
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  stem);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  stem);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, stem);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50);

	// Se dibuja el tallo. Un prisma rectangular.
	glBegin(GL_QUADS);

	/* Cara trasera del tallo.*/
	glVertex3f(lado,0.0,-lado);
	switch(optionMove){
		case 1:
		glVertex3f(lado+moveX,alto,-lado);
		glVertex3f(moveX-lado,alto,-lado);
		break;

		case 2:
		glVertex3f(lado,alto,moveZ-lado);
		glVertex3f(-lado,alto,moveZ-lado);
		break;

		case 3:
		glVertex3f(lado+moveXZMas,alto,moveXZMas-lado);
		glVertex3f(-lado+moveXZMas,alto,moveXZMas-lado);
		break;

	}
	glVertex3f(-lado,0.0,-lado);

	/* Cara derecha del tallo.*/
	glVertex3f(lado,0.0,-lado);
	glVertex3f(lado,0.0,lado);
	switch(optionMove){
		case 1:
		glVertex3f(lado+moveX,alto,lado);
		glVertex3f(lado+moveX,alto,-lado);
		break;
		case 2:
		glVertex3f(lado,alto,lado+moveZ);
		glVertex3f(lado,alto,-lado+moveZ);
		break;

		case 3:
		glVertex3f(lado+moveXZMas,alto,moveXZMas-lado);
		glVertex3f(moveXZMas-lado,alto,moveXZMas-lado);
		break;

	}

	/* Cara izquierda del tallo. */
	glVertex3f(-lado,0.0,-lado);
	switch(optionMove){
		case 1:
		glVertex3f(moveX-lado,alto,-lado);
		glVertex3f(moveX-lado,alto,lado);
		break;
		case 2:
		glVertex3f(-lado,alto,moveZ-lado);
		glVertex3f(-lado,alto,lado+moveZ);
		break;

		case 3:
		glVertex3f(lado+moveXZMas,alto,moveXZMas-lado);
		glVertex3f(moveXZMas-lado,alto,moveXZMas-lado);
		break;
	}
	glVertex3f(-lado,0.0,lado);

	/* Cara frontal del tallo. */
	glVertex3f(lado,0.0,lado);
	switch(optionMove){
		case 1:
		glVertex3f(lado+moveX,alto,lado);
		glVertex3f(moveX-lado,alto,lado);
		break;
		case 2:
		glVertex3f(lado,alto,lado+moveZ);
		glVertex3f(-lado,alto,lado+moveZ);
		break;

		case 3:
		glVertex3f(lado+moveXZMas,alto,moveXZMas-lado);
		glVertex3f(moveXZMas-lado,alto,moveXZMas-lado);
		break;
	}
	glVertex3f(-lado,0.0,lado);
	glEnd();
}

/**
* Rutina para dibujar una de las flores.
*/
void drawFlower(double radio, int altura,
				double x, double y, double z, 
				int option, int XZ, int num){
	// Se traslada a flor al espacio de dibujo deseado.
	glPushMatrix();
	glTranslatef(x,y,z);
	
	double alto=0;

	switch(altura){
		case 1:
		alto=downUp1;
		break;
		case 2:
		alto=downUp2;
		break;
		case 3:
		alto=downUp3;
		break;
		case 4:
		alto=downUp4;
		break;
	}

	// Dibuja el tallo de la flor.
	// Se especifica el comportamiento del movimiento del tallo.
	switch(XZ){
		case 1:
		drawStem(radio/4,alto,1);
		break;
		case 2:
		drawStem(radio/4,alto,2);
		break;
	}

	// Se especifica el color de los vertices para iluminación. El centro de la flor (amarillo)
	float center[]  = {1.0, 1.0, 0.0, 1.0};
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  center);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  center);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, center);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10);

	// Se mueve el espacio según el comportamiento del tallo.
	glPushMatrix();
	switch(XZ){
		case 1:
		glTranslatef(moveX,alto,0);
		break;
		case 2:
		glTranslatef(0,alto,moveZ);
		break;
	}

	// Dibuja el centro de la flor.
	drawSphere(1.0,1.0,1.0,0.0);

	// Se definen los colores que puede tomar una flor.
	float red[]={1.0,0,0,1.0};
	float blue[]={0.0,0,1,1};
	float yellow[]={0.22,0.69,0.87,1};
	float purple[]={1.0,0,1,1};
	float white[]={1.0,1,1,1};
	float orange[]={1.0,0.5,0,1};
	float pink[]={1,0.11,0.68,1};
	float violet[]={0.87,0.58,0.98,1};
	float aquamarine[]={0.8,0.196078,0.6,1};

	// Elige un color aleatorio para la flor.
	float auxiliar[4];
	switch(num){
		case 1:
		auxiliar[0]=red[0];
		auxiliar[1]=red[1];
		auxiliar[2]=red[2];
		break;
		case 2:
		auxiliar[0]=violet[0];
		auxiliar[1]=violet[1];
		auxiliar[2]=violet[2];
		break;
		case 3:
		auxiliar[0]=yellow[0];
		auxiliar[1]=yellow[1];
		auxiliar[2]=yellow[2];
		break;
		case 4:
		auxiliar[0]=purple[0];
		auxiliar[1]=purple[1];
		auxiliar[2]=purple[2];
		break;
		case 5:
		auxiliar[0]=white[0];
		auxiliar[1]=white[1];
		auxiliar[2]=white[2];
		break;
		case 6:
		auxiliar[0]=orange[0];
		auxiliar[1]=orange[1];
		auxiliar[2]=orange[2];
		break;
		case 7:
		auxiliar[0]=pink[0];
		auxiliar[1]=pink[1];
		auxiliar[2]=pink[2];
		break;
		case 8:
		auxiliar[0]=blue[0];
		auxiliar[1]=blue[1];
		auxiliar[2]=blue[2];
		break;
		case 9:
		auxiliar[0]=aquamarine[0];
		auxiliar[1]=aquamarine[1];
		auxiliar[2]=aquamarine[2];
		break;
	}

	// Se especifica la opacididad del color.
	auxiliar[3]=1;

	// Se da color a los vertices para los petalos de la flor.
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  auxiliar);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  auxiliar);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, auxiliar);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50);

	// Según el comportamiento del movimiento se los petalos se elige el ángulo de rotación.
	double grade=0;
	switch(option){
		case 1:
		grade=movePosition1;
		break;
		case 2:
		grade=movePosition2;
		break;
		case 3:
		grade=movePosition3;
		break;
		case 4:
		grade=movePosition4;
		break;
	}

	// Primer petalo.
	glPushMatrix();
	glTranslatef(0,0,-radio);
	glRotatef(grade,-1,0,0);//ESTE
	glPushMatrix();
	glScalef(1.0,2.0,1.0);
	drawCircle(radio,25);
	glPopMatrix();
	glPopMatrix();

	// Segundo petalo.
	glPushMatrix();
	glTranslatef(radio,0,0);
	glRotatef(90,0,1,0);
	glRotatef(grade,1,0,0);// ESTE
	glPushMatrix();
	glScalef(1.0,2.0,1.0);
	drawCircle(radio,25);
	glPopMatrix();
	glPopMatrix();

	// Tercer petalo.
	glPushMatrix();
	glTranslatef(0,0,radio);
	glRotatef(grade,1,0,0);//ESTE
	glPushMatrix();
	glScalef(1.0,2.0,1.0);
	drawCircle(radio,25);
	glPopMatrix();
	glPopMatrix();

	// Cuarto petalo.
	glPushMatrix();
	glTranslatef(-radio,0,0);
	glRotatef(90,0,-1,0);
	glRotatef(grade,1,0,0);// ESTE
	glPushMatrix();
	glScalef(1.0,2.0,1.0);
	drawCircle(radio,25);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glRotatef(45,0,1,0);
	// Quinto petalo.
	glPushMatrix();
	glTranslatef(0,0,-radio);
	glRotatef(grade,-1,0,0);//ESTE
	glPushMatrix();
	glScalef(1.0,2.0,1.0);
	drawCircle(radio,25);
	glPopMatrix();
	glPopMatrix();

	// Sexto petalo.
	glPushMatrix();
	glTranslatef(radio,0,0);
	glRotatef(90,0,1,0);
	glRotatef(grade,1,0,0);// ESTE
	glPushMatrix();
	glScalef(1.0,2.0,1.0);
	drawCircle(radio,25);
	glPopMatrix();
	glPopMatrix();

	// Septimo petalo.
	glPushMatrix();
	glTranslatef(0,0,radio);
	glRotatef(grade,1,0,0);//ESTE
	glPushMatrix();
	glScalef(1.0,2.0,1.0);
	drawCircle(radio,25);
	glPopMatrix();
	glPopMatrix();

	// Octavo petalo.
	glPushMatrix();
	glTranslatef(-radio,0,0);
	glRotatef(90,0,-1,0);
	glRotatef(grade,1,0,0);// ESTE
	glPushMatrix();
	glScalef(1.0,2.0,1.0);
	drawCircle(radio,25);
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();

	glPopMatrix();
}

/**
* Permite definir los parámetros de la fuente de iluminación.
*/
void mySetLight(){
	// Posición de la fuente de luz.
	float light0_position[] = {0,  10.0, 0, 1.0 };
	
	// Se coloca la posición de la luz.
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	
	/* Se activa el sombreado dentro de los objetos */
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	// Se habilita la luz 0.
	glEnable(GL_LIGHT0);
}

/**
* Permite dar al espacio cielo, usando una textura.
*/
void drarSky(){
	// Se dibuja el cielo.
	glColor3f(1,1,1);
	glBegin(GL_QUADS);
  	glTexCoord2f(1.0f, 1.0f);
  	glVertex3f(-ancho*1.5,0,-ancho*1.5);
  	glTexCoord2f(0.0f, 1.0f);
  	glVertex3f(ancho*1.5,0,-ancho*1.5);
  	glTexCoord2f(0.0f, 0.0f);
  	glVertex3f(ancho*1.5,50,-ancho*1.5);
  	glTexCoord2f(1.0f, 0.0f);
  	glVertex3f(-ancho*1.5,50,-ancho*1.5);
  	
  	glTexCoord2f(1.0f, 1.0f);
  	glVertex3f(-ancho*1.5,0,ancho*1.5);
  	glTexCoord2f(0.0f, 1.0f);
  	glVertex3f(ancho*1.5,0,ancho*1.5);
  	glTexCoord2f(0.0f, 0.0f);
  	glVertex3f(ancho*1.5,50,ancho*1.5);
  	glTexCoord2f(1.0f, 0.0f);
  	glVertex3f(-ancho*1.5,50,ancho*1.5);

  	glTexCoord2f(1.0f, 1.0f);
  	glVertex3f(ancho*1.5,0,-ancho*1.5);
  	glTexCoord2f(0.0f, 1.0f);
  	glVertex3f(ancho*1.5,0,ancho*1.5);
  	glTexCoord2f(0.0f, 0.0f);
  	glVertex3f(ancho*1.5,50,ancho*1.5);
  	glTexCoord2f(1.0f, 0.0f);
  	glVertex3f(ancho*1.5,50,-ancho*1.5);

  	glTexCoord2f(1.0f, 1.0f);
  	glVertex3f(-ancho*1.5,0,-ancho*1.5);
  	glTexCoord2f(0.0f, 1.0f);
  	glVertex3f(-ancho*1.5,0,ancho*1.5);
  	glTexCoord2f(0.0f, 0.0f);
  	glVertex3f(-ancho*1.5,50,ancho*1.5);
  	glTexCoord2f(1.0f, 0.0f);
  	glVertex3f(-ancho*1.5,50,-ancho*1.5);
  	glEnd();
}

/**
* Area de dibujo del espacio.
*/
void myDisplay() {	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

	glLoadIdentity();
	// Se ajusta la vista al escenario.
	gluLookAt(0,20,ancho*1.5,0,0,0,0,1,0);

	// Se rota el espacio según la variable de rotación.
	glRotatef(cameraRotator,0,1,0);

	// Se dibuja el cielo.
	drarSky();

	// Se habilita la iluminación.
	glEnable(GL_LIGHTING);

	// Se define el color café para la tierra.
  	float tierra[]  = {0.4,0.25,0.20, 1.0};
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  tierra);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  tierra);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, tierra);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50);

	/* Base de las flores.*/
	glBegin(GL_QUADS);
	glVertex3f(ancho*1.5,0.0,ancho*1.5);
	glVertex3f(ancho*1.5,0.0,-ancho*1.5);
	glVertex3f(-ancho*1.5,0.0,-ancho*1.5);
	glVertex3f(-ancho*1.5,0.0,ancho*1.5);
	glEnd();

	// Option: 1-4
	// XZ: 1-2
	int color=0;
	int opt=0;
	int opXZ=0;
	int altura=0;
	// Se dibujan las flores en el espacio.
	for(int i=-ancho;i<ancho;i+=6)
		for (int j = -ancho; j < ancho; j+=6){
			drawFlower(1,(altura%4)+1,i,0,j,(opt%4)+1,(opXZ%2)+1,(color%9)+1);
			color++;
			opt++;
			opXZ++;
			altura++;
		}
	// Se dibuja el pasto en el espacio.
	for(int k=-ancho;k<ancho;k+=1)
		for (int l = -ancho; l < ancho; l+=1){
			glPushMatrix();
			glTranslatef(k,0,l);;
			drawStem(0.05,2,(opXZ%3)+1);
			glPopMatrix();
			opXZ++;
		}

	glutSwapBuffers();
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
}

void myReshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (double)w / (double)h, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void myInit(const char *progname) {	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1000, 700);		// ancho y largo
	glutInitWindowPosition(100, 100); 	// origen de la ventana
	glutCreateWindow(progname);
	loadMyTexture("sky.jpg");
	glClearColor(0, 0, 0, 0.0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	myInit("Proyecto Final");
	glutKeyboardFunc(myKeyboard);
	glutDisplayFunc(myDisplay);
	mySetLight();
	glutIdleFunc(myUpdate);
	glutReshapeFunc(myReshape);
	glutMainLoop();
	return 0;
}
