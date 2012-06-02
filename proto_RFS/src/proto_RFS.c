/*
 * proto_fuse.c
 *
 *  Created on: 01/06/2012
 *      Author: utnso
 */

#include <stddef.h>
#include <stdlib.h>
//#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <headers/TAD_sockets.h>

struct NIPC
{
	char type;
	int payloadLength;
	char* payload;
};

struct NIPC* deserializar(char* paqueteSerializado)
{
	struct NIPC *paquete = malloc(sizeof(struct NIPC));
	int offset = 0;
	int tamanio_temp = sizeof(char);

	memcpy(&paquete->type, paqueteSerializado, tamanio_temp);
	offset = tamanio_temp;
	tamanio_temp = sizeof(int);
	memcpy(&paquete->payloadLength, paqueteSerializado + offset, tamanio_temp);
	offset += tamanio_temp;
	for(tamanio_temp = 0; (paqueteSerializado + offset)[tamanio_temp] != '\0'; tamanio_temp++);
	paquete->payload = malloc(tamanio_temp);
	memcpy(paquete->payload, paqueteSerializado + offset, tamanio_temp);

	return paquete;
}

char* serializar(struct NIPC *paqueteNIPC)
{
	char* serializado;
	serializado = malloc(sizeof(char) + sizeof(int) + paqueteNIPC->payloadLength + 1);
	int offset = 0;
	int tamanio_temp = sizeof(char);

	memcpy(serializado, &paqueteNIPC->type, tamanio_temp);
	offset = tamanio_temp;
	tamanio_temp = sizeof(int);
	memcpy(serializado + offset, &paqueteNIPC->payloadLength, tamanio_temp);
	offset += tamanio_temp;
	tamanio_temp = paqueteNIPC->payloadLength + 1;
	memcpy(serializado + offset, paqueteNIPC->payload, tamanio_temp);

	return serializado;
}



static int hello_getattr()
{
	int resultado = 0;

	t_socket_servidor* servidor = socket_crearServidor("127.0.0.1",5301);
	t_socket_cliente *cliente;

	socket_escuchar(servidor);
	cliente = socket_aceptar(servidor);

	t_buffer* buffer;
	buffer = malloc(sizeof(t_buffer));
	buffer = socket_Recibir(cliente->servidor);

	struct NIPC *deserializado = deserializar(buffer->data);
	printf("Llego el paquete que contiene: \n Typo: %c \n Largo del payload: %d \n Payload: %s \n", deserializado->type
																								  , deserializado->payloadLength
																							      , deserializado->payload);

	struct stat estado;
	stat(deserializado->payload, &estado);
	printf("Tamaño de archivo: %ld bytes\n",estado.st_size);

	socket_destruirCliente(cliente);
	socket_destruirServidor(servidor);
	socket_destruirBuffer(buffer);

	return resultado;
}

/*static struct fuse_operations proto_oper =
{
		.getattr = hello_getattr,
};*/

int main(int argc, char *argv[])
{
	/*struct stat *estado;
	estado = malloc(sizeof(struct stat));*/
	hello_getattr();
	//free(estado);
	return 0;
	//return fuse_main(argc, argv, &proto_oper,NULL);
}
