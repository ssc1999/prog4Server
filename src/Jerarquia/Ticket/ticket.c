#include "ticket.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../BD/BD.h"
#include "../../BD/sqlite3.h"
//#include "../../Log/logger.h"

void imprimirTicket(Ticket ticket) {
	printf("Nombre comprador: %s\n", ticket.nomComprador);
	printf("Nombre coche: %s\n", ticket.matricula);
	printf("Fecha compra: %s\n", ticket.fechaCompra);
}
