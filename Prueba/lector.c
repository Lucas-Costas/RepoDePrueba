/*
 * parser.c
 *
 *  Created on: 26/10/2012
 *      Author: Que esta vez si me va a volar la cabeza
 */

/*
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "headers/ManejoDeProcesos.h"*/
/*
int main()
{
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

	//Crear proceso de prueba
	imagen_proceso_t proceso = crearProceso(0,stream);
	agregarVariable(&proceso,'a',0);
	agregarVariable(&proceso,'b',0);
	agregarVariable(&proceso,'c',0);


	printf( "El contenido del archivo de prueba es: \n" );

	rewind(arch);
	while( feof (arch) == 0 )
	{
		char linea[100]="";
		fgets(linea,100,arch);
		parsear(linea,&proceso);
	}

	estadoDeProceso(proceso);
	puts("----------------------------------");

	fclose(arch);

	return 0;
}*/
