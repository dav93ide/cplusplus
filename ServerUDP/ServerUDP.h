#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define BUFFER_SIZE    1024

#define SUCCESS 0x0
#define FAIL    -0x1

class ServerUDP {
    public:
        ServerUDP(char *, int);
        ~ServerUDP();
        bool initSocket();
        bool bindSocket();
        int recvMsg(char *);
        void sendMsg(char *);

    private:
        char *mHostAddress;
        int mPort;
        struct sockaddr_in m_server_addr;
        struct sockaddr_in m_client_addr;
        socklen_t mSockLenT;
        int mServerSocket;
};