#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

//Patrones que usaremos para los poligonos
GLubyte fly[] = {
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x03, 0x80, 0x01, 0xC0, 0x06, 0xC0, 0x03, 0x60, 
      0x04, 0x60, 0x06, 0x20, 0x04, 0x30, 0x0C, 0x20, 
      0x04, 0x18, 0x18, 0x20, 0x04, 0x0C, 0x30, 0x20,
      0x04, 0x06, 0x60, 0x20, 0x44, 0x03, 0xC0, 0x22, 
      0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22, 
      0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22,
      0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22, 
      0x66, 0x01, 0x80, 0x66, 0x33, 0x01, 0x80, 0xCC, 
      0x19, 0x81, 0x81, 0x98, 0x0C, 0xC1, 0x83, 0x30,
      0x07, 0xe1, 0x87, 0xe0, 0x03, 0x3f, 0xfc, 0xc0, 
      0x03, 0x31, 0x8c, 0xc0, 0x03, 0x33, 0xcc, 0xc0, 
      0x06, 0x64, 0x26, 0x60, 0x0c, 0xcc, 0x33, 0x30,
      0x18, 0xcc, 0x33, 0x18, 0x10, 0xc4, 0x23, 0x08, 
      0x10, 0x63, 0xC6, 0x08, 0x10, 0x30, 0x0c, 0x08, 
      0x10, 0x18, 0x18, 0x08, 0x10, 0x00, 0x00, 0x08};

 GLubyte halftone[] = {
      0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55, 
      0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55, 
      0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
      0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55, 
      0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55, 
      0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
      0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55, 
      0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55, 
      0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
      0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55, 
      0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55, 
      0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
      0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55, 
      0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55, 
      0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
      0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55};


void reshape(int width, int height)
{
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
 
void draw()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(20);

    glPolygonMode(GL_FRONT, GL_LINE);

    glBegin(GL_POLYGON);
	glColor3f(1,0,0);
	glVertex2f(-0.2,-0.2);		
	glColor3f(1,1,0);
	glVertex2f(-0.2,0.2);	
	glColor3f(1,0,1);
	glVertex2f(0.2,0.2);	
	glColor3f(0.5,1,0);
	glVertex2f(0.2,-0.2);	
    glEnd();
  
    glPolygonMode(GL_FRONT, GL_POINT);

    glBegin(GL_POLYGON);
	glColor3f(0,1,0);
	glVertex2f(0.5,0.5);		
	glColor3f(0,1,1);
	glVertex2f(0,0.5);
	glColor3f(0,1,0.5);
	glVertex2f(0,-0.5); 
	glColor3f(0.5,1,0.5);
	glVertex2f(0.5,-0.5);	
    glEnd();


   glFlush();
}

//Ejemplo de front face
void drawFF()
{
    glClear(GL_COLOR_BUFFER_BIT);
   
    glFrontFace(GL_CW);

    glPointSize(20);

    glPolygonMode(GL_FRONT, GL_LINE);

    glBegin(GL_POLYGON);
	glColor3f(1,0,0);
	glVertex2f(-0.2,-0.2);		
	glColor3f(1,1,0);
	glVertex2f(-0.2,0.2);	
	glColor3f(1,0,1);
	glVertex2f(0.2,0.2);	
	glColor3f(0.5,1,0);
	glVertex2f(0.2,-0.2);	
    glEnd();

    glFrontFace(GL_CCW);

    glPolygonMode(GL_FRONT, GL_POINT);
    glBegin(GL_POLYGON);
	glColor3f(0,1,0);
	glVertex2f(0.5,0.5);		
	glColor3f(0,1,1);
	glVertex2f(0,0.5);
	glColor3f(0,1,0.5);
	glVertex2f(0,-0.5); 
	glColor3f(0.5,1,0.5);
	glVertex2f(0.5,-0.5);	
    glEnd();
    glFlush();
}


//Ejemplo de culling face
void drawCF()
{
    glClear(GL_COLOR_BUFFER_BIT);
   
    glFrontFace(GL_CW);//Cambio de direccion

    glEnable(GL_CULL_FACE);//Activamos el corte de caras

    glCullFace(GL_FRONT);//Indicamos que caras se quieren cortar

    glBegin(GL_POLYGON);
	glColor3f(1,0,0);
	glVertex2f(-0.2,-0.2);		
	glColor3f(1,1,0);
	glVertex2f(-0.2,0.2);	
	glColor3f(1,0,1);
	glVertex2f(0.2,0.2);	
	glColor3f(0.5,1,0);
	glVertex2f(0.2,-0.2);	
    glEnd();

    glDisable(GL_CULL_FACE);//Desactivamos el corte de caras

    glFrontFace(GL_CCW);//Cambio de direccion

    glEnable(GL_CULL_FACE);//Indicamos que caras se quieren cortar

    glCullFace(GL_FRONT);//Indicamos que caras se quieren cortar

    glBegin(GL_POLYGON);
	glColor3f(0,1,0);
	glVertex2f(0.5,0.5);		
	glColor3f(0,1,1);
	glVertex2f(0,0.5);
	glColor3f(0,1,0.5);
	glVertex2f(0,-0.5); 
	glColor3f(0.5,1,0.5);
	glVertex2f(0.5,-0.5);	
    glEnd();

    glDisable(GL_CULL_FACE);

    glFlush();
}

//Ejemplo de polygon stipple
void drawPP()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glShadeModel(GL_FLAT);//Cambiamos del modo smooth, que permite interpolacion, al modo flat 

    glBegin(GL_POLYGON);
	glColor3f(1,0,0);
	glVertex2f(-0.8,-0.2);		
	glColor3f(1,1,0);
	glVertex2f(-0.8,0.2);	
	glColor3f(1,0,1);
	glVertex2f(-0.4,0.2);	
	glColor3f(0.5,1,0);
	glVertex2f(-0.4,-0.2);	
    glEnd();

    glEnable(GL_POLYGON_STIPPLE);//Activamos el modo de poligonos con patrones

    glPolygonStipple(fly);//
                          //La funcion toma como parametro un bitmap de 32 x 32 bits

    glBegin(GL_POLYGON);
	glColor3f(1,0,0);
	glVertex2f(-0.2,-0.2);		
	glColor3f(1,1,0);
	glVertex2f(-0.2,0.2);	
	glColor3f(1,0,1);
	glVertex2f(0.2,0.2);	
	glColor3f(0.5,1,0);
	glVertex2f(0.2,-0.2);	
    glEnd();

    glPolygonStipple(halftone);

    glBegin(GL_POLYGON);
	glColor3f(1,0,0);
	glVertex2f(0.4,-0.2);		
	glColor3f(1,1,0);
	glVertex2f(0.4,0.2);	
	glColor3f(1,0,1);
	glVertex2f(0.8,0.2);	
	glColor3f(0.5,1,0);
	glVertex2f(0.8,-0.2);	
    glEnd();

    glDisable (GL_POLYGON_STIPPLE);
	
    glFlush();

}

//Dibujar un circulo 
void drawCicle()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLE_FAN);
    //Coordenadas del centro
    float cx = 0;
    float cy = 0;
    //radio
    float r = 0.5; 
    //num de segmentos
    int num_segments = 360;
    for(int ii = 0; ii < num_segments; ii++) { 
	float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);
	float x = r * cos(theta);
	float y = r * sin(theta);
	glVertex2f(x + cx, y + cy);
    } 
    glEnd(); 
    glFlush();
}


void drawSquare()
{
    glBegin(GL_TRIANGLE_STRIP);

	glVertex3f(0.9,-0.9,0);
	glVertex3f(0.9,0.9,0);
	glVertex3f(-0.9,-0.9,0);
	glVertex3f(-0.9,0.9,0);

    glEnd();
	
}

void drawSquare2()
{
    glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(0.6,-0.6,0);
	glVertex3f(0.6,0.6,0);
	glVertex3f(-0.6,-0.6,0);
	glVertex3f(-0.6,0.6,0);
    glEnd();
}

void drawSquare3()
{
    glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(0.6,-0.6,-1);
	glVertex3f(0.6,0.6,-1);
	glVertex3f(-0.6,-0.6,-1);
	glVertex3f(-0.6,0.6,-1);
    glEnd();
}


//Primer forma de profundidad, sin usar depth test
void drawDepth1()
{
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(1,0,0);
   drawSquare();	
   glColor3f(1,1,1);
   drawSquare2();
   glFlush();
}

//Segunda forma de profundidad, usando depth test
void drawDepth2()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_DEPTH);
   glColor3f(1,0,0);
   drawSquare();	
   glColor3f(1,1,1);
   drawSquare3();
   glDisable(GL_DEPTH);
   glFlush();
}

void init()
{
    glClearColor(0,0,0,0);
}
 
void initWindow(){
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Hello OpenGL");
}


//Funcion para manejar los eventos de teclado
//Por el momento solo cierra la ventana si presionan escape
void keyInput(unsigned char key, int x, int y)
{
   switch(key) 
   {	  
      case 27:
         exit(0);
         break;
      default:
         break;
   }
}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    initWindow();
    init();  
    glutDisplayFunc(drawDepth2);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyInput);//maneja los eventos de teclado que se definan en la funcion de parametro
    glutMainLoop();

    return 0;
}
