namespace cSocket
{	
	void init();
	
	void uninit();
	
	SOCKET tcpConnect(const char *addr, int port);
	
	int tcpRecv(SOCKET s, char *buffer, int buffSize);
	
	void tcpSend(SOCKET s, const char *buffer, int buffSize);
	
	void tcpClose();
};
