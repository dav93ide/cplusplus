/* Working, ma bisogna include "Socket.cpp" */

#include <winsock2.h>
#include <shlwapi.h>
#include <ws2tcpip.h>
#include "Socket.h"

#define SIZEOF_SOCKADDR(family) ((family) == AF_INET ? sizeof(SOCKADDR_IN) : sizeof(SOCKADDR_IN6))
#define CWA(dll, api)                 ::api

bool Socket::init(void)
{
	WSADATA WSAData;
	return CWA(ws2_32, WSAStartup)(MAKEWORD(2, 2), &WSAData) == 0 ? true : false;
}

void Socket::uninit(void)
{
	CWA(ws2_32, WSACleanup)();
}

SOCKET Socket::TcpConnect(const SOCKADDR_STORAGE *sockAddr)
{
	SOCKET sck = CWA(ws2_32, socket)(sockAddr->ss_family, SOCK_STREAM, IPPROTO_TCP);
	if(sck != INVALID_SOCKET)
	{
		if(CWA(ws2_32, connect)(sck, (sockaddr *)sockAddr, SIZEOF_SOCKADDR(sockAddr->ss_family)) != 0)
		{
			CWA(ws2_32, closesocket)(sck);
			sck = INVALID_SOCKET;
		}
	}
	return sck;
}

int Socket::TcpRecv(SOCKET sck, char *buffer, int buffer_size)
{
	return CWA(ws2_32, recv)(sck, buffer, buffer_size, 0);
}

bool Socket::TcpSend(SOCKET sck, const char *buffer, int buffer_size)
{
	return (CWA(ws2_32, send)(sck, buffer, buffer_size, 0) == buffer_size) ? true : false;
}

SOCKET Socket::TcpListen(const SOCKADDR_STORAGE *sockAddr, int backlog)
{
	SOCKET sck = CWA(ws2_32, socket)(sockAddr->ss_family, SOCK_STREAM, IPPROTO_TCP);
	if(sck != INVALID_SOCKET)
	{
		if(CWA(ws2_32, bind)(sck, (sockaddr *)sockAddr, SIZEOF_SOCKADDR(sockAddr->ss_family)) != 0 || CWA(ws2_32, listen)(sck, backlog) != 0)
		{
			CWA(ws2_32, closesocket)(sck);
			sck = INVALID_SOCKET;
		}
	}
	return sck;
}

void Socket::TcpClose(SOCKET sck)
{
	if(sck != INVALID_SOCKET)
	{
		CWA(ws2_32, shutdown)(sck, SD_BOTH);
		CWA(ws2_32, closesocket)(sck);
	}
}
