#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>

int horas, minutos, segundos;

void sincronizar(){
  time_t t = time(NULL);
  struct tm *horaActual = localtime(&t);
	
  horas = horaActual -> tm_hour;
  minutos = horaActual -> tm_min;
  segundos = horaActual -> tm_sec;
}

//Dibujar un circulo 
void drawCircle( )
{
  float x, y, theta;
  glColor3f(1,1,1);
  glBegin(GL_TRIANGLE_FAN);
  for(int i = 0; i < 100; i++) { 
    theta = 2.0f * 3.1415926f * float(i) / 100.0f;
    x = cos(theta);
    y = sin(theta);
    glVertex2f(x, y);
  }
  glEnd();
  glPushMatrix();
  for (int ang = 0; ang < 360; ang +=6){
    if (ang % 90 == 0){
      glColor3f(0.0f,0.0f,0.0f);
      glBegin(GL_POLYGON);
      glVertex2f(0.02f,0.9f);
      glVertex2f(0.02f,0.98f);
      glVertex2f(-0.02f,0.98f);
      glVertex2f(-0.02f,0.9f);
      glEnd();
    } else{
      if (ang % 30 == 0){
	glColor3f(0.15f,0.15f,0.15f);
	glBegin(GL_POLYGON);
	glVertex2f(0.01f,0.9f);
	glVertex2f(0.01f,0.98f);
	glVertex2f(-0.01f,0.98f);
	glVertex2f(-0.01f,0.9f);
	glEnd();
      } else{
	glColor3f(0.25f,0.25f,0.25f);
	glBegin(GL_LINES);
	glVertex2f(0.0f,0.92f);
	glVertex2f(0.0f,0.98f);
	glEnd();
      }
    }
    glRotatef(6, 0, 0, 1);
  }
  glPopMatrix();
}
//Dibujar las manecillas del reloj 
void manecillas(float anguloHoras, float anguloMinutos, float anguloSegundos)
{
  //manecilla de las horas
  glColor3f(0.25f,0.25f,0.25f);
  glPushMatrix();
  glRotatef(anguloHoras, 0, 0, 1);
  glBegin(GL_POLYGON);
  glVertex2f(0.03f,-0.03f);
  glVertex2f(0.03f,0.6f);
  glVertex2f(0.0f,0.7f);
  glVertex2f(-0.03f,0.6f);
  glVertex2f(-0.03f,-0.03f);
  glEnd();
  glPopMatrix();
  //manecilla de los minutos
  glColor3f(0.5f,0.5f,0.5f);
  glPushMatrix();
  glRotatef(anguloMinutos, 0, 0, 1);
  glBegin(GL_POLYGON);
  glVertex2f(0.02f,-0.02f);
  glVertex2f(0.02f,0.75f);
  glVertex2f(0.0f,0.85f);
  glVertex2f(-0.02f,0.75f);
  glVertex2f(-0.02f,-0.02f);
  glEnd();
  glPopMatrix();
  //manecilla de los segundos
  glColor3f(0.75f,0.75f,0.75f);
  glPushMatrix();
  glRotatef(anguloSegundos, 0, 0, 1);
  glBegin(GL_POLYGON);
  glVertex2f(0.01f,-0.01f);
  glVertex2f(0.01f,0.9f);
  glVertex2f(0.0f,0.95f);
  glVertex2f(-0.01f,0.9f);
  glVertex2f(-0.01f,-0.01f);
  glEnd();
  glPopMatrix();
  //"eje"
  glColor3f(0.0f,0.0f,0.0f);
  glBegin(GL_POLYGON);
  glVertex2f(0.005f,-0.005f);
  glVertex2f(0.005f,0.005f);
  glVertex2f(-0.005f,0.005f);
  glVertex2f(-0.005f,-0.005f);
  glEnd();
}

void reshape(int width, int height)
{
  glViewport(0, 0, (GLsizei)width, (GLsizei)height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1, 1, -1, 1, -2, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void calculaAngulos(float* h, float* m, float* s){
  (*s) = segundos * -6.0f;
  (*m) = minutos * -6.0f;
  (*h) = (horas +((float)(minutos/5)/12.0f)) * -30.0f;
}
 
void draw()
{
  glClear(GL_COLOR_BUFFER_BIT);
  float h, m, s;
  drawCircle();
  calculaAngulos(&h, &m, &s);
  manecillas(h, m, s);
  glFlush();
}


void init()
{
  glClearColor(0,0,0,0);
  sincronizar();
}
 
void initWindow(){
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(20, 20);
  glutInitWindowSize(600, 600);
  glutCreateWindow("Reloj");
}

void tick(int param){
  segundos++;
  if (segundos > 60){
    segundos -= 60;
    minutos++;
    if (minutos > 60){
      minutos -= 60;
      horas++;
      if (horas > 12){
	horas -= 12;
      }
    }
  }
  glutPostRedisplay();
  glutTimerFunc(1000, tick, 0);
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
  glutDisplayFunc(draw);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyInput);//maneja los eventos de teclado que se definan en la funcion de parametro
  glutMainLoop();
  return 0;
}
