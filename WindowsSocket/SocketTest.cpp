/* Working, ma bisogna include "Socket.cpp" */

#include <stdio.h>
#include <winsock2.h>
#include <iostream>
#include "Socket.cpp"

using namespace std;

#pragma comment (lib, "Ws2_32.lib")

int main()
{
	SOCKET sck;
	char server_reply[1024];
	const char *send_buffer = "Prova!";
	int size;
		
	SOCKADDR_IN server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_address.sin_port = htons((unsigned short) 6667);
		
	cout << "[+] Starting..." << endl;
	
	if(Socket::init())
	{
		cout << "[+] Socket Init Ok... " << endl;
	}
	else
	{
		cout << "[-] Socket Init Error... " << endl;
	}
	sck = Socket::TcpConnect( (SOCKADDR_STORAGE *) &server_address);
	
	if( sck != INVALID_SOCKET)
	{
		cout << "[+] Connected..." << endl;
	}
	else
	{
		cout << "[-] Connection Error..." << endl;
	}
	
	
	size = Socket::TcpRecv(sck, server_reply, 1024);
	
	if(size){ cout << "OK" << endl; } else { cout<<"ERROR"<<endl;}
	
	cout << "[+] Ricevuto in risposta:\n\n\n"<< server_reply <<"\n\n\n\n[+] Invio Messaggio di test...\n";
	
	Socket::TcpSend(sck, send_buffer, (int) strlen(send_buffer));
	
	Socket::TcpClose(sck);
	
	Socket::uninit();
	
	getchar();
	
	return 0;
}
