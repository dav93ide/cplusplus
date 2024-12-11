#include <winsock2.h>
#include <windows.h>

#pragma comment (lib, "Ws2_32.lib")

#include "cSocket.h"

// WSADATA object initialize
void cSocket::init()
{
	WSADATA	wsaData;
	WSAStartup(MAKEWORD(2,2), &wsaData);
}

// WSA Cleanup
void cSocket::uninit()
{
	WSACleanup();
}

// TCP connect to a server using address + port
// Return the SOCKET or SOCKET_ERROR
SOCKET cSocket::tcpConnect(const char *addr, int port)
{
	sockaddr_in sckaddr;
    sckaddr.sin_family = AF_INET;
    sckaddr.sin_addr.s_addr = inet_addr(addr);
    sckaddr.sin_port = htons(port);
    
	SOCKET s = INVALID_SOCKET;
	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s != INVALID_SOCKET){
		if ( connect(s, (SOCKADDR *) &sckaddr, sizeof(sckaddr)) != 0){
			closesocket(s);
			s = INVALID_SOCKET;
		}
	}
	return s;
}

// Send data through a tcpsocket
int cSocket::tcpRecv(SOCKET s, char *buffer, int buffSize)
{
	int by_recv = recv(s, buffer, buffSize, 0);
	return by_recv;
	
}

// Receive data through a tcpsocket
void cSocket::tcpSend(SOCKET s, const char *buffer, int buffSize)
{
	send(s, buffer, buffSize, 0);
}

void cSocket::tcpClose(SOCKET s)
{
	if( s != INVALID_SOCKET){
		shutdown(s, SD_BOTH);
		closesocket(s);
	}
}

