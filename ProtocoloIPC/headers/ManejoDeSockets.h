/*
 * ManejoDeSockets.h
 *
 *  Created on: 02/11/2012
 *      Author: Que esta vez si me va a volar la cabeza
 */

#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#ifndef MANEJODESOCKETS_H_
#define MANEJODESOCKETS_H_

#define MAX_BUFFER_TAMANIO 1000

typedef struct socket_t
{
	int32_t descriptor;
	struct sockaddr_in direccion;
} t_socket;

t_socket* crearSocket(char* ip, uint16_t puerto);
int32_t conectarSocket(t_socket* socketCliente, char* ipServidor , uint16_t puerto);
int32_t bindearSocket(t_socket* socket);
int32_t escucharSocket(t_socket* socket);
t_socket* aceptarSocket(t_socket* socket);
int32_t enviarSocket(t_socket* socket, void* paquete, size_t tamanioPaquete);
int32_t recibirSocket(t_socket* socket, void* paqueteRecibido);
void destruirSocket(t_socket* socket);
char* recibirSocketVariable(t_socket* socket);

#endif /* MANEJODESOCKETS_H_ */
