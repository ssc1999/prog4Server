#include "vendedor.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../BD/BD.h"
#include "../../BD/sqlite3.h"
//#include "../../Log/logger.h"

void imprimirVendedor(Vendedor vendedor) {
	printf("Nombre: %s\n", vendedor.nombre);
	printf("Dni: %s\n", vendedor.dni);
	printf("Email: %s\n", vendedor.email);
	printf("Sueldo: %f\n", vendedor.sueldo);
	printf("Número de ventas: %f\n", vendedor.numVentas);
}
