#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>

void init ( void )
{
	/* En esta sección se indicarán los parámetros de inicialización de OpenGL (estado de buffers, .) */
}

void display ( void )
{
	/* En esta sección, se indicarán las características de OpenGL .incluyendo el código necesario para
	representar los objetos en pantalla */
}

void reshape ( int w, int h)
{
	/* En esta sección, se indicará el código a ejecutar cuando se produce una redimensión de la ventana.
	También es utilizada para definir el área de proyección de la figura en la ventana.*/
}

void keyboard (unsigned char key, int x, int y)
{
	/* En esta sección, se indicarán las tareas a realizar ante un evento de teclado. Se ha de tener presente
	que todos los eventos de teclado no producen un redibujado de la pantalla, por lo que es conveniente
	forzar este redibujado con funciones como glutPostRedisplay () */
}

void mouse ( int button, int state, int x, int y )
{
	/* En esta sección, se indicarán las tareas a realizar ante un evento de ratón. Se ha de tener presente
	que todos los eventos de ratón no producen un redibujado de la pantalla, por lo que es conveniente
	forzar este redibujado con funciones como glutPostRedisplay () */
}

int main ( int argc, char** argv )
{
	glutInit (&argc, argv);										//Esta función es la encargada de inicializar GLUT, además de realizar un análisis de los parámetros suministrados en la línea de comandos.
	glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);	//Define el modo en el que se tiene que dibujar la ventana, como en otras funciones los parámetros a utilizar se definen con bit o máscaras de bits. (color|buffer|tipo de buffer)
	glutInitWindowSize (800,600);								//Esta función define el tamaño de la ventana expresada en pixeles.
	glutInitWindowPosition (100,100);							//Esta función indica la posición inicial de la ventana desde la posicion dada de la pantalla.
	glutCreateWindow ("Plantilla openGL");						//Esta función es la que propiamente crea la ventana, el parámetro es el nombre asignado a la misma.
	init ();													//En esta función definida por el usuario, se inicializan parámetros propios de OpenGL antes de pasar el control del programa a GLUT.
	glutReshapeFunc (reshape);									//Esta función indica la llamada a ejecutar cuando se realiza una redimensión de la ventana. También es utilizada para definir el área de proyección de la figura en la ventana.
	glutKeyboardFunc (keyboard);								//Esta función indica la llamada utilizada por GLUT ante un evento de teclado.
	glutMouseFunc (mouse);										//Esta función indica la llamada utilizada por GLUT ante un evento de mouse.
	glutDisplayFunc (display);									//Aquí se define la primer llamada. La función pasada como parámetro, será llamada cada vez que GLUT determine que la ventana debe ser redibujada ( por ejemplo, al maximizar, poner otras ventanas encima, ...)
	glutMainLoop ();											//Esta función cede el control de flujo del programa a GLUT, que a partir de estos “eventos”, irá llamando a las funciones que han sido pasadas como callback.
	return 0;
}