// IMPORTANT: Winsock Library ("ws2_32") should be linked

#include <stdio.h>
#include <winsock2.h>
#include <math.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000

void menu(SOCKET comm_socket);

int main(int argc, char *argv[])
{

	//	sqlite3 *db;
	//
	//	int result = sqlite3_open("BD/DB.db", &db);
	//	if (result != SQLITE_OK) {
	//		LOG_PRINT("Error opening database\n");
	//	}

	WSADATA wsaData;
	SOCKET conn_socket;
	SOCKET comm_socket;
	struct sockaddr_in server;
	struct sockaddr_in client;
	char sendBuff[512], recvBuff[512];
	char opcion[20], opcion2[20], usuario[20], contrasenya[20];

	printf("\nInitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		return -1;
	}

	printf("Initialised.\n");

	// SOCKET creation
	if ((conn_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	printf("Socket created.\n");

	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	// BIND (the IP/port with socket)
	if (bind(conn_socket, (struct sockaddr *)&server,
			 sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code: %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	printf("Bind done.\n");

	// LISTEN to incoming connections (socket server moves to listening mode)
	if (listen(conn_socket, 1) == SOCKET_ERROR)
	{
		printf("Listen failed with error code: %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	// ACCEPT incoming connections (server keeps waiting for them)
	printf("Waiting for incoming connections...\n");
	int stsize = sizeof(struct sockaddr);
	comm_socket = accept(conn_socket, (struct sockaddr *)&client, &stsize);
	// Using comm_socket is able to send/receive data to/from connected client
	if (comm_socket == INVALID_SOCKET)
	{
		printf("accept failed with error code : %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}
	printf("Incomming connection from: %s (%d)\n", inet_ntoa(client.sin_addr),
		   ntohs(client.sin_port));

	// Closing the listening sockets (is not going to be used anymore)
	closesocket(conn_socket);

	// SEND and RECEIVE data (CLIENT/SERVER PROTOCOL)
	printf("Waiting for incoming commands from client... \n");

	//////////////////////////////////////////
	//	recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
	//	printf(recvBuff);
	//	strcpy(sendBuff, recvBuff);
	//	send(comm_socket, sendBuff, sizeof(sendBuff), 0);

	do
	{
		recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
		strcpy(opcion, recvBuff);
		printf("%s \n", recvBuff);
		
		if (strcmp(recvBuff, "login") == 0)
		{
			printf("entra en el if \n");
			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			strcpy(usuario, recvBuff);
			printf("%s \n", usuario);
			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			strcpy(contrasenya, recvBuff);
			printf("%s \n", contrasenya);

			//dentro del if llamamos al metodo bd con los dos atributos, si ok, dpm
			if(strcmp(usuario, "serch") == 0 && strcmp(contrasenya, "123") == 0){
				strcpy(sendBuff, "correcto");
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);

				do{
					recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
					strcpy(opcion2, recvBuff);
					if (strcmp(opcion2, "comprarCoches") == 0)
					{
						/* code */
					}
					if (strcmp(opcion2, "misCoches") == 0)
					{
						/* code */
					}
					if (strcmp(opcion2, "misTickets") == 0)
					{
						/* code */
					}
					if (strcmp(opcion2, "verPerfil") == 0)
					{
						/* code */
					}
				} while (strcmp(opcion2, "cerrarSesion") == 0);
			}else{
				strcpy(sendBuff, "erroneo");
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
			}
		}
		if (strcmp(recvBuff, "register") == 0)
		{
			printf("entra en el if \n");
			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			strcpy(usuario, recvBuff);
			printf("%s \n", usuario);
			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			strcpy(contrasenya, recvBuff);
			printf("%s \n", contrasenya);

			// los devolvemos para comprobar que llegan
			strcpy(recvBuff, usuario);
			send(comm_socket, sendBuff, sizeof(sendBuff), 0);
			strcpy(recvBuff, contrasenya);
			send(comm_socket, sendBuff, sizeof(sendBuff), 0);
		}
		// if (strcmp(recvBuff, "exit") == 0)
		// {
			
		// }
		// switch (opcion)
		// {
		// case 1:
		// 	// Inicio de sesion
		// 	recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
		// 	strcpy(usuario, recvBuff);
		// 	recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
		// 	strcpy(contrasenya, recvBuff);

		// 	// los devolvemos para comprobar que llegan
		// 	strcpy(recvBuff, usuario);
		// 	send(comm_socket, sendBuff, sizeof(sendBuff), 0);
		// 	strcpy(recvBuff, contrasenya);
		// 	send(comm_socket, sendBuff, sizeof(sendBuff), 0);
		// 	break;
		// case 2:
		// 	// Registro

		// 	break;
		// case 3:
		// 	// Salir
		// 	printf("Servidor finalizado");
		// 	break;
		// default:
		// 	printf("Error, el parametro de entrada no coincide.");
		// 	break;
		// }
	} while (strcmp(opcion,"exit") != 0);

	// CLOSING the sockets and cleaning Winsock...
	closesocket(comm_socket);
	WSACleanup();

	return 0;
	// do {
	// 	recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
	// 	opcion = atoi(recvBuff);
	// 	switch(opcion){
	// 		case 1:
	// 			//mandar instruccion mostrarCoches al servidor

	// 			strcpy(sendBuff, "Hola");
	// 			send(comm_socket, sendBuff, sizeof(sendBuff), 0);
	// 			break;
	// 		case 2 :
	// 			//mandar instruccion misCoches al servidor

	// 			break;
	// 		case 3 :
	// 			//mandar instruccion misTickets al servidor
	// 			printf("Servidor finalizado");
	// 			break;
	// 		default:
	// 			printf("Error, el parametro de entrada no coincide.");
	// 			break;
	// 	}
	// } while (opcion != 5);
}