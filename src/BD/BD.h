#ifndef BD_BD_H_
#define BD_BD_H_


#include "../Jerarquia/Coche/coche.h"
#include "../Jerarquia/Comprador/comprador.h"
#include "../Jerarquia/Ticket/ticket.h"
#include "../Jerarquia/Vendedor/vendedor.h"

Ticket* getTickets(sqlite3* db);
Coche* getCoches(sqlite3* db);
Comprador* getCompradores(sqlite3* db);
Vendedor* getVendedores(sqlite3* db);

int updateCoche(sqlite3* db, char matricula[10], char usuario[10]);// para cuando lo compremos

int insertTicket(sqlite3* db, char usuario[20], char matricula[40], char fechaCompra[10]);

int deleteTickets(sqlite3* db, char usuario[20]);

int loginBD(sqlite3 *db, char usuario[], char contrasenya[20]);
Coche* getMisCoches(sqlite3* db, char usuario[20]);

//int imprimirTickets(sqlite3* db, char nomComprador[25]);

// 1. selct 2. delete 3. insert 4. update

#endif
