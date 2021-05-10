#include "main.h"

int prog_act = 0;
int max_prog = 0;
GLuint program[10];
GLuint vao;
GLuint vbo;

float rotx = 4, roty = 0, rotz = 0;

Mesh *objeto;

void myInit(const char* s){
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(s);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void clean(void) {
	elimMesh(objeto);
}

void reshape (int width, int height){
	glViewport(0, 0, width, height);
	float ar = (float) width / (float) height;
	glm::mat4 projection = glm::perspective(glm::radians(60.0f), ar, 0.1f, 100.0f);
	//glm::mat4 projection = glm::ortho(-3.0f, 3.0f,-3.0f, 3.0f,  0.1f, 100.0f);
	GLuint projLoc = glGetUniformLocation(program[prog_act], "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void keyboard(unsigned char key, int x, int y) {
	switch(key) {
		//tecla 'esc'
		case 27: 	glutLeaveMainLoop();	break;
		case 'q':	rotx++;	break;
		case 'w':	rotx--;	break;
		case 'a':	roty++;	break;
		case 's':	roty--;	break;
		case 'z':	rotz++;	break;
		case 'x':	rotz--; break;
	}
	glutPostRedisplay();
}

void display (void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//matriz de modelo: usada para aplicar transformaciones a los modelos y
	// para el manejo de la camara
	glm::mat4 modelview;
	//model = glm::translate(model, glm::vec3(0.0, 0.0, -15.0));
	modelview = glm::rotate(modelview, glm::radians(rotx), glm::vec3(1.0, 0.0, 0.0));
	modelview = glm::rotate(modelview, glm::radians(roty), glm::vec3(0.0, 1.0, 0.0));
	modelview = glm::rotate(modelview, glm::radians(rotz), glm::vec3(0.0, 0.0, 1.0));

	modelview = glm::lookAt(glm::vec3(0.0, 2.0, 8.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0)) * modelview;
	GLuint modelLoc = glGetUniformLocation(program[prog_act], "modelview");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelview));

	//matriz de normales: usada para transformar normales al espacio de vista
	glm::mat4 normalMat = glm::transpose(glm::inverse(modelview));
	GLuint normalmLoc = glGetUniformLocation(program[prog_act], "normalMat");
	glUniformMatrix4fv(normalmLoc, 1, GL_FALSE, glm::value_ptr(normalMat));

	drawMesh(objeto);
	glFlush();
}


int main(int argc, char** argv){
	glutInit(&argc, argv);
	myInit("Mi programa de OpenGL");

	glewExperimental=GL_TRUE;
	GLenum err=glewInit();
	if(err!=GLEW_OK) {
		// Problem: glewInit failed, something is seriously wrong.
    	printf("glewInit failed: %s\n", glewGetErrorString(err));
    	exit(1);
	}
	//Creamos programa GLSL
	program[0] = initShader("test.vsh", "test.fsh");
	max_prog++;

	//activamos el programa 0
	glUseProgram(program[0]);

	//creamos el Mesh
	objeto = createMesh("statue.obj");
	if (objeto == NULL) {
		glutLeaveMainLoop();
	}

	glEnable(GL_DEPTH_TEST);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutCloseFunc(clean);
	glutMainLoop();
	return 0;
}

