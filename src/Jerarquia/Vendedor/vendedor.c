#include "vendedor.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../Logger/log.h"
#include "../../BD/BD.h"
#include "../../BD/sqlite3.h"
//#include "../../Log/logger.h"

void imprimirVendedor(Vendedor vendedor) {
	printf("Nombre: %s\n", vendedor.nombre);
	printf("Dni: %s\n", vendedor.dni);
	printf("Email: %s\n", vendedor.email);
	printf("Sueldo: %f\n", vendedor.sueldo);
	printf("Numero de ventas: %f\n", vendedor.numVentas);
}

Vendedor* getVendedor(sqlite3 *db, char usuario[20]){
	log_trace("Consultando vendedor a la BD");
	Vendedor *vendedor = (Vendedor *)malloc(sizeof(Vendedor));
	vendedor = getVendedorBD(db, usuario);
	log_trace("Mandando vendedor al server");
	return vendedor;
}