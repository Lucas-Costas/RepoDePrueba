/*
 * Server.c
 *
 *  Created on: 02/11/2012
 *      Author: utnso
 */

#include "headers/ManejoDeSockets.h"
#include <stdlib.h>
#include <stdio.h>

int main()
{
	printf("Este es el servidor... \n");
	t_socket* socketServidor = crearSocket("127.0.0.1",3000);
	if(bindearSocket(socketServidor) == -1 )
	{
		puts("Error al bindear");
		return -1;
	}
	if(escucharSocket(socketServidor) == -1)
	{
		puts("Error al escuchar");
		return -1;
	}
	t_socket* tratador = aceptarSocket(socketServidor);
	if(tratador->descriptor == -1)
	{
		puts("Error al aceptar");
		return -1;
	}

	char* recibido = recibirSocketVariable(tratador);
	printf("Llego el mensaje: %s \n",recibido);

	destruirSocket(socketServidor);
	destruirSocket(tratador);
	return 0;
}
