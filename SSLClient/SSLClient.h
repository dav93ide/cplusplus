#include "../../All/Programming/C++/Exercises_Linux/ClientTCP/ClientTCP.h"
#include <string>
#include <openssl/ssl.h>
#include <openssl/err.h>

class SLLClient : public ClientTCP {

    public:
        SLLClient(char * address, int port, std::string pathCert, std::string pathKeyCert);
        virtual bool initSocket(void) override;
        bool connectSocket(void) override;
        virtual bool sendMsg(char *, int) override;
        virtual bool recvMsg(char *, int) override;
        virtual void closeSocket(void) override;

    private:
        SSL *mSSL;
        SSL_CTX *mCtx;
        std::string mPathCertificate;
        std::string mKeyCertificate;

        int loadCertificates();
        void initCtx();

};