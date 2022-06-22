#include "comprador.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int comprarCoche(sqlite3 *db, Ticket *ticket)
{
	updateCocheBD(db, ticket->nomUsuario, ticket->matricula);
	insertTicket(db, ticket);
	// metodo BD de cambiar atributo en coche
	// metodo de crear ticket
}

Comprador getComprador(sqlite3 *db, char usuario[20]){

}

char *getNombreComprador(sqlite3 *db, char usuario[20]){
	char *nombreComprador = malloc(sizeof(char) * 20);
	strcpy(nombreComprador, getComprador(db, usuario).nombre);
	return nombreComprador;
}