#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <map>
#include <stdio.h>
#include <iostream>
#include <string>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

using namespace std;



int main(int argc,char *argv[])
{
	
	
	
	WSADATA	wsaData;
	sockaddr_in server;
	SOCKET clientsocket;
	SOCKET servers;
	
	WSAStartup (MAKEWORD(2,2), &wsaData);
	int status;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(27015);
	servers = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	
	status = bind(servers, (SOCKADDR *) &server, sizeof(server));
	
	
	
	if( status == SOCKET_ERROR){
		printf("bind Error");
		closesocket(servers);
		WSACleanup();
		exit(1);
	}
	
	cout << "status = " << status << endl;
	cout << "Bind Success" << endl;
	
	status = listen(servers, SOMAXCONN);
	
	
	
	if ( status == SOCKET_ERROR){
		printf("listening Error");
		closesocket(servers);
		WSACleanup();
		exit(1);
	}
	
	cout << "status = " << status << endl;
	cout << "Listening Success.. Waiting connection..." << endl;
	
	clientsocket = accept(servers, NULL, NULL);
	
	if (clientsocket != INVALID_SOCKET){
		cout << "Client connected" << endl;
		cout << "Sending Message" << endl;
		string mex("CiaoCiao");
		const char *send_mex = mex.c_str();
		send(clientsocket, send_mex, 1024, 0);
		cout << "Message Sent" << mex << endl;
		mex = "end";
		send_mex = mex.c_str();
		send(clientsocket, send_mex, 1024, 0);
		cout << "end sent" << endl;
		char buffer[1024];
		recv(clientsocket, buffer, 1024, 0);
		cout << "received:"<<buffer;
	}
	
	printf("Closing");
	closesocket(servers);
	WSACleanup();
	int a;
	cin >> a;
	exit(1);
}
