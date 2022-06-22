#ifndef BD_BD_H_
#define BD_BD_H_

#include "../Jerarquia/Coche/coche.h"
#include "../Jerarquia/Comprador/comprador.h"
#include "../Jerarquia/Ticket/ticket.h"
#include "../Jerarquia/Vendedor/vendedor.h"

Ticket *getAllTickets(sqlite3 *db);
Coche *getAllCoches(sqlite3 *db);
Comprador *getAllCompradores(sqlite3 *db);
Vendedor *getAllVendedores(sqlite3 *db);

// SELECT ME DEVUELVE EL TIPO
int login(sqlite3 *db, char usuario[], char contrasenya[20]);
// UPDATE
int updateCoche(sqlite3 *db, char matricula[10], char usuario[10]); // para cuando lo compremos
// INSERT
int insertTicket(sqlite3 *db, char usuario[20], char matricula[40], char fechaCompra[10]);
// SELECT
Comprador getComprador(sqlite3 *db, char usuario[20]);
// SELECT
Vendedor getVendedor(sqlite3 *db, char usuario[20]);
// SELECT
Coche *getCoches(sqlite3 *db, char usuario[20]);
// SELECT
Ticket *getTickets(sqlite3 *db, char usuario[20]);
// INSERT
int registrarComprador(sqlite3 *db, char usuario[20], char contrasenya[20], char nombre[25], char dni[9], char email[25], char cuentaBancaria[20]);
// INSERT
int registrarVendedor(sqlite3 *db, char usuario[20], char contrasenya[20], char nombre[25], char dni[9], char email[25], float sueldo, int numVentas);
// DELETE
int deleteTickets(sqlite3 *db, char usuario[20]);

// int imprimirTickets(sqlite3* db, char nomComprador[25]);

// 1. selct 2. delete 3. insert 4. update

#endif
