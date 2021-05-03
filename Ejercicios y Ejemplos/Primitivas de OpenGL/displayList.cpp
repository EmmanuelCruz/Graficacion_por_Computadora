#include <iostream>
#include <GL/glut.h>

using namespace std;

static int isWire = 0;

static unsigned int theCubes;//cubo

static unsigned int base;//indice base de las display list

static unsigned int Board;//tablero

static unsigned int offset[6] = {0, 2, 1, 1, 0, 2}; //Arreglo de los desplazamientos de las display list

static float vertices[8][2] = { 
	 	       	     	{30,30},
			     	{10,10},
			     	{70,30},
			     	{90,10},
			     	{70,70},
			     	{90,90},
			     	{30,70},
			     	{10,90}
		              };

//Cuadrado
void drawSquare(float x, float y, float width)
{
   
   glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(x,y);
        glVertex2f(x+width,y);
	glVertex2f(x,y+width);
	glVertex2f(x+width,y+width);
   glEnd();

}

//Display list
void DisplayFigListConfig()
{
   theCubes = glGenLists(1);
   glNewList(theCubes, GL_COMPILE);
   //glColor3f(1,0,0);//cambio de estado
   drawSquare(0,0,10);
   glEndList();
}

//Display List Editable
void DisplayPolygon()
{
   float *v1 = { vertices[3] };
   float *v2 = { vertices[1] };
   float *v3 = { vertices[7] };
   
   glNewList(1,GL_COMPILE);
	glVertex2fv(v1); 
   glEndList();

   glNewList(2,GL_COMPILE);
	glVertex2fv(v2);
   glEndList();
   
   glNewList(3,GL_COMPILE);
	glVertex2fv(v3);
   glEndList();

   glNewList(4,GL_COMPILE);
	glBegin(GL_POLYGON);
		glCallList(1);
		glCallList(2);
		glCallList(3);
	glEnd();
   glEndList();

}

//Display List cambiante
void DisplayPolygon(float * v1, float * v2, float * v3)
{
 
   glNewList(1,GL_COMPILE);
	glVertex2fv(v1); 
   glEndList();

   glNewList(2,GL_COMPILE);
	glVertex2fv(v2);
   glEndList();
   
   glNewList(3,GL_COMPILE);
	glVertex2fv(v3);
   glEndList();

   glNewList(4,GL_COMPILE);
	glBegin(GL_POLYGON);
		glCallList(1);
		glCallList(2);
		glCallList(3);
	glEnd();
   glEndList();

}

//Multiples display list
void DisplayMultList()
{
   base = glGenLists(3); 

   glListBase(base); 

   glNewList(base, GL_COMPILE);
      glColor3f (1.0, 0.0, 0.0); 
      glBegin(GL_TRIANGLES);
      glVertex2f(10.0, 10.0);
      glVertex2f(20.0, 10.0);
      glVertex2f(20.0, 40.0);
      glEnd();
      glTranslatef(15.0, 0.0, 0.0); 
   glEndList();

   glNewList(base + 1, GL_COMPILE);
      glColor3f(0.0, 1.0, 0.0); 
      glBegin(GL_QUADS);
      glVertex2f(10.0, 10.0);
      glVertex2f(20.0, 10.0);
      glVertex2f(20.0, 40.0);
      glVertex2f(10.0, 40.0);
      glEnd();
      glTranslatef(15.0, 0.0, 0.0); 
   glEndList();

   glNewList(base + 2, GL_COMPILE);
      glColor3f(0.0, 0.0, 1.0);  
      glBegin(GL_POLYGON);
      glVertex2f(10.0, 10.0);
      glVertex2f(20.0, 10.0);
      glVertex2f(20.0, 20.0);
      glVertex2f(15.0, 40.0);
      glVertex2f(10.0, 20.0);
      glEnd();
      glTranslatef(15.0, 0.0, 0.0); 
   glEndList();

}

void drawMulSquare()
{

   glColor3f(1.0, 1.0, 1.0);
   glPushMatrix();
   glTranslatef(0.0, 60.0, 0.0);
   glCallList(theCubes); 
   glPopMatrix();

   glColor3f(1.0, 0.0, 0.0);
   glPushMatrix();
   glTranslatef(30.0, 60.0, 0.0);
   glCallList(theCubes); 
   glPopMatrix();

   glColor3f(0.0, 1.0, 0.0);
   glPushMatrix();
   glTranslatef(60.0, 60.0, 0.0);
   glCallList(theCubes); 
   glPopMatrix();

   glColor3f(0.0, 0.0, 1.0);
   glPushMatrix();
   glTranslatef(0.0, 30.0, 0.0);
   glCallList(theCubes); 
   glPopMatrix();

}

void drawPolygon(float * v1, float * v2, float *v3)
{
   DisplayPolygon(v1,v2,v3);
   glCallList(4);
}

void drawBoard()
{
   glCallList(Board); 
}

void init()
{
   
   DisplayFigListConfig();
   //DisplayPolygon();
   //DisplayMultList();

   glClearColor(0,0,0,0);

}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (isWire) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	

    drawMulSquare();

    //drawSquare(0,0,20);//cambio de estado


   //Display list editable
/*
    glColor3f(1,1,1);

    drawPolygon(vertices[1], vertices[4], vertices[7]);

    drawPolygon(vertices[2], vertices[3], vertices[4]);

    glPushMatrix();
    glTranslatef(-30,0,0);
    glColor3f(1,0,0);
    glCallList(4);
    glPopMatrix();
*/

    //multiples display lists
    //glLoadIdentity();
    //t p r r t p
    //glCallLists(6, GL_INT, offset); 
   
    glFlush();

}

void reshape(int width, int height)
{
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,100,0,100,-1,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
 
void initWindow(){
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Display Lists OpenGL");
}

void keyInput(unsigned char key, int x, int y)
{
   switch(key) 
   {	  
     case ' ':
         if (isWire == 0) isWire = 1;
         else isWire = 0;
         glutPostRedisplay();
         break;	
     case 27:
         exit(0);
         break;
      default:
         break;
   }
}

void printInteraction(void)
{
   cout << "Presiona espacio para intercambiar entre Fill y Line." << endl;
}


int main(int argc, char **argv)
{

    printInteraction();

    glutInit(&argc, argv);
    initWindow();
    init();  

    glutDisplayFunc(display);

    glutReshapeFunc(reshape);

    glutKeyboardFunc(keyInput);

    glutMainLoop();

    return 0;

}







































