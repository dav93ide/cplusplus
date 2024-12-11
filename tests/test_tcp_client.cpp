/*
    # Compilation:
        g++ test_tcp_client.cpp -o tcp_client.out ../ClientTCP/ClientTCP.cpp

    # Compilation with _DEBUG:
        g++ test_tcp_client.cpp -o tcp_client.out ../ClientTCP/ClientTCP.cpp -D_DEBUG
*/
#include <iostream>
#include "../ClientTCP/ClientTCP.h"

#define ADDRESS "127.0.0.1"
#define PORT    6666

#define MSG_SIZE    1024

#define CLIENT_HANDSHAKE    "._Client-Hand-Shake_."
#define SERVER_HANDSHAKE    "._Server-Hand-Shake_."

#define CMD_STOP    "cmd_stop"

int main(){
    ClientTCP *clientTcp = new ClientTCP(strdup(ADDRESS), PORT);
    clientTcp->initSocket();
#ifdef _DEBUG
    std::cout << "[+] Socket Initialized..." << std::endl;
#endif
    if(clientTcp->connectSocket()){
#ifdef _DEBUG
        std::cout << "[+] Socket connection success..." << std::endl;
#endif
        char msg[MSG_SIZE];
        strcpy(msg, CLIENT_HANDSHAKE);
        if(clientTcp->sendMsg(msg, strlen(msg))){
#ifdef _DEBUG
            std::cout << "[+] Sent Client Handshake." << std::endl;
#endif
            clientTcp->recvMsg(msg, MSG_SIZE);
            if(strcmp((const char *) msg, SERVER_HANDSHAKE) == 0x0){
#ifdef _DEBUG
            std::cout << "[+] Got Server Handshake." << std::endl;
#endif
                int cmd = 0x0;
                while(cmd != -0x1){
                    std::cout << "[?] enter command: ";
                    std::cin >> cmd;
                    if(cmd == -0x1){
                        strcpy(msg, CMD_STOP);
                    } else {
                        sprintf(msg, "%d", cmd);
                    }
                    if(clientTcp->sendMsg(msg, sizeof(msg))){
#ifdef _DEBUG
                        std::cout << "[+] Sent msg: " << msg << std::endl;
#endif
                    }
#ifdef _DEBUG
                    else {
                        std::cerr << "[!] Fail send msg: " << msg << std::endl;
                    }
#endif
                }
            }
#ifdef _DEBUG
            else {
                std::cerr << "[!] Fail receive server handshake." << std::endl;
            }
#endif
        }
#ifdef _DEBUG
        else {
            std::cerr << "[!] Fail send client handshake." << std::endl;
        }
#endif
        clientTcp->closeSocket();
#ifdef _DEBUG
        std::cout << "[+] Socket closed." << std::endl;
#endif
    }
#ifdef _DEBUG
    else {
        std::cerr << "[!] Socket connection fail..." << std::endl;   
    }
#endif
    return 0x0;
}