/*
 * Client.c
 *
 *  Created on: 02/11/2012
 *      Author: utnso
 */

#include "headers/ManejoDeSockets.h"
#include <stdlib.h>
#include <stdio.h>

int main()
{
	printf("Este es el cliente... \n");
	t_socket* socketCliente = crearSocket("127.0.0.1",3001);

	if( conectarSocket(socketCliente,"127.0.0.1",3000) == -1)
	{
		puts("Error al conectar con servidor");
		return -1;
	}

	char* mensaje2 = "Soy cliente y me quiero pasar del tamanio porque soy re pelotudo y tengo ganas de joder al programador";
	if( enviarSocket(socketCliente,mensaje2,sizeof("Soy cliente y me quiero pasar del tamanio porque soy re pelotudo y tengo ganas de joder al programador")) == -1 )
	{
		puts("Error al enviar mensaje 2");
		return -1;
	}

	destruirSocket(socketCliente);
	return 0;
}
