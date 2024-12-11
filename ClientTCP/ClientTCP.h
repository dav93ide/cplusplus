
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define SUCCESS 0x0
#define ERROR -0x1

class ClientTCP {
    public:
        ClientTCP(char *, int);
        virtual bool initSocket(void);
        virtual bool connectSocket(void);
        virtual bool sendMsg(char *, int);
        virtual bool recvMsg(char *, int);
        virtual void closeSocket(void);
        
    protected: 
        char *mAddress;
        int mPort;
        int mClientSocket;
        struct sockaddr_in m_server_addr;
        socklen_t m_addr_size;
        ssize_t m_ssize;
};