#include "../../BD/sqlite3.h"

#ifndef TICKET_H_
#define TICKET_H_

typedef struct {
	char nomComprador[20];
	char nomUsuario[20];
	char matricula[20];
	char fechaCompra[10];
	int precio;
} Ticket;

void imprimirTicket(Ticket ticket);
Ticket* getTicket(sqlite3 *db, char usuario[20]);
void insertTicket(sqlite3 *db, Ticket *ticket);
#endif /* TICKET_H_ */
