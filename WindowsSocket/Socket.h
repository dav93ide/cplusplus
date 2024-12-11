/* Working, ma bisogna include "Socket.cpp" */

namespace Socket{

	bool init(void);
	
	void uninit(void);
	
	int TcpRecv(SOCKET sck, char *buffer, int buffer_size);
	
	bool TcpSend(SOCKET sck, const char *buffer, int buffer_size);

	SOCKET TcpConnect(const SOCKADDR_STORAGE *sockAddr);
	
	SOCKET TcpListen(const SOCKADDR_STORAGE *sockAddr, int backlog);
	
	void TcpClose(SOCKET sck);
	
}
