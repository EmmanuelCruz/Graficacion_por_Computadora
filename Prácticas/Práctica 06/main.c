/* main.c
 */
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include <unistd.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <fstream>
#include <iostream>

float camaraX=0;
float camaraZ=0;
float length=10;
float ancho=length*2;
float camaraY=length/3;
unsigned int tex[50];
unsigned int numTex=0;

void cargarTextura(const char * imagen){
  unsigned int texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  int width, height, nrChannels;
  unsigned char *data = stbi_load(imagen, &width, &height, &nrChannels, 0);
  if (data)
    {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    }
  else
    {
      std::cout << "Failed to load texture" << std::endl;
    }
  stbi_image_free(data);
}

void myUpdate() {
  glutPostRedisplay();
}

void myKeyboard(unsigned char key, int x, int y) {
  if (key == 27) exit(0);
  switch(key){
  	case 'y':
  	  if(camaraY>length*6-10)
  	camaraY=length*6-5;
  else
  	camaraY+=2;
  break;
  	case 'b':
  if(camaraY<length)
  	camaraY=length/3;
  else
  	camaraY-=2;
  break;
  }
}

void specialKeyboard(int key, int x, int y){
	switch(key){
	case GLUT_KEY_RIGHT:
  if(camaraX>length*6-10)
  	camaraX=length*6-5;
  else
  	camaraX+=2;
  break;
  	case GLUT_KEY_LEFT:
  if(camaraX<-length*6+10)
  	camaraX=-length*6+5;
  else
  	camaraX-=2;
  break;
  	case GLUT_KEY_UP:
  if(camaraZ>ancho-10)
  	camaraZ=ancho-5;
  else
  	camaraZ+=2;
  break;
  	case GLUT_KEY_DOWN:
  if(camaraZ<-ancho+10)
  	camaraZ=-ancho+5;
  else
  	camaraZ-=2;
  break;
	}
}

void myDisplay() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_DEPTH_TEST);
  //glEnable(GL_LIGHTING);
  glLoadIdentity();
  glLoadIdentity();
  gluLookAt(camaraX,length/3,camaraZ,-30,camaraY,0,0,1,0);
  

  glBindTexture(GL_TEXTURE_2D,tex[0]);

  cargarTextura("Texturas/T0.bmp");
  
  // Fondo del espacio.
  glColor3f(1,1,1);
  glBegin(GL_QUADS);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(-7*length,0,-ancho-10);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(7*length,0,-ancho-10);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(7*length,120,-ancho-10);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(-7*length,120,-ancho-10);
  glEnd();

  glBegin(GL_QUADS);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(-7*length,0,ancho+10);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(7*length,0,ancho+10);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(7*length,120,ancho+10);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(-7*length,120,ancho+10);
  glEnd();

  glBegin(GL_QUADS);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(7*length,0,-ancho-10);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(7*length,0,ancho+10);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(7*length,120,ancho+10);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(7*length,120,-ancho-10);
  glEnd();

  glBegin(GL_QUADS);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(-7*length,0,-ancho-10);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-7*length,0,ancho+10);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-7*length,120,ancho+10);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(-7*length,120,-ancho-10);
  glEnd();

  cargarTextura("Texturas/img1.bmp");
  glColor3f(1,1,1);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-6*length,length,-ancho);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(-4*length,length,-ancho);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(-4*length,3*length,-ancho);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-6*length,3*length,-ancho);
  glEnd();

  cargarTextura("Texturas/img2.bmp");
  glColor3f(1,1,1);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-6*length,0,-ancho);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(-5*length,0,-ancho);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(-5*length,length,-ancho);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-6*length,length,-ancho);
  glEnd();

  cargarTextura("Texturas/img3.bmp");
  glColor3f(1,1,1);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-5*length,0,-ancho);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(-4*length,0,-ancho);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(-4*length,length,-ancho);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-5*length,length,-ancho);
  glEnd();

  cargarTextura("Texturas/img4.bmp");
  glColor3f(1,1,1);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-4*length,length,-ancho);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(-2*length,length,-ancho);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(-2*length,length*3,-ancho);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-4*length,length*3,-ancho);
  glEnd();

  cargarTextura("Texturas/img5.bmp");
  glColor3f(1,1,1);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-4*length,0,-ancho);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(-3*length,0,-ancho);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(-3*length,length,-ancho);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-4*length,length,-ancho);
  glEnd();

  cargarTextura("Texturas/img6.bmp");
  glColor3f(1,1,1);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-3*length,0,-ancho);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(-2*length,0,-ancho);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(-2*length,length,-ancho);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-3*length,length,-ancho);
  glEnd();

  cargarTextura("Texturas/img7.bmp");
  glColor3f(1,1,1);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-2*length,length,-ancho);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(0,length,-ancho);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(0,length*3,-ancho);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-2*length,length*3,-ancho);
  glEnd();

  cargarTextura("Texturas/img8.bmp");
  glColor3f(1,1,1);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-2*length,0,-ancho);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(-length,0,-ancho);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(-length,length,-ancho);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-2*length,length,-ancho);
  glEnd();

  cargarTextura("Texturas/img9.bmp");
  glColor3f(1,1,1);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-length,0,-ancho);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(0,0,-ancho);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(0,length,-ancho);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-length,length,-ancho);
  glEnd();

  cargarTextura("Texturas/img10.bmp");
  glColor3f(1,1,1);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(0,length,-ancho);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(2*length,length,-ancho);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(2*length,length*3,-ancho);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(0,length*3,-ancho);
  glEnd();

  cargarTextura("Texturas/img11.bmp");
  glColor3f(1,1,1);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(0,0,-ancho);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(length,0,-ancho);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(length,length,-ancho);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(0,length,-ancho);
  glEnd();

  cargarTextura("Texturas/img12.bmp");
  glColor3f(1,1,1);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(length,0,-ancho);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(2*length,0,-ancho);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(2*length,length,-ancho);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(length,length,-ancho);
  glEnd();

  cargarTextura("Texturas/img13.bmp");
  glColor3f(1,1,1);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(2*length,length,-ancho);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(4*length,length,-ancho);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(4*length,length*3,-ancho);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(2*length,length*3,-ancho);
  glEnd();

  cargarTextura("Texturas/img14.bmp");
  glColor3f(1,1,1);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(2*length,0,-ancho);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(3*length,0,-ancho);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(3*length,length,-ancho);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(2*length,length,-ancho);
  glEnd();

  cargarTextura("Texturas/img15.bmp");
  glColor3f(1,1,1);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(3*length,0,-ancho);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(4*length,0,-ancho);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(4*length,length,-ancho);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(3*length,length,-ancho);
  glEnd();

  cargarTextura("Texturas/img16.bmp");
  glColor3f(1,1,1);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(4*length,length,-ancho);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(6*length,length,-ancho);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(6*length,length*3,-ancho);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(4*length,length*3,-ancho);
  glEnd();

  cargarTextura("Texturas/img17.bmp");
  glColor3f(1,1,1);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(4*length,0,-ancho);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(5*length,0,-ancho);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(5*length,length,-ancho);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(4*length,length,-ancho);
  glEnd();

  cargarTextura("Texturas/img18.bmp");
  glColor3f(1,1,1);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(5*length,0,-ancho);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(6*length,0,-ancho);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(6*length,length,-ancho);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(5*length,length,-ancho);
  glEnd();

  cargarTextura("Texturas/img21.bmp");
  glColor3f(1,1,1);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-6*length,length,ancho);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(-4*length,length,ancho);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(-4*length,3*length,ancho);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-6*length,3*length,ancho);
  glEnd();

  cargarTextura("Texturas/img22.bmp");
  glColor3f(1,1,1);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-6*length,0,ancho);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(-5*length,0,ancho);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(-5*length,length,ancho);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-6*length,length,ancho);
  glEnd();

  cargarTextura("Texturas/img23.bmp");
  glColor3f(1,1,1);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-5*length,0,ancho);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(-4*length,0,ancho);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(-4*length,length,ancho);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-5*length,length,ancho);
  glEnd();

  cargarTextura("Texturas/img24.bmp");
  glColor3f(1,1,1);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-4*length,length,ancho);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(-2*length,length,ancho);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(-2*length,length*3,ancho);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-4*length,length*3,ancho);
  glEnd();

  cargarTextura("Texturas/img25.bmp");
  glColor3f(1,1,1);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-4*length,0,ancho);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(-3*length,0,ancho);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(-3*length,length,ancho);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-4*length,length,ancho);
  glEnd();

  cargarTextura("Texturas/img26.bmp");
  glColor3f(1,1,1);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-3*length,0,ancho);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(-2*length,0,ancho);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(-2*length,length,ancho);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-3*length,length,ancho);
  glEnd();

  cargarTextura("Texturas/img27.bmp");
  glColor3f(1,1,1);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-2*length,length,ancho);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(0,length,ancho);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(0,length*3,ancho);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-2*length,length*3,ancho);
  glEnd();

  cargarTextura("Texturas/img28.bmp");
  glColor3f(1,1,1);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-2*length,0,ancho);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(-length,0,ancho);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(-length,length,ancho);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-2*length,length,ancho);
  glEnd();

  cargarTextura("Texturas/img29.bmp");
  glColor3f(1,1,1);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-length,0,ancho);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(0,0,ancho);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(0,length,ancho);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-length,length,ancho);
  glEnd();

  cargarTextura("Texturas/img30.bmp");
  glColor3f(1,1,1);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(0,length,ancho);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(2*length,length,ancho);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(2*length,length*3,ancho);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(0,length*3,ancho);
  glEnd();

  cargarTextura("Texturas/img31.bmp");
  glColor3f(1,1,1);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(0,0,ancho);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(length,0,ancho);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(length,length,ancho);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(0,length,ancho);
  glEnd();

  cargarTextura("Texturas/img32.bmp");
  glColor3f(1,1,1);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(length,0,ancho);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(2*length,0,ancho);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(2*length,length,ancho);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(length,length,ancho);
  glEnd();

  cargarTextura("Texturas/img33.bmp");
  glColor3f(1,1,1);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(2*length,length,ancho);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(4*length,length,ancho);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(4*length,length*3,ancho);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(2*length,length*3,ancho);
  glEnd();

  cargarTextura("Texturas/img34.bmp");
  glColor3f(1,1,1);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(2*length,0,ancho);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(3*length,0,ancho);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(3*length,length,ancho);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(2*length,length,ancho);
  glEnd();

  cargarTextura("Texturas/img35.bmp");
  glColor3f(1,1,1);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(3*length,0,ancho);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(4*length,0,ancho);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(4*length,length,ancho);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(3*length,length,ancho);
  glEnd();

  cargarTextura("Texturas/img36.bmp");
  glColor3f(1,1,1);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(4*length,length,ancho);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(6*length,length,ancho);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(6*length,length*3,ancho);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(4*length,length*3,ancho);
  glEnd();

  cargarTextura("Texturas/img37.bmp");
  glColor3f(1,1,1);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(4*length,0,ancho);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(5*length,0,ancho);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(5*length,length,ancho);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(4*length,length,ancho);
  glEnd();

  cargarTextura("Texturas/img38.bmp");
  glColor3f(1,1,1);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(5*length,0,ancho);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(6*length,0,ancho);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(6*length,length,ancho);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(5*length,length,ancho);
  glEnd();

  cargarTextura("Texturas/T46.bmp");
  glBegin(GL_QUADS);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(6*length,0,-ancho);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(6*length,0,-ancho/2);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(6*length,length,-ancho/2);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(6*length,length,-ancho);
  glEnd();

  glBegin(GL_QUADS);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(6*length,0,-ancho/2);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(6*length,0,0);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(6*length,length,0);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(6*length,length,-ancho/2);
  glEnd();

  glBegin(GL_QUADS);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(6*length,0,0);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(6*length,0,ancho/2);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(6*length,length,ancho/2);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(6*length,length,0);
  glEnd();

  glBegin(GL_QUADS);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(6*length,0,ancho/2);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(6*length,0,ancho);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(6*length,length,ancho);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(6*length,length,ancho/2);
  glEnd();

  cargarTextura("Texturas/T3.bmp");
  glBegin(GL_QUADS);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(-6*length,0,-ancho);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-6*length,0,-ancho/2);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-6*length,length,-ancho/2);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(-6*length,length,-ancho);
  glEnd();

  glBegin(GL_QUADS);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(-6*length,0,-ancho/2);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-6*length,0,0);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-6*length,length,0);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(-6*length,length,-ancho/2);
  glEnd();

  glBegin(GL_QUADS);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(-6*length,0,0);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-6*length,0,ancho/2);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-6*length,length,ancho/2);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(-6*length,length,0);
  glEnd();

  glBegin(GL_QUADS);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(-6*length,0,ancho/2);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-6*length,0,ancho);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-6*length,length,ancho);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(-6*length,length,ancho/2);
  glEnd();

  cargarTextura("Texturas/T4.bmp");
  glBegin(GL_QUADS);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(6*length,0,ancho);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-6*length,0,ancho);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-6*length,0,-ancho);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(6*length,0,-ancho);
  glEnd();

  glFlush();
  glutSwapBuffers();
  //glDisable(GL_LIGHTING);
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_TEXTURE_2D);
}

void myReshape(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, (double)w / (double)h, 0.1, 150.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void myInit(const char *progname) {	
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  char* s;
  glutInitWindowSize(1000, 700);		// ancho y largo
  glutInitWindowPosition(100, 100); 	// origen de la ventana
  glutCreateWindow(progname);
  glClearColor(0.0, 0.0, 0.0, 0.0);
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  myInit("Texturas");
  glutKeyboardFunc(myKeyboard);
  glutSpecialFunc(specialKeyboard);
  glutDisplayFunc(myDisplay);
  glutIdleFunc(myUpdate);
  glutReshapeFunc(myReshape);
  glutMainLoop();
  return 0;
}
