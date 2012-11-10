/*
 * NIPC.h
 *
 *  Created on: 02/11/2012
 *      Author: Que esta vez si me va a volar la cabeza
 */

#ifndef Estructuras_H_
#define Estructuras_H_

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
	void* llamada;
}nodoStack_t;

typedef struct
{

    PCB_t PCB_proceso;
    variable_t segmentoDeDatos[10];
    char* segmentoDeCodigo;
    nodoStack_t segmentoDeStack[10];
}imagen_proceso_t;

#endif /* Estructuras_H_ */
