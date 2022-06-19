#include "../../BD/sqlite3.h"

#ifndef TICKET_H_
#define TICKET_H_

typedef struct {
	char nomComprador[25];
	char nomCoche[40]; // marca modelo
	char fechaCompra[10];
} Ticket;

void imprimirTicket(Ticket ticket);

#endif /* TICKET_H_ */
