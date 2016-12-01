/*************************************************************************/
/*                                                                       */
/*                 glig.h LIBRERIA DE MODELADO GEOMETRICO	             */
/*                                                                       */
/*   Rev. 3.0  01/09/2012   Universidad Jaume I de Castellón             */
/*                                                                       */
/*************************************************************************/



#ifndef GLIG_H
#define GLIG_H

/* Devuelve la coordenada x de un punto en R3 a partir de un punto (u,v) */
float xSuperQuadric(float u, float v, float R, float s1, float s2);

/* Devuelve la coordenada y de un punto en R3 a partir de un punto (u,v) */
float ySuperQuadric(float u, float v, float R, float s1, float s2);

/* Devuelve la coordenada z de un punto en R3 a partir de un punto (u,v) */
float zSuperQuadric(float u, float v, float R, float s1, float s2);

// Crea la esfera haciendo lonchas
void igCreateQuadricObject(int pu, int pv, float uMax, float vMax, float R, float s1, float s2);

void igWireSphere(int pu, int pv);
void igWireRulo(int pu, int pv);
void igWireDado(int pu, int pv);
void igWireSemiSphere(int pu, int pv);

void igWireCubo(void);
void igWireCuboSize(float size);

void igWireCone(int pu, int pv);

#endif