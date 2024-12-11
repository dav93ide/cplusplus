#include "ClientTCP.h"

ClientTCP::ClientTCP(char *address, int port){
    mAddress = address;
    mPort = port;
}

bool ClientTCP::initSocket(){
    mClientSocket = socket(PF_INET, SOCK_STREAM, 0x0);
    m_server_addr.sin_family = AF_INET;
    m_server_addr.sin_port = htons(mPort);
    m_server_addr.sin_addr.s_addr = inet_addr(mAddress);
    memset(m_server_addr.sin_zero, '\0', sizeof m_server_addr.sin_zero);
    m_addr_size = sizeof m_server_addr;
    return true;
}

bool ClientTCP::connectSocket(){
    return connect(mClientSocket, (struct sockaddr *) &m_server_addr, m_addr_size) == SUCCESS;
}

bool ClientTCP::sendMsg(char *buffer, int size){
    return send(mClientSocket, buffer, size, 0x0) != ERROR;
}

bool ClientTCP::recvMsg(char *buffer, int size){
    return recv(mClientSocket, buffer, size, 0x0) != ERROR;
}

void ClientTCP::closeSocket(){
    close(mClientSocket);
}