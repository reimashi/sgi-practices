#include <gl/glut.h>
#include <stdio.h>
#include "cuadrado.h"

/******************************************************************/
/* Funcion de dibujado                                            */
/* Parametros: Ninguno                                            */
/* Salida: Ninguna                                                */
/******************************************************************/
void Dibuja(void)
{
	/* Establece el color de borrado */
	glClearColor (0.0f, 0.0f, 0.0f, 0.0f);

	/* Borra el buffer de color */
	glClear (GL_COLOR_BUFFER_BIT);

	/* Establece el color de dibujo */
	glColor3f (1.0f, 1.0f, 1.0f);

	/* Crea un poligono 2D (cuadrado) */
	glBegin (GL_POLYGON);
		glVertex2f (-0.5f, -0.5f);
		glVertex2f (-0.5f, 0.5f);
		glVertex2f (0.5f, 0.5f);
		glVertex2f (0.5f, -0.5f);
	glEnd ();

	/* Se asegura de que se ejecutan todas las ordenes */
	glFlush ();
}


/******************************************************************************************/
/* Establece el area visible                                                              */
/* Parametros: int ancho --> Ancho del area visible                                       */
/*             int alto --> Alto del area visible                                         */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void TamanyoVentana (int ancho, int alto)
{
	glViewport (0, 0, ancho, alto);
}


/******************************************************************************************/
/* Inicia las propiedades de la vista                                                     */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void IniciaVista (void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}


/******************************************************************************************/
/* Abre una ventana OpenGL                                                                */
/* Parametros: int numeroArgumentos --> El numero de argumentos en la llamada al programa */
/*             char ** listaArgumentos --> Vector de cadenas con cada argumento           */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void AbreVentana (int numeroArgumentos, char ** listaArgumentos)
{
	glutInit(&numeroArgumentos, listaArgumentos);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (500, 500);
	glutInitWindowPosition (100, 100);
	glutCreateWindow (listaArgumentos[0]);
	glutDisplayFunc (Dibuja);
	glutReshapeFunc (TamanyoVentana);
	IniciaVista ();
}


/******************************************************************************************/
/* Funcion principal                                                                      */
/* Parametros: int numeroArgumentos --> El numero de argumentos en la llamada al programa */
/*             char ** listaArgumentos --> Vector de cadenas con cada argumento           */
/* Salida: Un entero que se devuelve al sistema al acabar la ejecucion del programa       */
/******************************************************************************************/
int main(int numArgumentos, char ** listaArgumentos)
{
	/* Crea la ventana de la aplicaci¢n */
	AbreVentana (numArgumentos, listaArgumentos);

	/* Establece el bucle principal de control de OpenGL */
	glutMainLoop();

	return (0);
}