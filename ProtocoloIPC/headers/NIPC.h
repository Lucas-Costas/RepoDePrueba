/*
 * NIPC.h
 *
 *  Created on: 02/11/2012
 *      Author: Que esta vez si me va a volar la cabeza
 */

#ifndef NIPC_H_
#define NIPC_H_

typedef struct
{
	int8_t tipo;
	int16_t tamañoDelCuerpo;
}cabecera_NIPC_t;

typedef struct
{
	cabecera_NIPC_t cabecera;
	char* cuerpo;
}paquete_NIPC_t;

#endif /* NIPC_H_ */
