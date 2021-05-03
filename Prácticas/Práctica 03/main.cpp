/* main.c
 */
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <cstdio>

// Vista de la cámara al modelo en el eje X.
float modelViewerX=0;
// Vista de la cámara al modelo en el eje Y.
float modelViewerY=0;
// Vista de la cámara al modelo en el eje Z.
float modelViewerZ=0;

// Modelo cargado. 0 - bear. 1 - statue
int modelo=0;

// Modelo cargado del oso
int bear;

// Modelo cargado de la estatua.
int statue;

// Estructura para poder almancenar una coordenada.
struct coordenada{
	// Componentes de una coordenada.
  float x, y, z;

  coordenada(float a, float b, float c) :	 x(a), y(b), z(c){};
};

// Estructura para poder almancenar una cara.
struct cara
{
  int NoCaras;
  // Puntos que almacena una cara tanto de coordenadas, vectores normales y texturas.
  int caras[9];

  // Guarda los identificadores de vértices, de vectores normales y mapeo de texturas.
  cara(int caran, int f1, int f2, int f3, int f4, int f5,
       int f6, int f7, int f8, int f9) : NoCaras(caran){
    caras[0]=f1;
    caras[1]=f2;
    caras[2]=f3;
    caras[3]=f4;
    caras[4]=f5;
    caras[5]=f6;
    caras[6]=f7;
    caras[7]=f8;
    caras[8]=f9;
  }

  // Guarda solo identificadores de los vértices que componen la cara.
  cara(int caran, int f1, int f2, int f3) : NoCaras(caran){
    caras[0]=f1;
    caras[1]=f2;
    caras[2]=f3;
  }
};

// Carga el modelo OBJ.
int loadOBJ(const char* name,int op){
	// Vector para guardar las coordenadas.
  std::vector<std::string*> coord;
  // Vector para guardar los vértices.
  std::vector<coordenada*> vertice;
  // Vector para guardar las caras.
  std::vector<cara*> faces;
  // Vector para guardar las normales.
  std::vector<coordenada*> normales;

  // Leemos el archivo
  std::ifstream in(name);
  // Si el archivo no fue encontrado mandamos un error.
  if(!in.is_open()){
    std::cout << "Archivo no encontrado" << std::endl;
    return -1;
  }
  char c[256];

  while(!in.eof()){
    in.getline(c,256);
    coord.push_back(new std::string(c));
  }

  // Recorremos lo leído en el archivo .obj.
  for(int i=0;i<coord.size();i++){
  	// Si nos encontramos un comentario nos pasamos a la siguiente línea.
    if((*coord[i])[0]=='#')
      continue;
	// Si nos encontramos un vértice lo leemos, lo transformamos a coordenada y lo agregamos al vector de vértices.
    else if ((*coord[i])[0]=='v' &&
	     (*coord[i])[1]==' ')
      {
	float tmpx, tmpy, tmpz;
	sscanf(coord[i]->c_str(),"v %f %f %f",&tmpx,&tmpy,&tmpz);
	vertice.push_back(new coordenada(tmpx,tmpy,tmpz));
      }
    // Si nos encontramos un vector normal lo leemos, lo transformamos a coordenada y lo agregamos al vector de normales.
    else if ((*coord[i])[0]=='v')
      {
	float tmpx, tmpy, tmpz;
	sscanf(coord[i]->c_str(),"vn %f %f %f",&tmpx,&tmpy,&tmpz);
	normales.push_back(new coordenada(tmpx,tmpy,tmpz));
      }
    // Si nos encontramos una cara la leemos, la transformams a una cara y la agregamos al vector de caras.
    else if ((*coord[i])[0]=='f')
      {
	int a1,a2,a3,b1,b2,b3,c1,c2,c3,d;
	// Si la cara es de bear.obj sólo leemos los 3 identificadores de los vértices. En otro caso leemos todas las componentes de statue.obj
	if(op==1){
	  sscanf(coord[i]->c_str(),"f %d/%d/%d %d/%d/%d %d/%d/%d",
		 &a1,&a2,&a3,&b1,&b2,&b3,&c1,&c2,&c3);
	  faces.push_back(new cara(d,a1,a2,a3,b1,b2,b3,c1,c2,c3));
	} else{
	  sscanf(coord[i]->c_str(),"f %d %d %d",&a1,&a2,&a3);
	  faces.push_back(new cara(d,a1,a2,a3));
	}
      }
  }

  // DIBUJAR (YUJU!!!)
  int numero;
  numero=glGenLists(1);
  glNewList(numero,GL_COMPILE);
  // Si leímos bear.obj pintamos de café oscuro. En otro caso de blanco.
  if(op==0){
    glColor3f(0.36,0.25,0.20);
  } else{
    glColor3f(1,1,1);
  }
  for (int i = 0; i < faces.size(); ++i)
    {
      if(op==1){
	glBegin(GL_TRIANGLES);
	// CASO PARA LA ESTATUA
	glNormal3f(normales[0]->x,
		   normales[0]->y,
		   normales[0]->z);
	// Primer vértice
	glVertex3f(vertice[faces[i]->caras[0]-1]->x,
		   vertice[faces[i]->caras[0]-1]->y,
		   vertice[faces[i]->caras[0]-1]->z);

	// Segundo vértice
	glVertex3f(vertice[faces[i]->caras[3]-1]->x,
		   vertice[faces[i]->caras[3]-1]->y,
		   vertice[faces[i]->caras[3]-1]->z);

	// Tercer vértice
	glVertex3f(vertice[faces[i]->caras[6]-1]->x,
		   vertice[faces[i]->caras[6]-1]->y,
		   vertice[faces[i]->caras[6]-1]->z);
	glEnd();
      } else{
	glBegin(GL_TRIANGLES);
	// CASO PARA EL OSO
	// Primer vértice
	glVertex3f(vertice[faces[i]->caras[0]-1]->x,
		   vertice[faces[i]->caras[0]-1]->y,
		   vertice[faces[i]->caras[0]-1]->z);

	// Segundo vértice
	glVertex3f(vertice[faces[i]->caras[1]-1]->x,
		   vertice[faces[i]->caras[1]-1]->y,
		   vertice[faces[i]->caras[1]-1]->z);

	// Tercer vértice
	glVertex3f(vertice[faces[i]->caras[2]-1]->x,
		   vertice[faces[i]->caras[2]-1]->y,
		   vertice[faces[i]->caras[2]-1]->z);
	glEnd();
      }
    }
  glEndList();
  return numero;
}

void myReshape(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, (double)w / (double)h, 0.1, 25.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void myInit(const char *progname) {	
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
  glutInitWindowSize(1000, 700);		// ancho y largo
  glutInitWindowPosition(100, 100); 	// origen de la ventana
  glutCreateWindow(progname);
  glClearColor(0.0, 0.0, 0.0, 0.0);
  bear=loadOBJ("bear.obj",0);
  statue=loadOBJ("statue.obj",1);
}

//no es necesario pero si se quiere usar se puede
void myUpdate() {
  glutPostRedisplay();
}

void myDisplay() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glLoadIdentity();
  // Posicionamos la carama en un punto segun el modelo.
  if(modelo==0)
    gluLookAt(0,0,10,0,0,0,0,1,0);
  else
    gluLookAt(0,0,17,0,0,0,0,1,0);
  // Rotamos la figura según los parámetros
  glRotatef(modelViewerY,1,0,0);
  glRotatef(modelViewerX,0,1,0);
  glRotatef(modelViewerZ,0,0,1);
  // Mostramos el modelo según el caso.
  if(modelo==0)
    glCallList(bear);
  else
    glCallList(statue);
  glutSwapBuffers();
  glDisable(GL_DEPTH_TEST);
}

void myKeyboard(unsigned char key, int x, int y) {
  if (key == 27) exit(0);
  switch(key){
  case '1':
  modelo=0;
  break;
  case '2':
  modelo=1;
  break;
  case 'z':
  modelViewerZ+=5;
  break;
  case 'Z':
  modelViewerZ-=5;
  break;
  }
}

void specialKeyboard(int key, int x, int y){
	switch(key){
	case GLUT_KEY_RIGHT:
    modelViewerX+=5;
    break;
  	case GLUT_KEY_LEFT:
    modelViewerX-=5;
    break;
  	case GLUT_KEY_UP:
    modelViewerY+=5;
    break;
  	case GLUT_KEY_DOWN:
    modelViewerY-=5;
    break;
	}
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  myInit("Ejercicio 3");
  glutKeyboardFunc(myKeyboard);
  glutSpecialFunc(specialKeyboard);
  glutDisplayFunc(myDisplay);
  glutIdleFunc(myUpdate);
  glutReshapeFunc(myReshape);
  glutMainLoop();
  return 0;
}	
