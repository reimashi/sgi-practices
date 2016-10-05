#include <gl/glut.h>
#include <stdio.h>
#include "raton.h"

/******************************************************************************************/
/* Funcion de dibujado                                                                    */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void Dibuja(void)
{
	/* Dibuja un segmento de linea entre el punto incial y el final */
	glBegin (GL_LINES);
		glVertex2i (InicioX, VentanaAlto-InicioY);
		glVertex2i (FinX, VentanaAlto-FinY);
	glEnd ();

	/* Se asegura de que se ejecutan todas las ordenes */
	glFlush ();
}


/******************************************************************************************/
/* Establece el area visible y el tipo de proyeccion                                      */
/* Parametros: int ancho --> Ancho del area visible                                       */
/*             int alto --> Alto del area visible                                         */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void TamanyoVentana (int ancho, int alto)
{
	glMatrixMode(GL_PROJECTION); /* Activamos la matriz de proyeccion */
	glLoadIdentity(); /* la iniciamos con la matriz identidad */
	glOrtho(0.0, ancho, 0.0, alto, -1.0, 1.0); /* establecemos los parametros de la proyeccion */
	glViewport (0, 0, ancho, alto); /* establecemos los parametros del area de dibujo */
	VentanaAncho = ancho; /* guardamos el ancho y alto de la ventana */
	VentanaAlto = alto;
	glClear (GL_COLOR_BUFFER_BIT); /* borramos la ventana */
	InicioX = InicioY = FinX = FinY = Pulsaciones = 0; /* Inica las variables */
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
void TecladoCallback (unsigned char tecla, int x, int y)
{
	switch (tecla)
	{
		case 27 : /* Codigo de la tecla de Escape */
			exit (0);
			break;

		case 'r' :
			glColor3f (1.0f, 0.0f, 0.0f);
			break;

		case 'g':
			glColor3f(0.0f, 1.0f, 0.0f);
			break;

		case 'b':
			glColor3f(0.0f, 0.0f, 1.0f);
			break;

		case 'R':
			glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			glFlush();
			break;

		case 'G':
			glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			glFlush();
			break;

		case 'B':
			glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			glFlush();
			break;

		case 'Y':
			glClearColor(1.0f, 1.0f, 0.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			glFlush();
			break;
	}
}


/******************************************************************************************/
/* Funcion de callback de las acciones del raton                                          */
/* Parametros: int boton --> Codigo del boton que se ha pulsado                           */
/*             int estado --> Estado del boton                                            */
/*             int x --> Coordenada x del cursor en el momento de pulsar la tecla         */
/*             int y --> Coordenada y del cursor en el momento de pulsar la tecla         */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void RatonCallback (int boton, int estado, int x, int y)
{
	if (boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN)
	{
		InicioX = x;
		InicioY = y;
		InicioActivo = true;
	}
	else if (boton == GLUT_LEFT_BUTTON && estado == GLUT_UP)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glFlush();

		FinX = x;
		FinY = y;
		glutPostRedisplay();

		InicioActivo = false;
	}
	else if (boton == GLUT_RIGHT_BUTTON && estado == GLUT_DOWN)
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glFlush();
	}
}

void RatonMotionCallback(int x, int y) {
	if (InicioActivo) {
		glClear(GL_COLOR_BUFFER_BIT);
		glFlush();

		FinX = x;
		FinY = y;
		glutPostRedisplay();
	}
}


/******************************************************************************************/
/* Inicia las funciones de callback                                                       */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void IniciaFuncionesCallback (void)
{
	glutKeyboardFunc (TecladoCallback);
	glutMouseFunc(RatonCallback);
	glutMotionFunc(RatonMotionCallback);
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
	IniciaFuncionesCallback ();

	/* Establece el bucle principal de control de OpenGL */
	glutMainLoop();

	return (0);
}