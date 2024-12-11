#include "ClientUDP.h"

ClientUDP::ClientUDP(char *address, int port){
    mAddress = address;
    mPort = port;
}

ClientUDP::~ClientUDP(){

}

bool ClientUDP::initSocket(){
    if((mClientSocket = socket(AF_INET, SOCK_DGRAM, 0x0)) != FAIL){
        m_server_addr.sin_family = AF_INET;
        m_server_addr.sin_port = htons(mPort);
        m_server_addr.sin_addr.s_addr = inet_addr(mAddress);

        mSockLenT = sizeof m_server_addr;
        return true;
    } else {
        return false;
    }
}

void ClientUDP::sendMsg(char *buffer){
    sendto(mClientSocket, buffer, strlen(buffer), MSG_CONFIRM, (const struct sockaddr *) &m_server_addr, mSockLenT);
}

int ClientUDP::recvMsg(char *buffer){
    return recvfrom(mClientSocket, (char *) buffer, MSG_WAITALL, MSG_WAITALL, (struct sockaddr *) &m_server_addr, &mSockLenT);
}