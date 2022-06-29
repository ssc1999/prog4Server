#include "comprador.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../Logger/log.h"
#include "../../BD/BD.h"
#include "../../BD/sqlite3.h"
//#include "../../Log/logger.h"

void imprimirComprador(Comprador comprador)
{
	printf("Nombre: %s\n", comprador.nombre);
	printf("Dni: %s\n", comprador.dni);
	printf("Email: %s\n", comprador.email);
	printf("Cuenta bancaria: %s\n", comprador.cuentaBancaria);
}

int comprarCoche(sqlite3 *db, Ticket* ticket){
	log_trace("Comprar coche inicializado");
	insertTicket(db, ticket);
	updateVendedor(db, ticket->precio, ticket->nomUsuario);
	updateCoche(db, ticket->matricula, ticket->nomUsuario);
	log_trace("Comprar coche finalizado");
	return 0;
}

Comprador* getComprador(sqlite3 *db, char usuario[20]){
	log_trace("Consultando comprador a la BD");
	Comprador* comprador = (Comprador*) malloc(sizeof(Comprador));
	comprador = getCompradorBD(db, usuario);
	log_trace("Mandando comprador al server");
	return comprador;
}

char *getNombreComprador(sqlite3 *db, char usuario[20]){
	char *nombreComprador = malloc(sizeof(char) * 20);
	Comprador *comprador = (Comprador*) malloc(sizeof(Comprador));
	comprador = getCompradorBD(db, usuario);
	strcpy(nombreComprador, comprador->nombre);
	return nombreComprador;
}