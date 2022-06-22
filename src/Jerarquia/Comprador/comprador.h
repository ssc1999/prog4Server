#include "../../BD/sqlite3.h"
#include "../Ticket/ticket.h"

#ifndef COMPRADOR_H_
#define COMPRADOR_H_

typedef struct
{
	char usuario[20];
	char contrasenya[20];
	char nombre[25];
	char dni[9];
	char email[25];
	char cuentaBancaria[20];
	// tipo 1
} Comprador;

void imprimirComprador(Comprador comprador);
int comprarCoche(sqlite3 *db, Ticket *ticket);
int login(sqlite3 *db, char usuario[20], char contrasenya[20]);
Comprador getComprador(sqlite3 *db, char usuario[20]);
char *getNombreComprador(sqlite3 *db, char usuario[20]);

#endif /* COMPRADOR_H_ */
