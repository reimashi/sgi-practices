#include <gl/glut.h>
#include <stdio.h>
#include "glig.h"

void SetupWindow(GLsizei ancho, GLsizei alto)
{
	/* Definicion del viewport */
	glViewport(0, 0, ancho, alto);

	/* Definicion de la vista */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0*(GLfloat)alto / (GLfloat)ancho, 2.0*(GLdouble)alto / (GLfloat)ancho, -2.0, 2.0);
}

void OpenWindow(int numeroArgumentos, char ** listaArgumentos)
{
	glutInit(&numeroArgumentos, listaArgumentos);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(VentanaAncho, VentanaAlto);
	glutInitWindowPosition(VentanaX, VentanaY);
	glutCreateWindow(listaArgumentos[0]);
	glutDisplayFunc(Dibuja);
	glutReshapeFunc(TamanyoVentana);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); /* Establece el color de borrado */
	glClear(GL_COLOR_BUFFER_BIT); /* Borra el buffer de color */
	glColor3f(1.0f, 1.0f, 1.0f); /* Establece el color de dibujo */
}