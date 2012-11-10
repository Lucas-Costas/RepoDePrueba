/*
 * NIPC.h
 *
 *  Created on: 02/11/2012
 *      Author: Que esta vez si me va a volar la cabeza
 */

#ifndef Estructuras_H_
#define Estructuras_H_

#include <collections/list.h>
#include <collections/node.h>
#include <collections/queue.h>

typedef struct
{
	 int32_t PID;
     int32_t ProgramCounter;
}PCB_t;

typedef struct
{
	char nombre;
	int32_t valor;
}variable_t;

typedef struct
{
	int32_t numeroDeLinea;
	char* llamada;
}nodoStack_t;

typedef struct
{

    PCB_t PCB_proceso;
    t_list* segmentoDeDatos;
    char* segmentoDeCodigo;
    t_queue* segmentoDeStack;
}imagen_proceso_t;

#endif /* Estructuras_H_ */
