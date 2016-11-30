/*************************************************************************/
/*                                                                       */
/*   modelado.c                                                          */
/*   Rev. 3.0  01/09/2012   Universidad Jaume I de Castellón             */
/*                                                                       */
/*************************************************************************/

#include <stdio.h>
#include "glig.h"
#include "modelado.h"


/******************************************************************************************/
/* Crea las distintas display lists                                                       */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void IniciaDisplayLists (void)
{
	CreaArco ();
	CreaArcos ();
	CreaSuelo ();
	CreaEscena ();
}


/******************************************************************************************/
/* Dibuja la escena                                                                       */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void DibujaEscena (void)
{
	glCallList (escena);
}


/******************************************************************************************/
/* Crea una display list para un arco                                                     */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void CreaArco (void)
{
	arco = glGenLists (1);

	if (arco != 0)
	{
		glNewList (arco, GL_COMPILE);
		glPushMatrix();
			glTranslatef(0.75,0.0,0.0);
			glScalef(0.5,2.0,0.5);
			igWireCube();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-0.75,0.0,0.0);
			glScalef(0.5,2.0,0.5);
			igWireCube();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0,0.75,0.0);
			glScalef(2.0,0.5,0.5);
			igWireCube();
		glPopMatrix();
		glEndList ();
	}
	else puts ("Se ha producido un error creando la display list para un arco.");
}


/******************************************************************************************/
/* Crea una display list para todos los arcos                                             */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void CreaArcos (void)
{
	int i;

	arcos = glGenLists (1);

	if (arcos != 0)
	{
		glNewList (arcos, GL_COMPILE);
		glScalef(0.9,0.9,0.9);
		for(i = 0; i < 12; i++)
		{
			glPushMatrix();
				glRotatef(i*30.0,0.0,1.0,0.0);
				glTranslatef(0.0,0.0,-2.0);
				glScalef(0.5,0.5,0.5);
				/*arco();*/
				glCallList (arco);
			glPopMatrix();
		}
		glEndList ();
	}
	else puts ("Se ha producido un error creando la display list para los arcos.");
}


/******************************************************************************************/
/* Crea una display list para el suelo                                                    */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void CreaSuelo (void)
{
	suelo = glGenLists (1);

	if (suelo != 0)
	{
		glNewList (suelo, GL_COMPILE);
		glPushMatrix();
			glTranslatef(0.0,-0.5,0.0);
			glRotatef(12.0,0.0,1.0,0.0);
			glScalef(2.0,0.005,2.0);
			igWireCone(12,6);
		glPopMatrix();
		glEndList ();
	}
	else puts ("Se ha producido un error creando la display list para el suelo.");
}


/******************************************************************************************/
/*  Crea una display list para toda la escena                                             */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void CreaEscena(void)
{
	escena = glGenLists (1);

	if (escena != 0)
	{
		glNewList (escena, GL_COMPILE);
		glPushMatrix();
			glScalef(3.0,3.0,3.0);
			glPushMatrix();
				glTranslatef(0.0,0.0,-5.0);
				glColor3f(0.0,1.0,1.0);
				/*arcos();*/
				glCallList (arcos);
				glColor3f(1.0,0.0,0.0);
				/*suelo();*/
				glCallList (suelo);
			glPopMatrix();
			glPushMatrix();
				glColor3f(0.0,1.0,1.0);
				/*arcos();*/
				glCallList (arcos);
				glColor3f(0.0,1.0,0.0);
				/*suelo();*/
				glCallList (suelo);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0,0.0,5.0);
				glColor3f(0.0,1.0,1.0);
				/*arcos();*/
				glCallList (arcos);
				glColor3f(0.0,0.0,1.0);
				/*suelo();*/
				glCallList (suelo);
			glPopMatrix();
		glPopMatrix();
		glEndList ();
	}
	else puts ("Se ha producido un error creando la display list de la escena.");
}