/*************************************************************************/
/*                                                                       */
/*   modelado.h                                                          */
/*   Rev. 27/10/03   AUTORES: C.Rebollo
/*                                                                       */
/*************************************************************************/

#ifndef MODELADO_H
#define MODELADO_H

#include <gl/glut.h>


/* Identificadores de las display list */
GLuint abeto,abetopush,escalera, arco, stonehenge;

/* Definición Funciones de modelado */
void IniciaDisplayLists (void);
void CreaAbeto(void);
void CreaAbetoPush(void);
void CreaEscalera(void);
void CreaArco(void);
void CreaStonehenge(void);

#endif
