/*
 * PROCER.c
 *
 *  Created on: 09/11/2012
 *      Author: Que esta vez si me va a volar la cabeza
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <collections/list.h>
#include <collections/queue.h>
#include <collections/node.h>

#include "headers/ManejoDeProcesos.h"
#include "parser.h"
#include "PROCER.h"

int main()
{
	// Recibir un proceso del STS*/
	/*
	 * TODO
	 * Por ahora esto va a ser representado por un proceso creado de la nada
	 */
	FILE* arch = fopen( "Prueba" , "r" );
	if ( arch == NULL )
	{
		printf("no se encontro el archivo \n");
		return -1;
	}

	char* stream;
	size_t tamanio= 0;
	size_t offset = 0;
	stream = malloc(0);

	while( feof (arch) == 0 )
	{
		char linea[50]="";
	 	fgets(linea,50,arch);
	 	tamanio = strlen(linea);
	 	stream = realloc(stream,tamanio+offset);
	 	memcpy( stream + offset , linea , tamanio );
	 	offset += tamanio;
	}

	stream = realloc( stream , tamanio + offset + 1 );
	memcpy( stream + offset , "\0" , 1 );

	fclose(arch);

	imagen_proceso_t procesoNuevo = crearProceso(0,stream);
	agregarVariable(&procesoNuevo,'a',0);
	agregarVariable(&procesoNuevo,'b',0);
	agregarVariable(&procesoNuevo,'c',0);

	// Inicializar los parametros de planificacion necesarios TODO

	// Buscar la ultima linea ejecutada
	//char proximaLinea[200] = irALinea(codigoAEjecutar,proceso->PCB_proceso->ProgramCounter);

	// Ejecutar programa

	int32_t resultadoParseo = NOSALTO; //TODO
	size_t posicion = 0;
	size_t tamanioProximaLinea = strcspn(procesoNuevo.segmentoDeCodigo , "\n" );
	char* proximaLinea = "";

	//while(proceso.PCB_proceso.ProgramCounter != FIN /*|| el STS no me saque TODO*/)
	while(strcmp(proximaLinea,"fin_funcion") != 0)
	{
		if(resultadoParseo == SALTO)
		{
			int32_t numeroDeLinea = 0;
			size_t posicion = 0;
			size_t tamanioProximaLinea = strcspn(procesoNuevo.segmentoDeCodigo , "\n" );

			while(numeroDeLinea != procesoNuevo.PCB_proceso.ProgramCounter)
			{
				posicion += tamanioProximaLinea + 1;
				tamanioProximaLinea = strcspn(procesoNuevo.segmentoDeCodigo + posicion,"\n");
				numeroDeLinea++;
			}

			proximaLinea = malloc(tamanioProximaLinea);
			strncpy(proximaLinea,stream+posicion,tamanioProximaLinea);
			//resultadoParseo = parsear( proximaLinea , &proceso );
			printf("Ejecutar: \'%s\'\n",proximaLinea);
		}
		if(resultadoParseo == NOSALTO)
		{
			proximaLinea = malloc(tamanioProximaLinea + 1);
			strncpy(proximaLinea , procesoNuevo.segmentoDeCodigo + posicion , tamanioProximaLinea);
			printf("Ejecutar: \'%s\'\n",proximaLinea);
			//resultadoParseo = parsear( proximaLinea , &proceso );
			posicion += tamanioProximaLinea + 1;
			tamanioProximaLinea = strcspn(procesoNuevo.segmentoDeCodigo + posicion,"\n");
		}
	}

	free(proximaLinea);
	free(stream);

	puts("Termine");

	return 0;
}
