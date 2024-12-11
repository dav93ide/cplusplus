
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define SUCCESS 0x0
#define ERROR   -0x1

class ClientTCP {
    private: 
        char *mAddress;
        int mPort;
        int mClientSocket;
        struct sockaddr_in m_server_addr;
        socklen_t m_addr_size;
        ssize_t m_ssize;

    public:
        ClientTCP(char *, int);
        void initSocket(void);
        bool connectSocket(void);
        bool sendMsg(char *, int);
        bool recvMsg(char *, int);
        void closeSocket(void);
        
};