/*
    Compiled using:
        g++ main.cpp ClientTCP.cpp
*/

#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "ClientTCP.h"

using namespace std;

int main(){
    ClientTCP client = ClientTCP( (char*) LOCALHOST, PORT);
    client.initSocket();
    if(client.connectSocket()){
        std::cout << "[+] Connected...";
    }
    char bSend[50];
    strcpy(bSend, "Test...");
    client.sendMsg(bSend, strlen(bSend));
    client.closeSocket();
}