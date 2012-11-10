/*
 * parser.h
 *
 *  Created on: 26/10/2012
 *      Author: utnso
 */

#ifndef PARSER_H_
#define PARSER_H_

	// Macro para el PCB
	#define FIN -2

	// Macros para el comparador de saltos
	#define IGUAL 0
	#define DISTINTO 1

	// Macros para retornar
	#define SALTO -3
	#define NOSALTO -4
	#define ERROR -5
	#define IO_BLOQUEADA -6
	#define IO_OK -7

	#include "headers/Estructuras.h"
	#include "headers/ManejoDeProcesos.h"
	#include <string.h>

	int parsear(char* linea, imagen_proceso_t* proceso);
	int esUnInterprete(char* linea);
	int esUnComentario(char* linea);
	int determinarTipoDeLinea(char* linea);
	char* primerPalabra(char* linea);
	int esUnaLineaVacia(char* linea);
	int esUnaEtiqueta(char* linea);
	int especificaTiempo(char* linea);
	int esUnaAsignacion(char* linea);
	int esUnaEntradaSalida(char* linea);
	int imprimir(char* linea, imagen_proceso_t proceso);
	int saltar(char* linea , imagen_proceso_t* proceso,int comparador);
	int resultadoExpresion(char* linea,imagen_proceso_t proceso);
	int asignarVariable(char* linea,imagen_proceso_t proceso);
	int ejecutarIO(char* linea);
	int resultadoExpresion(char* expresion,imagen_proceso_t proceso);
	int obtenerResultado(char* expresion,int posicionOperador,int finCadena,imagen_proceso_t proceso);
	int obtenerOperando(char* expresion,int inicioOperando, int finOperando,imagen_proceso_t proceso);
	int32_t esUnaFuncion(char* linea);
	int32_t buscarStringEIr(char* stringBuscado,imagen_proceso_t* proceso);
	void irAFuncion(char* linea,imagen_proceso_t* proceso);
	enum tipoDeLinea { INTERPRETE , COMENTARIO , OTRO , DECLARACION_DE_VARIABLES,
						LINEA_VACIA, COMIENZO_PROGRAMA, FIN_PROGRAMA, COMIENZO_FUNCION,
						FIN_FUNCION, IMPRIMIR, SALTAR_NO_CERO, SALTAR_SI_CERO,
						ETIQUETA, ASIGNACION, IO_FUNCION,FUNCION};

#endif /* PARSER_H_ */
