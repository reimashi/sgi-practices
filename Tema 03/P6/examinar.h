/*************************************************************************/
/*                                                                       */
/*   examinar.c                                                          */
/*   Rev. 3.0  01/09/2012   Universidad Jaume I de Castellón             */
/*                                                                       */
/*************************************************************************/

#ifndef EXAMINAR_H
#define EXAMINAR_H

/* Variables Globales del modulo */
int VentanaAncho = 500, VentanaAlto = 500; /* Tamanyo de la ventana */
int VentanaX = 100, VentanaY = 100; /* Posicion de la ventana */
GLdouble  alfa = 0.0, beta = 0.0;
GLuint cuadrica;

/* Abre una ventana OpenGL */
void AbreVentana (int numeroArgumentos, char ** listaArgumentos);

/* Funcion de dibujado */
void Dibuja(void);

/* Establece el area visible */
void TamanyoVentana (int alto, int ancho);

/* Inicia las funciones de Callback */
void IniciaFuncionesCallback (void);

/* Define las acciones tras una pulsacion del teclado */
void Teclado (unsigned char tecla, int x, int y);

#endif