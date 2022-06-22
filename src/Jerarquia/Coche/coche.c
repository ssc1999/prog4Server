#include "coche.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../BD/BD.h"
#include "../../BD/sqlite3.h"
//#include "../../Log/logger.h"

void imprimirCoche(Coche coche) {
	printf("Matricula: %s\n", coche.matricula);
	printf("Marca: %s\n", coche.marca);
	printf("Modelo: %s\n", coche.modelo);
	if(coche.automatico == 0){
		printf("No automatico\n");
	} else if(coche.automatico == 1){
		printf("Automatico\n");
	}
	printf("Plazas: %d\n", coche.plazas);
	printf("Anyo fabricacion: %d\n", coche.anyoFabricacion);
}
