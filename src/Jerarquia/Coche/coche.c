#include "coche.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../BD/BD.h"
#include "../../BD/sqlite3.h"
//#include "../../Log/logger.h"

void imprimirCoche(Coche coche) {
	printf("Marca: %s\n", coche.marca);
	printf("Modelo: %s\n", coche.modelo);
	if(coche.automatico == 0){
		printf("No autom�tico\n");
	} else if(coche.automatico == 1){
		printf("Autom�tico\n");
	}
	printf("Plazas: %d\n", coche.plazas);
	printf("A�o fabricaci�n: %d\n", coche.anyoFabricacion);
}
