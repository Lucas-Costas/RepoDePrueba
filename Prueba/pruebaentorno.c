/*
 * pruebaentorno.c
 *
 *  Created on: 05/11/2012
 *      Author: Garou
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

	size_t posicion = 0;
	size_t tamanioProximaLinea = strcspn(stream , "\n" );
	char* proximaLinea = "";
	int32_t numeroDeLinea = 1;

			while(numeroDeLinea != 2)
			{
				posicion += tamanioProximaLinea + 1;
				tamanioProximaLinea = strcspn(stream + posicion,"\n");
				numeroDeLinea++;
			}

	char* linea = "";
	linea = malloc(tamanioProximaLinea);
	strncpy(linea,stream+posicion,tamanioProximaLinea);
	printf("N-Linea:%d\nLinea: \'%s\'\n",numeroDeLinea,linea);

	free(proximaLinea);
	free(stream);

	puts("Termine");

	return 0;
}
