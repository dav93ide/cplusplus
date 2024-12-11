/*
    Compilation:
        g++ testSC.cpp ../All/Programming/C++/Exercises_Linux/ClientTCP/ClientTCP.cpp SSLClient/SSLClient.cpp -o test_client_ssl.out -lssl -lcrypto
*/

#include "SSLClient.h"

SLLClient::SLLClient(char * address, int port, std::string pathCert, std::string pathKeyCert) : ClientTCP(address, port) {
    mPathCertificate = pathCert;
    mKeyCertificate = pathKeyCert;
}

bool SLLClient::initSocket() {
    SSL_library_init();
    initCtx();
    if(mCtx != NULL && loadCertificates() == SUCCESS){
        ClientTCP::initSocket();
        mSSL = SSL_new(mCtx);
        SSL_set_fd(mSSL, mClientSocket);
        return true;
    }
    return false;
}

bool SLLClient::connectSocket(void){
    return ClientTCP::connectSocket() && SSL_connect(mSSL) != -0x1;
}

bool SLLClient::sendMsg(char * msg, int len){
    return SSL_write(mSSL, msg, len);
}

bool SLLClient::recvMsg(char *buffer, int len){
    return SSL_read(mSSL, buffer, len);
}

void SLLClient::closeSocket(void){
    SSL_free(mSSL);
    ClientTCP::closeSocket();
    SSL_CTX_free(mCtx);
}

int SLLClient::loadCertificates(){
    if(SSL_CTX_use_certificate_file(mCtx, mPathCertificate.c_str(), SSL_FILETYPE_PEM) <= 0x0){
        return ERROR;
    }
    if(SSL_CTX_use_PrivateKey_file(mCtx, mKeyCertificate.c_str(), SSL_FILETYPE_PEM) <= 0x0){
        return ERROR;
    }
    if(!SSL_CTX_check_private_key(mCtx)){
        return ERROR;
    }
    return SUCCESS;
}   

void SLLClient::initCtx(){
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();

    const SSL_METHOD *method = SSLv23_client_method();
    mCtx = SSL_CTX_new(method);
}