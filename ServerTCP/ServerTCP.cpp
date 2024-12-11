/*
    Compilazione con define di DEBUG:
        g++ test.cpp ServerTCP.cpp -pthread -D _DEBUG -o test_server_tcp.out 
*/

#include "ServerTCP.h"

ServerTCP::ServerTCP(char *hostAddress, int port){
    mHostAddress = hostAddress;
    mPort = port;
    init();
}

ServerTCP::~ServerTCP(){
    closeServerSocket();
}

bool ServerTCP::start(int (*func)(int)){
    if(bindSocket() && listenSocket()){
        while(true){
            mSockLenT = sizeof(mSockAddrStorage);
            int clientSocket = accept(mServerSocket, (struct sockaddr *) &mSockAddrIn, &mSockLenT);     // Accettare una chiamata crea una nuova socket per la connessione in ingresso
#ifdef _DEBUG
            std::cout << "\n\n[+] New client connection! Socket: " << clientSocket << std::endl;
#endif
            std::thread client(func, clientSocket);
            client.detach();
        }
    } else {
        return false;
    }
    closeServerSocket();
    return true;
}

bool ServerTCP::init(){
    mServerSocket = socket(PF_INET, SOCK_STREAM, 0x0);          // Init socket.
    mSockAddrIn.sin_family = AF_INET;                           // Configura le impostazioni della struttura indirizzo del server (Famiglia di indirizzi = Internet).
    mSockAddrIn.sin_port = htons(mPort);                        // Setta il numero di porta utilizzando "htons()" per usare un ordine di bytes corretto.
    mSockAddrIn.sin_addr.s_addr = inet_addr(mHostAddress);      // Setta l'indirizzo IP convertendolo da array di char a bytes.
    memset(mSockAddrIn.sin_zero, '\0', sizeof(mSockAddrIn.sin_zero));   // Setta tutti i bits del campo padding a 0
    return true;
}

bool ServerTCP::bindSocket(){
    if(bind(mServerSocket, (struct sockaddr *) &mSockAddrIn, sizeof(mSockAddrIn)) == FAIL){
#ifdef _DEBUG
        std::cerr << "[!] Error bind socket." << std::endl;
#endif
        closeServerSocket();
        return false;
    }
#ifdef _DEBUG
        std::cout << "[+] Success bind socket." << std::endl;
#endif
    return true;
}

bool ServerTCP::listenSocket(){
    if(listen(mServerSocket, MAX_OPEN_CONNECTIONS) == FAIL){
#ifdef _DEBUG
        std::cerr << "[!] Error listen socket." << std::endl;
#endif
        closeServerSocket();
        return false;
    }
#ifdef _DEBUG
        std::cout << "[+] Listening..." << std::endl;
#endif
    return true;
}

void ServerTCP::closeServerSocket(){
    if(mServerSocket != SOCKET_CLOSED){
        close(mServerSocket);
        mServerSocket = SOCKET_CLOSED;
    }
}