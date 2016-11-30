/*************************************************************************/
/*                                                                       */
/*   examinar.c                                                          */
/*   Rev. 3.0  01/09/2012   Universidad Jaume I de Castellón             */
/*                                                                       */
/*************************************************************************/

/***************** INCLUDES DE LAS LIBRERIAS NECESARIAS ******************/
#include <gl/glut.h>
#include <stdio.h>
#include <math.h>
#include "examinar.h"
#include "glig.h"
#include "modelado.h"


/******************************************************************************************/
/* Establece el area visible y el tipo de proyeccion                                      */
/* Parametros: int ancho --> Ancho del area visible                                       */
/*             int alto --> Alto del area visible                                         */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void TamanyoVentana (GLsizei ancho, GLsizei alto)
{
    /* Definicion del viewport */
	glViewport(0, 0, ancho, alto);  

    /* Definicion de la vista */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(-10.0, 10.0, -10.0*(GLfloat)alto/(GLfloat)ancho, 10.0*(GLdouble)alto/(GLfloat)ancho, -20.0, 20.0);
	gluPerspective (60.0, (GLdouble)alto/(GLdouble)ancho, 1.0, 50.0);
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
	glutInitWindowSize (VentanaAncho, VentanaAlto);
	glutInitWindowPosition (VentanaX, VentanaY);
	glutCreateWindow (listaArgumentos[0]);
	glutDisplayFunc (Dibuja);
	glutReshapeFunc (TamanyoVentana);
	glClearColor (0.0f, 0.0f, 0.0f, 0.0f); /* Establece el color de borrado */
	glClear (GL_COLOR_BUFFER_BIT); /* Borra el buffer de color */
	glColor3f (1.0f, 1.0f, 1.0f); /* Establece el color de dibujo */
}


/******************************************************************************************/
/* Define las acciones tras una pulsacion del teclado                                     */
/* Parametros: unsigned char key --> Codigo de la tecla pulsada                           */
/*             int x --> Coordenada x del cursor en el momento de pulsar la tecla         */
/*             int y --> Coordenada y del cursor en el momento de pulsar la tecla         */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void Teclado (unsigned char tecla, int x, int y)
{
	switch (tecla)
	{
		case 27 : /* Codigo de la tecla de Escape */
			exit (0);
			break;

		case 'w' :
			modo = WALK;
			printf ("Modo = WALK      \r");
			break;

		case 'e' :
			modo = EXAMINAR;
			printf ("Modo = EXAMINAR    \r");
			break;

		case 'f' :
			modo = FLY;
			printf ("Modo = FLY      \r");
			break;
	}
}


/******************************************************************************************/
/* Define las acciones tras una pulsacion del teclado ampliado                            */
/* Parametros: unsigned char key --> Codigo de la tecla pulsada                           */
/*             int x --> Coordenada x del cursor en el momento de pulsar la tecla         */
/*             int y --> Coordenada y del cursor en el momento de pulsar la tecla         */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void TecladoAmpliado (int tecla, int x, int y)
{
	switch (tecla)
	{
		case GLUT_KEY_UP : // Pulsacion cursor arriba del teclado ampliado
			beta = beta + 1.50;
			if (beta > 360.0) beta = beta - 360.0;
			break;

		case GLUT_KEY_DOWN : // Pulsacion cursor abajo del teclado ampliado
			beta = beta - 1.50;
			if (beta < 0.0) beta = beta + 360.0;
			break;

		case GLUT_KEY_RIGHT : // Pulsacion cursor derecha del teclado ampliado
			alfa = alfa + 15.0;
			if (alfa > 360.0) alfa = alfa - 360.0;
			break;

		case GLUT_KEY_LEFT : // Pulsacion cursor izquierda del teclado ampliado
			alfa = alfa - 15.0;
			if (alfa < 0.0) alfa = alfa + 360.0;
			break;
	}
	glutPostRedisplay ();
}


/* Rutina de definición de eventos */
/******************************************************************************************/
/* Inicia las funciones de callback                                                       */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void IniciaFuncionesCallback (void)
{
	glutKeyboardFunc (Teclado);
	glutSpecialFunc (TecladoAmpliado);
}


/******************************************************************************************/
/* Funcion de dibujado                                                                    */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void Dibuja (void)
{
	glClear (GL_COLOR_BUFFER_BIT);
 
    /* Transformacion de la camara */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotated (beta, 1.0,0.0,0.0);
    glRotated (alfa, 0.0,1.0,0.0);

	//gluLookAt (ox, oy, oz, ix, iy, iz, 0, 1, 0);

	/* Llamadas a las display lists */
	DibujaEscena ();

	glFlush();
}


/******************************************************************************************/
/* Funcion principal                                                                      */
/* Parametros: int numeroArgumentos --> El numero de argumentos en la llamada al programa */
/*             char ** listaArgumentos --> Vector de cadenas con cada argumento           */
/* Salida: Un entero que se devuelve al sistema al acabar la ejecucion del programa       */
/******************************************************************************************/
int main(int numArgumentos, char ** listaArgumentos)
{	
	/* Creación de la ventana de la aplicación */
	AbreVentana (numArgumentos, listaArgumentos);

	/* Rutinas para el control de eventos */
    IniciaFuncionesCallback ();

	/* Crea las display list de cada cuadrica */
	IniciaDisplayLists ();

	printf ("Modo = WALK\r");
	
	/* A la espera de eventos.... */
	glutMainLoop();

	return (0);
}

