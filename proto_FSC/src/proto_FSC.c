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

static int hello_getattr(const char *path, struct stat *stbuf)
{
	struct NIPC *paqueteNIPC;
	int resultado = 0;

	paqueteNIPC = malloc(sizeof(struct NIPC));
	paqueteNIPC->payloadLength = strlen(path);
	paqueteNIPC->type = '1'; //Despues cuando definamos bien el protocolo vemos que le ponemos por ahora le pongo 1
	paqueteNIPC->payload = (char*) path;

	char* serializado = serializar(paqueteNIPC);

	t_socket_cliente* cliente = socket_crearCliente("127.0.0.1",5300);
	socket_conectar(cliente, "127.0.0.1", 5301);

	int tamanio = sizeof(char) + sizeof(int) + strlen(path) + 1;
	socket_Enviar(cliente->cliente,serializado,tamanio);

	/*t_buffer* buff;
	buff = malloc(sizeof(t_buffer));
	buff = socket_Recibir(cliente->cliente);*/

	socket_destruirCliente(cliente);

	return resultado;
}

/*static struct fuse_operations proto_oper =
{
		.getattr = hello_getattr,
};*/

int main(int argc, char *argv[])
{
	struct stat *estado;
	estado = malloc(sizeof(struct stat));
	hello_getattr("/home/utnso/Escritorio/FUSE_a_implementar",estado);
	free(estado);
	return 0;
	//return fuse_main(argc, argv, &proto_oper,NULL);
}
