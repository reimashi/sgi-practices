/*************************************************************************/
/*                                                                       */
/*   modelado.c                                                          */
/*   27/10/03  AUTORES: C.Rebollo                                        */
/*                                                                       */
/*************************************************************************/

/***************** INCLUDES DE LAS LIBRERIAS NECESARIAS ******************/
#include "glig.h"
#include "modelado.h"


/******************************************************************************************/
/* Crea los distintos objetos. En este caso iun abeto, si tuviese mas objetos, los pòndría*/
/* a continuación.                                                                        */
/* Parametros: ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void IniciaDisplayLists(void)
{
	/* Descomentar para dibujar los abetos
	CreaAbeto();
	CreaAbetoPush(); */
	/* Descomentar para dibujar la escalera
	CreaEscalera(); */
	CreaArco();
	CreaStonehenge();
}

/******************************************************************************************/
/* Crea una display list para dibujar un abeto                                            */
/* Parametros: ninguno */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/

void CreaEscalera() {
	escalera = glGenLists(1);
	if (escalera != 0) /* Cero no es un identificador valido para una display list */
	{
		glNewList(escalera, GL_COMPILE);

		glPushMatrix();
		glScalef(0.2, 2, 0.2);
		igWireCubo();
		glPopMatrix();

		for (int x = 0; x <= 10; x++) {
			glPushMatrix();
			glRotated(x * 36, 0, 1, 0);
			glTranslatef(0.25, -1 + (x * 0.2), 0);
			glScalef(0.5, 0.1, 0.2);
			igWireCubo();
			glPopMatrix();
		}

		glEndList();
	}
}

void CreaAbeto(void)
{
	abeto = glGenLists(1);
	if (abeto != 0) /* Cero no es un identificador valido para una display list */
	{
		glNewList(abeto, GL_COMPILE);

		glScalef(0.75, 1, 0.75);
		igWireCone(10, 10);

		glTranslatef(0, 0.25, 0);
		glScalef(0.75, 1, 0.75);
		igWireCone(10, 10);

		glTranslatef(0, 0.25, 0);
		glScalef(0.75, 1, 0.75);
		igWireCone(10, 10);

		glTranslatef(0, -0.5, 0);
		// Deshacemos la reducción de 0.75 dos veces usando la operacion (1 / 0.75 / 0.75) * 0.1
		glScalef((1 / 0.75 / 0.75) * 0.1, 1, (1 / 0.75 / 0.75) * 0.1);
		igWireRulo(10, 10);

		glEndList();
	}
}

void CreaAbetoPush(void)
{
	abetopush = glGenLists(1);
	if (abetopush != 0) /* Cero no es un identificador valido para una display list */
	{
		glNewList(abetopush, GL_COMPILE);

		glPushMatrix();
		glScalef(0.75, 1, 0.75);
		igWireCone(10, 10);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0, 0.25, 0);
		glScalef(0.75 * 0.75, 1, 0.75 * 0.75);
		igWireCone(10, 10);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0, 0.25 + 0.25, 0);
		glScalef(0.75 * 0.75 * 0.75, 1, 0.75 * 0.75 * 0.75);
		igWireCone(10, 10);
		glPopMatrix();

		glPushMatrix();
		glScalef(0.1, 1, 0.1);
		igWireRulo(10, 10);
		glPopMatrix();

		glEndList();
	}
}

void CreaArco() {
	arco = glGenLists(1);
	if (arco != 0) /* Cero no es un identificador valido para una display list */
	{
		float alto = 0.6;
		float ancho = 0.15;

		glNewList(arco, GL_COMPILE);

		glPushMatrix();
		glTranslatef(0, alto - ancho / 2, 0);
		glScalef(alto, ancho, ancho);
		igWireCubo();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-(alto / 2) + (ancho / 2), alto / 2, 0);
		glScalef(ancho, alto, ancho);
		igWireCubo();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(+(alto / 2) - (ancho / 2), alto / 2, 0);
		glScalef(ancho, alto, ancho);
		igWireCubo();
		glPopMatrix();

		glEndList();
	}
}

void CreaStonehenge(void) {
	stonehenge = glGenLists(1);
	if (stonehenge != 0) /* Cero no es un identificador valido para una display list */
	{
		glNewList(stonehenge, GL_COMPILE);

		for (int x = 0; x < 12; x++) {
			glPushMatrix();
			glRotated(x * (360 / 12), 0, 1, 0);
			glTranslatef(0, 0, 1.2);
			glCallList(arco);
			glPopMatrix();
		}

		glEndList();
	}
}