/*************************************************************************/
/*                                                                       */
/*                 glig.c LIBRERIA DE MODELADO GEOMETRICO	             */
/*                                                                       */
/*   Rev. 3.0  01/09/2012   Universidad Jaume I de Castellón             */
/*                                                                       */
/*************************************************************************/

/***************** INCLUDES DE LAS LIBRERIAS NECESARIAS ******************/
#include <gl/glut.h>
#include <math.h>
#include <stdio.h>
#include "glig.h"

#define PI 3.1415926535897932
#define ALFA (0.5-v)*PI
#define BETA 2*PI*u

/************************* FUNCIONES BASICAS **********************************************/
/******************************************************************************************/
/* Devuelve la coordenada x de un punto en R3 a partir de un punto (u,v)                  */
/*   de un espacio parametrico en R2                                                      */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: La coordenada x de un punto en R3                                              */
/******************************************************************************************/
float xSuperQuadric (float u, float v, float R, float s1, float s2)
{
	float cosalfa, cosbeta, powcosalfa, powcosbeta;

	cosalfa = (float)cos(ALFA);
	cosbeta = (float)cos(BETA);

	if(cosalfa > 0.0)
		powcosalfa = (float)pow(cosalfa,s1);
	else
		powcosalfa =(float) - pow(- cosalfa,s1);

	if(cosbeta > 0.0)
		powcosbeta = (float)pow(cosbeta,s2);
	else
		powcosbeta = (float) - pow(- cosbeta,s2);

	return (R*powcosalfa*powcosbeta);

}


/******************************************************************************************/
/* Devuelve la coordenada y de un punto en R3 a partir de un punto (u,v)                  */
/*   de un espacio parametrico en R2                                                      */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: La coordenada y de un punto en R3                                              */
/******************************************************************************************/
float ySuperQuadric (float u, float v, float R, float s1, float s2)
{
	float sinalfa, powsinalfa;

	sinalfa = (float)sin(ALFA);

	if(sinalfa > 0.0)
		powsinalfa = (float)pow(sinalfa,s1);
	else
		powsinalfa = (float)- pow(- sinalfa,s1);

	return (R*powsinalfa);
}


/******************************************************************************************/
/* Devuelve la coordenada de un punto en R3 a partir de un punto (u,v)                    */
/*   de un espacio parametrico en R2                                                      */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: La coordenada z de un punto en R3                                              */
/******************************************************************************************/
float zSuperQuadric(float u, float v, float R, float s1, float s2)
{
	float cosalfa, sinbeta, powcosalfa, powsinbeta;

	cosalfa = (float)cos(ALFA);
	sinbeta=(float)sin(BETA);

	if(cosalfa > 0.0)
		powcosalfa = (float)pow(cosalfa,s1);
	else
		powcosalfa=(float) - pow(- cosalfa,s1);

	if(sinbeta > 0.0)
		powsinbeta = (float)pow(sinbeta,s2);
	else
		powsinbeta = (float) - pow(- sinbeta,s2);

	return(R*powcosalfa*powsinbeta);
}

// Crea la esfera haciendo lonchas
void igCreateQuadricObject(int pu, int pv, float uMax, float vMax, float R, float s1, float s2)
{

	float u, v, inc_u, inc_v;
	float x, y, z;
	int i, j;

	v = 0.0f;
	u = 0.0f;

	inc_u = uMax / pu;
	inc_v = vMax / pv;

	for (j = 0; j < pv; j++) {
		glBegin(GL_LINE_LOOP);

		u = 0.0f;

		for (i = 0; i <= pu; i++)
		{
			x = xSuperQuadric(u, v, R, s1, s2);
			y = ySuperQuadric(u, v, R, s1, s2);
			z = zSuperQuadric(u, v, R, s1, s2);

			glVertex3f(x, y, z);
			u = u + inc_u;
		}

		glEnd();
		v = v + inc_v;
	}

	v = 0.0f;
	u = 0.0f;

	for (i = 0; i < pu; i++) {
		glBegin(GL_LINE_STRIP);
		v = 0.0f;
		for (j = 0; j <= pv; j++) {
			x = xSuperQuadric(u, v, R, s1, s2);
			y = ySuperQuadric(u, v, R, s1, s2);
			z = zSuperQuadric(u, v, R, s1, s2);

			glVertex3f(x, y, z);
			v = v + inc_v;
		}
		u = u + inc_u;
		glEnd();
	}
}

void igWireSphere(int pu, int pv) {
	igCreateQuadricObject(pu, pv, 1.0, 1.0, 1, 1, 1);
}

void igWireRulo(int pu, int pv) {
	igCreateQuadricObject(pu, pv, 1.0, 1.0, 1, 0.5, 1);
}

void igWireDado(int pu, int pv) {
	igCreateQuadricObject(pu, pv, 1.0, 1.0, 1, 0.5, 0.5);
}

void igWireSemiSphere(int pu, int pv) {
	igCreateQuadricObject(pu, pv, 1.0, 0.5, 1, 1, 1);
}

void igWireCubo(void) { igWireCuboSize(1.0); }

void igWireCuboSize(float size) {
	glBegin(GL_LINE_LOOP);

	float l = size / 2;

	//aristas traseras
	glVertex3f(-l, -l, -l);
	glVertex3f(l, -l, -l);
	glVertex3f(l, l, -l);
	glVertex3f(-l, l, -l);
	glVertex3f(-l, -l, -l);

	//parte delantera
	glVertex3f(-l, -l, l);
	glVertex3f(-l, l, l);
	glVertex3f(l, l, l);
	glVertex3f(l, -l, l);
	glVertex3f(-l, -l, l);

	//lado izquierdo
	glVertex3f(-l, -l, -l);
	glVertex3f(-l, -l, l);
	glVertex3f(-l, l, l);
	glVertex3f(-l, l, -l);
	glVertex3f(l, l, -l);
	glVertex3f(l, l, l);
	glVertex3f(l, -l, l);
	glVertex3f(l, -l, -l);

	glEnd();
}

void igWireCone(int pu, int pv) {
	igCreateQuadricObject(pu, pv, 1.0, 0.5, 1, 2, 1);
}
