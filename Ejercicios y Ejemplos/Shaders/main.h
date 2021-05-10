// main.h

#ifndef __main__
#define __main__

#include <stdio.h>
#include <stdlib.h>
//GLM---------------------
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//------------------------

#include <GL/glew.h>		//banderas: -lGLEW
#include <GL/freeglut.h>	// -lGL -lGLU -lXx86vm
#include <math.h>			//-lm

#define MAX_VERT			90000
#define MAX_FACE			90000
#define STEP				30
#define PI					3.1415
#define BUFFER_OFFSET(i) 	((char*) NULL + (i))
//------------------------

//Estructura para guardar los vertices
struct Vertex {
	glm::vec3 pos;		//posicion de vertices
	glm::vec3 normal;	//direccion de normal
	glm::vec2 texpos;	//posicion de textura
};

//Estructura para guardar modelos
struct Mesh {
	Vertex *verts;				//arreglo de vertices
	unsigned int *indices;		//arreglo de indices
	GLuint numv, numi;			//longitud de arreglos
	unsigned int VAO, VBO, EBO;	//ids para VAO, VBO y EB
};


char* readShaderSource(const char*);
GLuint initShader(const char*, const char*);
Mesh * createMesh(const char*);
void drawMesh(Mesh*);
void elimMesh(Mesh*);

#endif //__main__
