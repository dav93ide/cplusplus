#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")


int main(int argc, char* argv[]){
	WSADATA wsa;
	SOCKET sck, new_socket;
	struct sockaddr_in server, client;
	int c;
	char *message;
	char recv_buffer[1024];
	
	
	if(WSAStartup(MAKEWORD(2,2),&wsa) != 0){
		printf("[+] Inizializzazione Fallita. Codice D'Errore: %d\n",WSAGetLastError());
		return 1;
	}
	printf("[+] Winsock inizializzata...\n");
	
	sck = socket(AF_INET,SOCK_STREAM,0);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = htons((unsigned short) 6667);
	
	bind(sck, (struct sockaddr *)&server, sizeof(server));
	
	listen(sck, 3);
	
	c = sizeof(struct sockaddr_in);
	new_socket = accept(sck, (struct sockaddr *)&client, &c);
	
	if(new_socket != INVALID_SOCKET)
	{
		printf("[+] Client Accepted...\n");
	}
	else
	{
		printf("[-] Error While Accepting Connection...\n");
	}
	
	message = "Hello Client!";
	int size = strlen(message);
	send(new_socket, size, 8, 0);
	send(new_socket, message, strlen(message), 0);
	recv(new_socket, recv_buffer, 1024, 0);
	printf("[+] Messaggio Ricevuto: %s", recv_buffer);
	printf("[+] Message Sent...\n[+] Press A Button To Terminate...");
	getchar();
	closesocket(sck);
	WSACleanup();
	
	return 0;
	
}
