#include "ServerUDP.h"

ServerUDP::ServerUDP(char *address, int port){
    mHostAddress = address;
    mPort = port;
}

ServerUDP::~ServerUDP(){

}
#include <iostream>
bool ServerUDP::initSocket(){
    if((mServerSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) != FAIL){
        memset(&m_server_addr, 0x0, sizeof(m_server_addr));
        memset(&m_client_addr, 0x0, sizeof(m_client_addr));

        m_server_addr.sin_family = AF_INET;
        m_server_addr.sin_addr.s_addr = inet_addr(mHostAddress);
        m_server_addr.sin_port = htons(mPort);

        mSockLenT = sizeof(m_client_addr);
        
        return true;
    } else {
        return false;
    }
}

bool ServerUDP::bindSocket(){
    if(bind(mServerSocket, (struct sockaddr *) &m_server_addr, mSockLenT) != FAIL){
        return true;
    } else {
        return false;
    }
}

int ServerUDP::recvMsg(char *buffer){
    return recvfrom(mServerSocket, buffer, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr *) &m_client_addr, &mSockLenT);
}

void ServerUDP::sendMsg(char *buffer){
    sendto(mServerSocket, buffer, strlen(buffer), MSG_CONFIRM, (const struct sockaddr *) &m_client_addr, mSockLenT);
}