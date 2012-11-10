/*
 * ProcesoInterprete.c
 *
 *  Created on: 02/11/2012
 *      Author: Que esta vez si me va a volar la cabeza
 */

#include "ProcesoInterprete.h"
#include "headers/ManejoDeSockets.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int Stoi (char * string, char * formato);

int main (int argc,char** argv)
{
	 //Abrir el script que voy a interpretar

	 FILE* script = fopen( argv[1], "r");

	 if ( script == NULL )
	 {
	 	printf("No se encontro el archivo \n");
	 	return -1;
	 }

	 else
	 {
		 if(feof (script) == 0)
		 {
			 int32_t tamanioDePath = strlen(argv[0]) + (sizeof(char)*3);
			 char linea[tamanioDePath];
			 fgets(linea,tamanioDePath,script);
		 }
		 else
		 {
			 puts("Script vacio");
			 return -1;
		 }

		 char* stream;
		 size_t tamanio= 0;
		 size_t offset = 0;
		 stream = malloc(0);

		 while( feof (script) == 0 )
		 {
		 	char linea[50]="";
		 	fgets(linea,50,script);
		 	tamanio = strlen(linea);
		 	stream = realloc(stream,tamanio+offset);
		 	memcpy(stream+offset,linea,tamanio);
		 	offset += tamanio;
		 }

		 stream = realloc(stream,tamanio+offset+1);
		 memcpy(stream+offset,"\0",1);

		 fclose(script);

		 char* ip = getenv("PP_IP");
		 char* port = getenv("PP_Puerto");

		 if( (ip == NULL) || (port == NULL) )
		 {
			 puts("Variables PP_IP o PP_Puerto no especificadas");
			 return -1;
		 }

		 uint16_t puerto = (uint16_t) Stoi(port,"%u");

		 t_socket* socketCliente = crearSocket("127.0.0.1",3001);

		 puts("Conectando con servidor...");
		 printf("IP: %s\nPUERTO:%u\n",ip,puerto);

		 if( conectarSocket(socketCliente,ip,puerto) == -1)
		 {
		 	puts("Error al conectar con servidor");
		 	return -1;
		 }

		 if( enviarSocket(socketCliente,stream,strlen(stream)) == -1 )
		 {
		 	puts("Error al enviar mensaje");
		 	return -1;
		 }

		 free(stream);

		 destruirSocket(socketCliente);
	 }

	 return 0;
}

int Stoi (char* string, char* formato)
{
	int i;

	sscanf (string, formato, &i);

	return i;
}
