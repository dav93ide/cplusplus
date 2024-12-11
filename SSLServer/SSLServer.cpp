/*
    Compilazione:
        g++ test_server_ssl.cpp ServerSSL/SSLServer.cpp -o test_client_ssl.out -lssl -lcrypto -pthread
*/

#include "SSLServer.h"

SSLServer::SSLServer(char *host, int port, std::string pathCert, std::string pathKeyCert){
    mHostAddress = host;
    mPort = port;
    mPathCert = pathCert;
    mPathKeyCert = pathKeyCert;
}

bool SSLServer::start(int (*func)(SSL *ssl)){
    if(init()){
        if(bindSocket() && listenSocket()){
            while(true){
                mSockLenT = sizeof(mSockAddrStorage);
                int clientSocket = accept(mServerSocket, (struct sockaddr *) &mSockAddrIn, &mSockLenT);
                SSL *ssl = SSL_new(mCtx);
                SSL_set_fd(ssl, clientSocket);
                if(SSL_accept(ssl) != FAIL){
                    std::thread client(func, ssl);
                    client.detach();
                } else {
                    closeServerSocket();
                }
            }
        } else {
            return false;
        }
    }
    closeServerSocket();
    return true;
}

bool SSLServer::init(){
    SSL_library_init();
    initCtx();
    if(mCtx != NULL){
        if(loadCertificate() == SUCCESS){
            mServerSocket = socket(PF_INET, SOCK_STREAM, 0x0);
            mSockAddrIn.sin_family = AF_INET;
            mSockAddrIn.sin_port = htons(mPort);
            mSockAddrIn.sin_addr.s_addr = inet_addr(mHostAddress);
            memset(mSockAddrIn.sin_zero, '\0', sizeof(mSockAddrIn.sin_zero));
            return true;
        }
    }
    return false;
}

bool SSLServer::bindSocket(){
    if(bind(mServerSocket, (struct sockaddr *) &mSockAddrIn, sizeof(mSockAddrIn)) == FAIL){
        closeServerSocket();
        return false;
    }
    return true;
}

bool SSLServer::listenSocket(){
    if(listen(mServerSocket, MAX_OPEN_CONNECTIONS) == FAIL){
        closeServerSocket();
        return false;
    }
    return true;
}

void SSLServer::closeServerSocket(){
    close(mServerSocket);
    SSL_CTX_free(mCtx);
}

void SSLServer::initCtx(){
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();
    const SSL_METHOD *method = SSLv23_server_method();
    mCtx = SSL_CTX_new(method);
}

int SSLServer::loadCertificate(){
    if(SSL_CTX_load_verify_locations(mCtx, mPathCert.c_str(), mPathKeyCert.c_str()) != 0x1){
        return FAIL;
    }
    if(SSL_CTX_set_default_verify_paths(mCtx) != 0x1){
        return FAIL;
    }
    if(SSL_CTX_use_certificate_file(mCtx, mPathCert.c_str(), SSL_FILETYPE_PEM) <= 0x0){
        return FAIL;
    }
    if(SSL_CTX_use_PrivateKey_file(mCtx, mPathKeyCert.c_str(), SSL_FILETYPE_PEM) <= 0x0){
        return FAIL;
    }
    if(!SSL_CTX_check_private_key(mCtx)){
        return FAIL;
    }
    SSL_CTX_set_verify(mCtx, SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT, NULL);
    SSL_CTX_set_verify_depth(mCtx, 4);
    return SUCCESS;
}
