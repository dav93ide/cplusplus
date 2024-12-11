#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>         // "close()"
#include <thread>
#include <string>

#define MAX_OPEN_CONNECTIONS    20
#define BUFFER_SIZE    1024

#define SUCCESS 0x0
#define FAIL    -0x1
#define SOCKET_CLOSED   -0x1

#define CLIENT_HANDSHAKE    "._Client-Hand-Shake_."
#define SERVER_HANDSHAKE    "._Server-Hand-Shake_."

#define CMD_STOP    "cmd_stop"

class ServerTCP {
    public:
        ServerTCP(char *, int);         // Costruttore
        ~ServerTCP();                   // Distruttore
        virtual bool start(int (*func)(int));

    private:
        char *mHostAddress;
        int mPort;
        struct sockaddr_in mSockAddrIn;
        struct sockaddr_storage mSockAddrStorage;
        socklen_t mSockLenT;
        int mServerSocket;

        virtual bool init();
        bool bindSocket();
        bool listenSocket();
        virtual void closeServerSocket();
};