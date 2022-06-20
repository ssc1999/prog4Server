// IMPORTANT: Winsock Library ("ws2_32") should be linked

#include <stdio.h>
#include <winsock2.h>
#include <math.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000

void menu(SOCKET comm_socket);

int main(int argc, char *argv[]) {

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

	printf("\nInitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("Failed. Error Code : %d", WSAGetLastError());
		return -1;
	}

	printf("Initialised.\n");

	//SOCKET creation
	if ((conn_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		printf("Could not create socket : %d", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	printf("Socket created.\n");

	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	//BIND (the IP/port with socket)
	if (bind(conn_socket, (struct sockaddr*) &server,
			sizeof(server)) == SOCKET_ERROR) {
		printf("Bind failed with error code: %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	printf("Bind done.\n");

	//LISTEN to incoming connections (socket server moves to listening mode)
	if (listen(conn_socket, 1) == SOCKET_ERROR) {
		printf("Listen failed with error code: %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	//ACCEPT incoming connections (server keeps waiting for them)
	printf("Waiting for incoming connections...\n");
	int stsize = sizeof(struct sockaddr);
	comm_socket = accept(conn_socket, (struct sockaddr*) &client, &stsize);
	// Using comm_socket is able to send/receive data to/from connected client
	if (comm_socket == INVALID_SOCKET) {
		printf("accept failed with error code : %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}
	printf("Incomming connection from: %s (%d)\n", inet_ntoa(client.sin_addr),
			ntohs(client.sin_port));

	// Closing the listening sockets (is not going to be used anymore)
	closesocket(conn_socket);

	//SEND and RECEIVE data (CLIENT/SERVER PROTOCOL)
	printf("Waiting for incoming commands from client... \n");

	//////////////////////////////////////////
//	recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
//	printf(recvBuff);
//	strcpy(sendBuff, recvBuff);
//	send(comm_socket, sendBuff, sizeof(sendBuff), 0);



	menu(comm_socket);
	printf("ha salido del menu");

	// CLOSING the sockets and cleaning Winsock...
	closesocket(comm_socket);
	WSACleanup();

	return 0;
}

void menu(SOCKET comm_socket)
{
	char sendBuff[512], recvBuff[512];
	int opcion;
		do {
			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			opcion = atoi(recvBuff);
			if(strcmp(recvBuff, "1")){
				printf("Ha entrado");
				strcpy(sendBuff, "Hola");
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
			}
//			switch(opcion){
//				case 1:
//					//mandar instruccion mostrarCoches al servidor
//					printf("Ha entrado");
//					strcpy(sendBuff, "Hola");
//					send(comm_socket, sendBuff, sizeof(sendBuff), 0);
//					break;
//				case 2 :
//					//mandar instruccion misCoches al servidor
//
//					break;
//				case 3 :
//					//mandar instruccion misTickets al servidor
//
//					break;
//				case 4:
//					//mandar instruccion miPerfil al servidor
//
//					break;
//				case 5:
//					//mandar instruccion salir
//					printf("Servidor finalizado");
//					break;
//				default:
//					printf("Error, el parametro de entrada no coincide.");
//					break;
//			}
		} while (opcion != 5);
}
