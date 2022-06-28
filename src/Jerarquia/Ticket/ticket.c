#include "ticket.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../Logger/log.h"
#include "../../BD/BD.h"
#include "../../BD/sqlite3.h"
//#include "../../Log/logger.h"

void imprimirTicket(Ticket ticket) {
	printf("Nombre comprador: %s\n", ticket.nomComprador);
	printf("Nombre usuario: %s\n", ticket.nomUsuario);
	printf("Matr�cula: %s\n", ticket.matricula);
	printf("Fecha compra: %s\n", ticket.fechaCompra);
}

Ticket* getTicket(sqlite3 *db, char usuario[20]){
	log_trace("Consultando ticket a la BD");
	Ticket *ticket = (Ticket *)malloc(sizeof(Ticket));
	ticket = getTicketBD(db, usuario);
	log_trace("Mandando ticket al server");
	return ticket;
}
