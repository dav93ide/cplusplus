
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define SUCCESS 0x0
#define FAIL    -0x1
#define SOCKET_CLOSED   -0x1

#define BUFFER_SIZE 1024

class ClientUDP {
    public:
        ClientUDP(char *, int);
        ~ClientUDP();
        bool initSocket();
        void sendMsg(char *);
        int recvMsg(char *);

    private:
        char *mAddress;
        int mPort;
        int mClientSocket;
        struct sockaddr_in m_server_addr;
        socklen_t mSockLenT;


};