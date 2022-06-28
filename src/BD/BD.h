#ifndef BD_BD_H_
#define BD_BD_H_

#include "../Jerarquia/Coche/coche.h"
#include "../Jerarquia/Comprador/comprador.h"
#include "../Jerarquia/Ticket/ticket.h"
#include "../Jerarquia/Vendedor/vendedor.h"


Coche** getAllCoches(sqlite3 *db);
// SELECT ME DEVUELVE EL TIPO
int login(sqlite3 *db, char usuario[], char contrasenya[20]);
// UPDATE
int updateCocheBD(sqlite3 *db, char matricula[20], char usuario[20]); // para cuando lo compremos
// INSERT
int insertTicket(sqlite3 *db, Ticket *ticket);
// SELECT
Comprador* getCompradorBD(sqlite3 *db, char usuario[20]);
// SELECT
Vendedor* getVendedorBD(sqlite3 *db, char usuario[20]);
// SELECT
Coche* getCocheBD(sqlite3 *db, char usuario[20]);
// SELECT
Ticket *getTicketBD(sqlite3 *db, char usuario[20]);
// INSERT
int registrarComprador(sqlite3 *db, char usuario[20], char contrasenya[20], char nombre[25], char dni[9], char email[25], char cuentaBancaria[20]);
// INSERT
int registrarVendedor(sqlite3 *db, char usuario[20], char contrasenya[20], char nombre[25], char dni[9], char email[25]);

#endif
