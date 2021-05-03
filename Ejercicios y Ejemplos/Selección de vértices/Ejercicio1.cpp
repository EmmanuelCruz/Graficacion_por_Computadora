#include <stdlib.h>
#include <GL/glut.h>

void drawHouse(){
  glClear(GL_COLOR_BUFFER_BIT);

  // Cara trasera del cuadrado.
  glBegin(GL_POLYGON);
  glColor3f(0.9,0.2,0.2);
  glVertex3f(0,0,-4);
  glVertex3f(1,0,-4);
  glVertex3f(1,1,-4);
  glVertex3f(0,1,-4);
  glEnd();
 
  // Cara del trriángulo tasera.
  glBegin(GL_TRIANGLES);
  glColor3f(0.3,0.5,0.6);
  glVertex3f(-0.2,1,-4);
  glVertex3f(1.2,1,-4);
  glVertex3f(0.5,1.5,-4);
  glEnd();

  // LADO INFERIOR: lado rojo
  glBegin(GL_POLYGON);
  glColor3f(1,0,0);
  glVertex3f(1,0,-4);
  glVertex3f(0,-1,-2);
  glVertex3f(-1,-1,-2);
  glVertex3f(0,0,-4);
  glEnd();

  // LADO IZQUIERDO: lado verde
  glBegin(GL_POLYGON);
  glColor3f(0,1,0);
  glVertex3f(-1,-1,-2);
  glVertex3f(-1,0,-2);
  glVertex3f(0,1,-4);
  glVertex3f(-0,-0,-4);
  glEnd();

  // LADO SUPERIOR: lado azul
  glBegin(GL_POLYGON);
  glColor3f(0,0,1);
  glVertex3f(0,0,-2);
  glVertex3f(1,1,-4);
  glVertex3f(0,1,-4);
  glVertex3f(-1,0,-2);
  glEnd();


  // LADO DERECHO: lado morado
  glBegin(GL_POLYGON);
  glColor3f(1,0,1);
  glVertex3f(1,0,-4);
  glVertex3f(1,1,-4);
  glVertex3f(0,0,-2);
  glVertex3f(0,-1,-2);
  glEnd();

  // LADO DERECHO: lado morado
  glBegin(GL_POLYGON);
  glColor3f(1,0,1);
  glVertex3f(1,0,-4);
  glVertex3f(1,1,-4);
  glVertex3f(0,0,-2);
  glVertex3f(0,-1,-2);
  glEnd();

  // Lado izquierdo: techo
  glBegin(GL_POLYGON);
  glColor3f(0,1,1);
  glVertex3f(-0.2,0,-2);
  glVertex3f(-0.5,0.5,-2);
  glVertex3f(0.5,1.5,-4);
  glVertex3f(-0.2,1,-4);
  glEnd();

  // Lado inferior: techo abajo
  glBegin(GL_POLYGON);
  glColor3f(1,1,0);
  glVertex3f(1.2,1,-4);
  glVertex3f(0.2,0,-2);
  glVertex3f(-0.2,0,-2);
  glVertex3f(-0.2,1,-4);
  glEnd();

  // lado derecho: techo
  glBegin(GL_POLYGON);
  glColor3f(0,1,0);
  glVertex3f(-0.5,0.5,-2);
  glVertex3f(0.2,0,-2);
  glVertex3f(1.2,1,-4);
  glVertex3f(0.5,1.5,-4);
  glEnd();

  // Cara principal
  glBegin(GL_POLYGON);
  glColor3f(0.9,0.2,0.2);
  glVertex3f(-1,0,-2);
  glVertex3f(-1,-1,-2);
  glVertex3f(0,-1,-2);
  glVertex3f(0,0,-2);
  glEnd();

  // Cara del triángulo frontal.
  glBegin(GL_TRIANGLES);
  glColor3f(0.3,0.5,0.6);
  glVertex3f(-1.2,0,-2);
  glVertex3f(0.2,0,-2);
  glVertex3f(-0.5,0.5,-2);
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

void myInit(const char *progname) {
  glutInitDisplayMode(GLUT_RGBA);		// modo RGBA
  glutInitWindowSize(1000, 500);		// ancho y largo
  glutInitWindowPosition(100, 100); 	// origen de la ventana
  glutCreateWindow(progname);
  glClearColor(0, 0, 0, 0);
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  myInit("Casita");
  glutDisplayFunc(drawHouse);
  glutReshapeFunc(myReshape);
  glutMainLoop();
  return 0;
}
