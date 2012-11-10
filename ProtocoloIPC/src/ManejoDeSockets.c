/*
 * ManejoDeSockets.c
 *
 *  Created on: 02/11/2012
 *      Author: Que esta vez si me va a volar la cabeza
 */

#include "ManejoDeSockets.h"

t_socket* crearSocket(char* ip, uint16_t puerto)
{
	t_socket* socketCreado;
	socketCreado = malloc(sizeof(t_socket));
	int32_t descriptor = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in direccion;
	direccion.sin_family = AF_INET;
	direccion.sin_addr.s_addr = inet_addr(ip);
	direccion.sin_port = htons(puerto);

	socketCreado->descriptor = descriptor;
	socketCreado->direccion = direccion;

	return socketCreado;
}

int32_t conectarSocket(t_socket* socketCliente, char* ipServidor , uint16_t puerto)
{
	struct sockaddr_in* direccionServidor;
	direccionServidor = malloc(sizeof(struct sockaddr_in));
	direccionServidor->sin_family = AF_INET;
	direccionServidor->sin_addr.s_addr = inet_addr(ipServidor);
	direccionServidor->sin_port = htons(puerto);

	return connect(socketCliente->descriptor,(struct sockaddr*) direccionServidor, sizeof(struct sockaddr));
}

int32_t bindearSocket(t_socket* socket)
{
	return bind(socket->descriptor, (struct sockaddr*) &socket->direccion, sizeof(struct sockaddr));
}

int32_t escucharSocket(t_socket* socket)
{
	return listen(socket->descriptor, 10);
}

t_socket* aceptarSocket(t_socket* socket)
{
	int32_t descriptor = accept(socket->descriptor,NULL, 0);

	t_socket* socketManejador;
	socketManejador = malloc(sizeof(t_socket));
	socketManejador->descriptor = descriptor;

	return socketManejador;
}

int32_t enviarSocket(t_socket* socket, void* paquete, size_t tamanioPaquete)
{
	return send(socket->descriptor, paquete, tamanioPaquete, 0);
}

//Se le debe pasar la dirección de un buffer para que lo modifique.
int32_t recibirSocket(t_socket* socket, void* paqueteRecibido)
{
	return recv(socket->descriptor, paqueteRecibido, MAX_BUFFER_TAMANIO, 0);
}

char* recibirSocketVariable(t_socket* socket)
{
	char* paqueteRecibido = NULL;
	int32_t bytesRecibidos = 0;
	int32_t tamanioPaquete = 0;
	do
	{
		tamanioPaquete += 20;
		if( paqueteRecibido == NULL )
			paqueteRecibido = malloc( tamanioPaquete );
		else
			paqueteRecibido = realloc (paqueteRecibido, tamanioPaquete);
		bytesRecibidos = recv(socket->descriptor,paqueteRecibido,tamanioPaquete,MSG_PEEK );

	}while( bytesRecibidos == tamanioPaquete ) ;
	recv(socket->descriptor,paqueteRecibido,tamanioPaquete+bytesRecibidos, 0);

	return paqueteRecibido;
}

void destruirSocket(t_socket* socket)
{
	close(socket->descriptor);
	free(socket);
}
