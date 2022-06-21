#include "../../BD/sqlite3.h"

#ifndef TICKET_H_
#define TICKET_H_

typedef struct {
	char nomComprador[20];
	char nombreUsuario[20];
	char matricula[20];
	char fechaCompra[10];
} Ticket;

void imprimirTicket(Ticket ticket);

#endif /* TICKET_H_ */
