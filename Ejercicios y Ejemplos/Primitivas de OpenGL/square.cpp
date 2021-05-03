#include <GL/glut.h>


void reshape(int width, int height)
{
    //glViewport(0, 0, 500, 500);
    glOrtho(-1, 1, -1, 1, -1, 1);//0,100,0,100,-1,1
}
 

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
	glVertex2f(0.5,0.5);
	glVertex2f(-0.5,0.5);
	glVertex2f(-0.5,-0.5); 
	glVertex2f(0.5,-0.5);	
    glEnd();
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
    glutCreateWindow("Square OpenGL");
}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    initWindow();
    init();  

    glutDisplayFunc(draw);

    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;

}
