/*
 * ManejoDeProcesos.c
 *
 *  Created on: 06/11/2012
 *      Author: Que esta vez si me va a volar la cabeza
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <collections/list.h>
#include <collections/node.h>
#include <collections/queue.h>
#include "ManejoDeProcesos.h"
#include "Estructuras.h"

//PROCESOS

void (*estadoVar)(void* punteroAVariable);
void (*estadoCall)(void* punteroALlamada);

void estadoDeProceso(imagen_proceso_t proceso)
{
	puts("---------------------------------------------------");
	printf("ID = %d\n",proceso.PCB_proceso.PID);
	printf("PC = %d\n",proceso.PCB_proceso.ProgramCounter);
	puts("---------------Estructura de código----------------");
	estadoVar = &estadoVariable;
	list_iterate(proceso.segmentoDeDatos,estadoVar);
	puts("---------------Estructura del stack----------------");
	estadoCall = &estadoLlamada;
	list_iterate(proceso.segmentoDeStack->elements,estadoCall);
	puts("---------------------------------------------------");
}

imagen_proceso_t crearProceso(int32_t PID, char* script)
{
	imagen_proceso_t procesoNuevo;
	procesoNuevo.PCB_proceso.PID = PID;
	procesoNuevo.PCB_proceso.ProgramCounter = 0;
	procesoNuevo.segmentoDeCodigo = malloc( strlen(script) );
	strcpy(procesoNuevo.segmentoDeCodigo,script);
	procesoNuevo.segmentoDeDatos = list_create();
	procesoNuevo.segmentoDeStack = queue_create();

	return procesoNuevo;
}

//VARIABLES
void agregarVariable(imagen_proceso_t* proceso,char nombreVariable,int32_t valorVariable)
{
	variable_t* variable;
	variable = malloc(sizeof(variable_t));
	variable->nombre = nombreVariable;
	variable->valor = valorVariable;
	list_add(proceso->segmentoDeDatos,variable);
}

int32_t getValorVariable(imagen_proceso_t proceso, char nombreVariable)
{
	t_link_element* unaVariable = proceso.segmentoDeDatos->head;

	while(unaVariable != NULL && !esLaVariableQueBusco(unaVariable->data,nombreVariable))
		unaVariable = unaVariable->next;

	if(unaVariable == NULL)
		return -1;

	return getValor(unaVariable->data);
}

int32_t esLaVariableQueBusco(void* punteroAVariable,char nombreVariable)
{
	variable_t* variable;
	variable = malloc(sizeof(variable_t));
	variable = (variable_t*) punteroAVariable;
	return variable->nombre == nombreVariable;
}

int32_t getValor(void* punteroAVariable)
{
	variable_t* variable;
	variable = malloc(sizeof(variable_t));
	variable = (variable_t*) punteroAVariable;
	return variable->valor;
}

void setValorVariable(imagen_proceso_t proceso, char nombreVariable, int32_t valorVariable)
{
	t_link_element* unaVariable = proceso.segmentoDeDatos->head;

	while(unaVariable != NULL && !esLaVariableQueBusco(unaVariable->data,nombreVariable))
		unaVariable = unaVariable->next;

	if(unaVariable == NULL)
		return;

	setValor(unaVariable->data,valorVariable);
}

void setValor(void* punteroAVariable, int32_t valor)
{
	variable_t* variable;
	variable = malloc(sizeof(variable_t));
	variable = (variable_t*) punteroAVariable;
	variable->valor = valor;
}

void borrarVariable(imagen_proceso_t proceso,char nombreVariable)
{
	t_link_element* unaVariable = proceso.segmentoDeDatos->head;
	int32_t posicion = 0;

	while(unaVariable != NULL && !esLaVariableQueBusco(unaVariable->data,nombreVariable))
	{
		unaVariable = unaVariable->next;
		posicion++;
	}

	if(unaVariable == NULL)
		return;

	list_remove(proceso.segmentoDeDatos,posicion);
}

void estadoVariable (void* punteroAVariable)
{
	variable_t* variable;
	variable = malloc(sizeof(variable_t));
	variable = (variable_t*) punteroAVariable;
	printf("%c = %d\n",variable->nombre,variable->valor);
}


// STACK
void agregarLlamada(imagen_proceso_t proceso, int32_t numeroDeLinea, char* llamada)
{
	nodoStack_t* unaLlamada;
	unaLlamada = malloc(sizeof(nodoStack_t));
	unaLlamada->numeroDeLinea = numeroDeLinea;
	unaLlamada->llamada = malloc( strlen(llamada) );
	strcpy(unaLlamada->llamada,llamada);
	queue_push(proceso.segmentoDeStack,unaLlamada);
}

nodoStack_t* sacarLlamada(imagen_proceso_t proceso)
{
	void* punteroALlamada = queue_pop(proceso.segmentoDeStack);
	nodoStack_t* unaLlamada;
	unaLlamada = malloc(sizeof(nodoStack_t));
	unaLlamada = (nodoStack_t*) punteroALlamada;
	return unaLlamada;
}

void estadoLlamada (void* punteroALlamada)
{
	nodoStack_t* llamada;
	llamada = malloc(sizeof(nodoStack_t));
	llamada = (nodoStack_t*) punteroALlamada;
	printf("%d,%s\n",llamada->numeroDeLinea,llamada->llamada);
}
