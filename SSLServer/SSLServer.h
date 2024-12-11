#include <cstring>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>         // "close()"
#include <thread>
#include <string>
#include <openssl/ssl.h>
#include <openssl/types.h>

#define MAX_OPEN_CONNECTIONS    20
#define BUFFER_SIZE    1024

#define SUCCESS 0x0
#define FAIL    -0x1
#define SOCKET_CLOSED   -0x1

class SSLServer {

    public:
        SSLServer(char *host, int port, std::string pathCert, std::string pathKeyCert);
        bool start(int (*func)(SSL *ssl));

    private:
        char *mHostAddress;
        int mPort;
        struct sockaddr_in mSockAddrIn;
        struct sockaddr_storage mSockAddrStorage;
        socklen_t mSockLenT;
        int mServerSocket;

        SSL_CTX *mCtx;
        std::string mPathCert;
        std::string mPathKeyCert;

        bool init();
        bool bindSocket();
        bool listenSocket();
        void closeServerSocket();
        void initCtx();
        int loadCertificate();

};