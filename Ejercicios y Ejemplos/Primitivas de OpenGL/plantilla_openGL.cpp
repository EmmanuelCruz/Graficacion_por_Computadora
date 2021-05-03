#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>

void init ( void )
{
	/* En esta secci�n se indicar�n los par�metros de inicializaci�n de OpenGL (estado de buffers, .) */
}

void display ( void )
{
	/* En esta secci�n, se indicar�n las caracter�sticas de OpenGL .incluyendo el c�digo necesario para
	representar los objetos en pantalla */
}

void reshape ( int w, int h)
{
	/* En esta secci�n, se indicar� el c�digo a ejecutar cuando se produce una redimensi�n de la ventana.
	Tambi�n es utilizada para definir el �rea de proyecci�n de la figura en la ventana.*/
}

void keyboard (unsigned char key, int x, int y)
{
	/* En esta secci�n, se indicar�n las tareas a realizar ante un evento de teclado. Se ha de tener presente
	que todos los eventos de teclado no producen un redibujado de la pantalla, por lo que es conveniente
	forzar este redibujado con funciones como glutPostRedisplay () */
}

void mouse ( int button, int state, int x, int y )
{
	/* En esta secci�n, se indicar�n las tareas a realizar ante un evento de rat�n. Se ha de tener presente
	que todos los eventos de rat�n no producen un redibujado de la pantalla, por lo que es conveniente
	forzar este redibujado con funciones como glutPostRedisplay () */
}

int main ( int argc, char** argv )
{
	glutInit (&argc, argv);										//Esta funci�n es la encargada de inicializar GLUT, adem�s de realizar un an�lisis de los par�metros suministrados en la l�nea de comandos.
	glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);	//Define el modo en el que se tiene que dibujar la ventana, como en otras funciones los par�metros a utilizar se definen con bit o m�scaras de bits. (color|buffer|tipo de buffer)
	glutInitWindowSize (800,600);								//Esta funci�n define el tama�o de la ventana expresada en pixeles.
	glutInitWindowPosition (100,100);							//Esta funci�n indica la posici�n inicial de la ventana desde la posicion dada de la pantalla.
	glutCreateWindow ("Plantilla openGL");						//Esta funci�n es la que propiamente crea la ventana, el par�metro es el nombre asignado a la misma.
	init ();													//En esta funci�n definida por el usuario, se inicializan par�metros propios de OpenGL antes de pasar el control del programa a GLUT.
	glutReshapeFunc (reshape);									//Esta funci�n indica la llamada a ejecutar cuando se realiza una redimensi�n de la ventana. Tambi�n es utilizada para definir el �rea de proyecci�n de la figura en la ventana.
	glutKeyboardFunc (keyboard);								//Esta funci�n indica la llamada utilizada por GLUT ante un evento de teclado.
	glutMouseFunc (mouse);										//Esta funci�n indica la llamada utilizada por GLUT ante un evento de mouse.
	glutDisplayFunc (display);									//Aqu� se define la primer llamada. La funci�n pasada como par�metro, ser� llamada cada vez que GLUT determine que la ventana debe ser redibujada ( por ejemplo, al maximizar, poner otras ventanas encima, ...)
	glutMainLoop ();											//Esta funci�n cede el control de flujo del programa a GLUT, que a partir de estos �eventos�, ir� llamando a las funciones que han sido pasadas como callback.
	return 0;
}