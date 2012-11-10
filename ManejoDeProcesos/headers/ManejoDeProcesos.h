/*
 * ManejoDeProcesos.h
 *
 *  Created on: 06/11/2012
 *      Author: utnso
 */

#ifndef MANEJODEPROCESOS_H_
#define MANEJODEPROCESOS_H_

#include "Estructuras.h"

void estadoDeProceso(imagen_proceso_t proceso);
imagen_proceso_t crearProceso(int32_t PID, char* script);

//VARIABLES
void agregarVariable(imagen_proceso_t* proceso,char nombreVariable,int32_t valorVariable);
int32_t getValorVariable(imagen_proceso_t proceso, char nombreVariable);
int32_t esLaVariableQueBusco(void* punteroAVariable,char nombreVariable);
int32_t getValor(void* punteroAVariable);
void setValorVariable(imagen_proceso_t proceso, char nombreVariable, int32_t valorVariable);
void setValor(void* punteroAVariable, int32_t valor);
void borrarVariable(imagen_proceso_t proceso,char nombreVariable);
void estadoVariable(void* punteroAVariable);

// STACK
void agregarLlamada(imagen_proceso_t proceso, int32_t numeroDeLinea, char* llamada);
nodoStack_t* sacarLlamada(imagen_proceso_t proceso);
void estadoLlamada(void* punteroALlamada);

#endif /* MANEJODEPROCESOS_H_ */
