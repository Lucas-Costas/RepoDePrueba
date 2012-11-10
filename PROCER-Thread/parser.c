/*
 * parser.c
 *
 *  Created on: 26/10/2012
 *      Author: Que esta vez si me va a volar la cabeza
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "parser.h"
#include "Estructuras.h"
#include <string.h>

int parsear(char* linea, imagen_proceso_t* proceso)
{
	if(especificaTiempo(linea))
		printf("Especifica tiempo;");
		//sleep(tiempo);
	int tipoDeLinea = determinarTipoDeLinea(linea);
	switch (tipoDeLinea)
	{
		case LINEA_VACIA:
			return NOSALTO;
			break;
		case INTERPRETE:
			return NOSALTO;
			break;
		case COMENTARIO:
			return NOSALTO;
			break;
		case DECLARACION_DE_VARIABLES:
			return NOSALTO;
			break;
		case COMIENZO_PROGRAMA:
			return NOSALTO;
			break;
		case FIN_PROGRAMA:
			proceso->PCB_proceso.ProgramCounter = FIN;
			return FIN;
			break;
		case COMIENZO_FUNCION:
			puts("Una funcion empieza");
			break;
		case FIN_FUNCION:
			//nodoStack_t* retorno = sacarLlamada(proceso);
			//proceso->PCB_proceso->ProgramCounter = retorno->numeroDeLinea;
			puts("Una funcion finaliza");
			return SALTO;
			break;
		case IMPRIMIR:
			imprimir(linea,*proceso);
			return NOSALTO;
			break;
		case SALTAR_NO_CERO:
			return saltar(linea,proceso,DISTINTO);
			break;
		case SALTAR_SI_CERO:
			return saltar(linea,proceso,IGUAL);
			break;
		case ETIQUETA:
			return NOSALTO;
			break;
		case ASIGNACION:
			puts("Asignacion");
			asignarVariable(linea,*proceso);
			return NOSALTO;
			break;
		case IO_FUNCION:
			puts("I/O");
			ejecutarIO(linea);
			return NOSALTO;//TODO por ahora despues vemos
			break;
		case FUNCION:
			irAFuncion(linea,proceso);
			return SALTO;
		case OTRO:
			puts("Error");
			return ERROR;
			break;
	}
	return 0;
}

int determinarTipoDeLinea(char* linea)
{
	if(esUnaLineaVacia(linea))
		return LINEA_VACIA;
	if(esUnInterprete(linea))
		return INTERPRETE;
	if(esUnComentario(linea))
		return COMENTARIO;
	char* primera = primerPalabra(linea);
	if(strcmp(primera,"variables") == 0)
		return DECLARACION_DE_VARIABLES;
	if(strcmp(primera,"comienzo_programa") == 0)
		return COMIENZO_PROGRAMA;
	if(strcmp(primera,"fin_programa") == 0)
		return FIN_PROGRAMA;
	if(strcmp(primera,"comienzo_funcion") == 0)
		return COMIENZO_FUNCION;
	if(strcmp(primera,"fin_funcion") == 0)
		return FIN_FUNCION;
	if(strcmp(primera,"imprimir") == 0)
		return IMPRIMIR;
	if(strcmp(primera,"snc") == 0)
		return SALTAR_NO_CERO;
	if(strcmp(primera,"ssc") == 0)
		return SALTAR_SI_CERO;
	if(esUnaEtiqueta(linea))
		return ETIQUETA;
	if(esUnaAsignacion(linea))
		return ASIGNACION;
	if(esUnaEntradaSalida(linea))
		return IO_FUNCION;
	if(esUnaFuncion(linea))
		return FUNCION;
	return OTRO;
}

char* primerPalabra(char* linea)
{
	int i = 0;
	while(linea[i] != ' ' && linea[i] != '\n')
		i++;
	char* primerPalabra;
	primerPalabra = malloc(sizeof(char)*i);
	memcpy(primerPalabra,linea,sizeof(char)*i);
	primerPalabra = realloc(primerPalabra,sizeof(char)*(i+1));
	memcpy(primerPalabra + (sizeof(char) * i) , "\0" , 1);
	return primerPalabra;
}

int esUnaEntradaSalida(char* linea)
{
	if(linea[0] == 'i' && linea[1] == 'o' && linea[2] == '(' && linea[4] == ',' && linea[6] == ')')
		return 1;
	return 0;
}

int esUnaAsignacion(char* linea)
{
	return linea[1] == '=';
}

int especificaTiempo(char* linea)
{
	int i = 0;
	while(linea[i] != ';' && linea[i] != '\n')
		i++;
	if(linea[i] == ';')
		return 1;
	return 0;
}

int esUnaEtiqueta(char* linea)
{
	int i = 0;
	while(linea[i] != ':' && linea[i] != ' ' && linea[i] != '\n')
		i++;
	if(linea[i] == ':')
		return 1;
	return 0;
}

int esUnaLineaVacia(char* linea)
{
	int i = 0;
	while(linea[i] == ' ' || linea[i] == '\t')
		i++;
	if(linea[i] == '\n')
		return 1;
	return 0;
}

int esUnInterprete(char* linea)
{
	int esUnInterprete = 0;
	if(linea [0] == '#' && linea[1] == '!')
		esUnInterprete = 1;
	return esUnInterprete;
}

int esUnComentario(char* linea)
{
	int esUnComentario = 0;
	if(linea [0] == '#' && linea[1] != '!')
		esUnComentario = 1;
	return esUnComentario;
}

int imprimir(char* linea, imagen_proceso_t proceso)
{
	printf( "%c -> %d\n" , linea[9], getValorVariable(proceso,linea[9]) );

	return 0;
}

int32_t esUnaFuncion(char* linea)
{
	int32_t i=0;
	while(linea[i] != '#' && linea[i] != '(')
		i++;
	if(linea[i+1] == ')')
		return 1;
	return 0;
}

int saltar(char* linea , imagen_proceso_t* proceso,int comparador)
{
	switch (comparador)
	{
		case IGUAL:
			if( getValorVariable(*proceso,linea[4]) != 0)
			{
				puts("No salta");// TODO
				return NOSALTO;
			}
			break;
		case DISTINTO:
			if( getValorVariable(*proceso,linea[4]) == 0)
			{
				puts("No salta"); // TODO
				return NOSALTO;
			}
			break;
	}

	int i=6; //Inicio de la etiqueta
	while(linea[i] != '\n' && linea[i] != '#')
		i++;

	char* etiqueta;
	etiqueta = malloc(sizeof(char)*(i-6));
	memcpy(etiqueta,linea + 6, sizeof(char)*(i-6));
	etiqueta = realloc(etiqueta,sizeof(char)*(i-6+2));
	memcpy(etiqueta + (sizeof(char) * (i-6)) , ":\0" , 2);

	printf("Saltar a: \'%s\'\n",etiqueta);

	if(buscarStringEIr(etiqueta,proceso) == -1)
	{
		printf("No existe la etiqueta %s\n",etiqueta);
		return NOSALTO;
	}

	return SALTO;
}

int asignarVariable(char* linea,imagen_proceso_t proceso)
{
	setValorVariable(proceso,linea[0],resultadoExpresion(linea+2,proceso));

	return 0;
}

int resultadoExpresion(char* expresion,imagen_proceso_t proceso)
{
	if(esUnaEntradaSalida(expresion))
		return ejecutarIO(expresion);
	int i = 0;
	while(expresion[i] != '#' && expresion[i] != '\n' && expresion[i] != ';' && expresion[i] != '+' && expresion[i] != '-')
		i++;
	if(expresion[i] == '+' || expresion[i] == '-')
	{
		int j=i;
		while(expresion[j] != '#' && expresion[j] != '\n' && expresion[j] != ';')
			j++;
		return obtenerResultado(expresion,i,j+1,proceso);
	}
	return obtenerOperando(expresion,0,i,proceso);
}

int ejecutarIO(char* expr)
{
	return 0;
}

int obtenerResultado(char* expresion,int posicionOperador,int finCadena,imagen_proceso_t proceso)
{
	int operando1,operando2;
	operando1 = obtenerOperando(expresion,0,posicionOperador,proceso);
	operando2 = obtenerOperando(expresion,posicionOperador+1,finCadena,proceso);
	if(expresion[posicionOperador] == '+')
		return operando1 + operando2;
	if(expresion[posicionOperador] == '-')
		return operando1 - operando2;
	return -1;
}

int obtenerOperando(char* expresion,int inicioOperando, int finOperando,imagen_proceso_t proceso)
{
	char* operando;
	int operandoInt;
	int longitudOperando = finOperando - inicioOperando;

	operando = malloc(sizeof(char)*longitudOperando);
	memcpy(operando,expresion + (inicioOperando * (sizeof(char) ) ),longitudOperando);
	operando = realloc(operando,longitudOperando + 1);
	memcpy(operando + (sizeof(char) * longitudOperando), "\0", 1);

	if(longitudOperando == 1 && isalpha(expresion[inicioOperando]))
	{
		return getValorVariable(proceso,expresion[inicioOperando]);
	}
	else
		sscanf(operando, "%d", &operandoInt);

	return operandoInt;
}

void irAFuncion(char* linea,imagen_proceso_t* proceso)
{
	int32_t i = 0;
	while(linea[i] != '(')
		i++;
	char* nombreDeFuncion;
	nombreDeFuncion = malloc( i * sizeof(char) );
	strncpy(nombreDeFuncion,linea,i);

	char inicioFuncion[18 + i];
	strcpy(inicioFuncion,"comienzo_funcion ");
	strcat(inicioFuncion,nombreDeFuncion);
	printf("Ir a : %s\n",inicioFuncion);

	int32_t PCAnterior = proceso->PCB_proceso.ProgramCounter;

	if(buscarStringEIr(inicioFuncion,proceso) == -1)
	{
		printf("No esta definida la funcion %s\n",nombreDeFuncion);
		return;
	}

	printf("%s\n",nombreDeFuncion);
	agregarLlamada(*proceso,PCAnterior,nombreDeFuncion);
	puts("DentroDelPARCER");

}

int32_t buscarStringEIr(char* stringBuscado,imagen_proceso_t* proceso)
{
	char* codigoCopy;
	codigoCopy = malloc(strlen(proceso->segmentoDeCodigo));
	strcpy(codigoCopy,proceso->segmentoDeCodigo);

	printf("CODE:\n\'%s\'",codigoCopy);

	char* proximaLinea = strtok( codigoCopy, "\n" );
	printf("\'%s\'\n",proximaLinea);
	int32_t numeroDeLinea = 1;

	while( (proximaLinea != NULL) && !strstr( proximaLinea , stringBuscado ) )
	{
		proximaLinea = strtok( NULL, "\n" );
		printf("\'%d\'\'%s\'\n",numeroDeLinea,proximaLinea);
		numeroDeLinea++;
	}
	printf("CODE:\n\'%s\'",codigoCopy);

	if(proximaLinea == NULL)
		return -1;

	proceso->PCB_proceso.ProgramCounter = numeroDeLinea;
	printf("Ir a numero de linea : %d\n",numeroDeLinea);
	return 0;
}
