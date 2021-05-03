#include <GL/glut.h>

//Reajuste de la ventana 
void reshape(int width, int height)
{   
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
 
//Esta es la funcion que va a dibujar algo en pantalla
void draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    glLineWidth(50);//variable de estado para aumentar el ancho de las rectas

    glEnable(GL_LINE_STIPPLE);//activar lineas punteadas
    glLineStipple(1, 0x1111);
    glBegin(GL_LINES);
	glColor3f(1,0,0);
	glVertex2f(0.8,0.8);
	glVertex2f(-0.8,0.8);
 	glColor3f(0,0,1);
	glVertex2f(-0.8,-0.8); 
	glVertex2f(0.8,-0.8);	
    glEnd();

    glLineStipple(1,0x0101);
    glColor3f(0,1,0);
    glBegin(GL_LINES);
	glVertex2f(0.5,0.5);
	glVertex2f(-0.5,0.5);
	glColor3f(1,1,0);
	glVertex2f(-0.5,-0.5); 
	glVertex2f(0.5,-0.5);	
    glEnd();
    glDisable(GL_LINE_STIPPLE);
    glFlush();
}

void init()
{
    glClearColor(0,0,0,0);
}

//Inicializacion de la ventana
void initWindow(){
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Square OpenGL");
}

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

    glutDisplayFunc(draw);

    glutReshapeFunc(reshape);

    glutKeyboardFunc(keyInput);

    glutMainLoop();

    return 0;

}
