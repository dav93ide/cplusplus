/* 
    #------------------------------#
    | [Exercise 1] TCP Server C++  |
    #------------------------------#
    ~ Compilare con:
        $ g++ -pthread -o 1_tcp_server 1_TCP_Server.cpp
    
    ~ Avviare con:
        $ sudo ./1_tcp_server <num_port>
    Senza 'sudo' non ha i permessi per aprire una nuova porta di conseguenza non funziona.
    #------------------------------#
*/

#include <cstring>          // "sizeof()"
#include <iostream>
#include <string>
#include <unistd.h>         // "close()"
#include <pthread.h>
#include <cstdlib>          // "atoi()"

// Headers per "socket()", "getaddrinfo()" ecc..
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>

#define BUFFER_SIZE     1024
// Max dimensione del messaggio client
#define MAX_MSG_SIZE    2000
// Numero di connessioni permesse nella coda entrante
#define MAX_IN_CONNTS   0x8

#define LOCALHOST       "127.0.0.1"

#define IPV4    "IPv4"
#define IPV6    "IPv6"

#define CLIENT_HANDSHAKE    "._Client-Hand-Shake_."
#define SERVER_HANDSHAKE    "._Server-Hand-Shake_."

#define COMMAND_STOP        "cmd_stop"

#define SUCCESS     0x0
#define ERROR       -0x1

#define RET_ERR_PROGRAM_ARGS    -0x1
#define RET_ERR_GET_ADDRINFO    -0x2
#define RET_ERR_NO_HOST_ADDRS   -0x3
#define RET_ERR_CREATE_SOCKET   -0x4
#define RET_ERR_BIND_SOCKET     -0x5
#define RET_ERR_LISTNG_SOCKET   -0x6

void *socketThread(void *);

// Il numero di porta viene passato al programma come argomento da shell.
int main(int argc, char *argv[]){

    // Controlla se il numero di porta e` tra gli argomenti (args size == 2)
    if(argc != 0x2){
        std::cerr << "[-] Run with: \'program <port>\'\n";
        return -0x1;
    }
    int portNumber = atoi(argv[0x1]);
    int serverSocket, newSocket;
    struct sockaddr_in server_addr;
    struct sockaddr_storage server_storage;
    socklen_t addr_size;
    pthread_t tid[MAX_IN_CONNTS];

    // Creazione del socket
    serverSocket = socket(PF_INET, SOCK_STREAM, 0x0);
    std::cout << "[+] serverSocket: " << serverSocket << std::endl;
    // Configura le impostazioni della struttura indirizzo del server (Famiglia di indirizzi = Internet)
    server_addr.sin_family = AF_INET;
    // Setta il numero di porta utilizzando "htons()" per usare un ordine di bytes corretto
    server_addr.sin_port = htons(portNumber);
    // Setta l'indirizzo IP a localhost
    server_addr.sin_addr.s_addr = inet_addr(LOCALHOST);

    // Setta tutti i bitst del campo padding a 0
    memset(server_addr.sin_zero, '\0', sizeof server_addr.sin_zero);

    // Aggancia il socket alla struttura indirizzo
    int bindResult = bind(serverSocket, (struct sockaddr *) &server_addr, sizeof server_addr);
    if( bindResult == ERROR){
        std::cerr << "[-] Error while binding socket, bindResult: " << bindResult << std::endl;

        // Se accade qualche errore e` necessario chiudere la socket e liberare le risorse.
        close(serverSocket);
        return RET_ERR_BIND_SOCKET;
    }

    // Inizia ad ascoltare per connessioni in ingresso sulla socket
    if(listen(serverSocket, MAX_IN_CONNTS) == ERROR){
        std::cerr << "[-] Error while listening on socket\n";
        close(serverSocket);
        return RET_ERR_LISTNG_SOCKET;
    } else {
        std::cout << "[+] Listening..." << std::endl;
    }

    int i = 0x0;
    while(true){
        // Accettare una chiamata crea una nuova socket per la connessione in ingresso
        addr_size = sizeof server_storage;
        newSocket = accept(serverSocket, (struct sockaddr *) &server_storage, &addr_size);
        i++;
        // Per ogni richiesta client viene creato un thread e gli viene assegnata la richiesta 
        // del client per processarla in modo tale che il thread principale possa gestire nuove richieste.
        if(pthread_create(&tid[i], NULL, socketThread, &newSocket) != SUCCESS){
            std::cout << "[-] Failed to create new thread." << std::endl;
        }

        if(i >= MAX_IN_CONNTS){
            i = 0x0;
            while(i < MAX_IN_CONNTS){
                pthread_join(tid[i++], NULL);
            }
            i = 0x0;
        }
    }
    close(serverSocket);
    return 0x0;
}

void *socketThread(void *arg){
    char message[MAX_MSG_SIZE], buffer[BUFFER_SIZE];
    // Cast di arg a puntatore-a-int e quindi dereferenziazione del puntatore a arg.
    int newSocket = *((int *) arg);
    // Legge Handshake
    recv(newSocket, message, MAX_MSG_SIZE, 0x0);
    if(strcmp(message, CLIENT_HANDSHAKE) == SUCCESS){
        std::cout << newSocket << "] Got handshake. \t\t(n] -> socket_descriptor)" << std::endl;
        strcpy(message, SERVER_HANDSHAKE);
        if(send(newSocket, message, MAX_MSG_SIZE, 0x0) != ERROR){
            std::cout << newSocket << "] Sent Handshake.\n[+] Waiting for commands..." << std::endl;
            bool stop;
            char *old = new char[MAX_MSG_SIZE];
            int maxCntSame = 2;
            do {
                stop = false;
                if(maxCntSame > 0x0){
                    int recvRes = recv(newSocket, message, MAX_MSG_SIZE, 0x0);
                    if(recvRes != ERROR){
                        if(strcmp(message, old) == SUCCESS){
                            maxCntSame--;
                        } else {
                            strcpy(old, message);
                            if(strcmp(message, COMMAND_STOP) == SUCCESS){
                                std::cout << newSocket << "] Got Stop Command. Closing socket." << std::endl;
                            } else {
                                std::cout << newSocket << "] Got Command: " << message << std::endl;
                                stop = false;
                            }   
                        }
                    }
                }
            } while(!stop);
            std::cout << newSocket << "] Closing socket..." << std::endl;
        } else {
            std::cout << newSocket << "] Error send Handshake." << std::endl;
        }
    } else {
        std::cout << "[-] Wrong Handshake for Socket: " << newSocket << std::endl;
    }
    close(newSocket);
    pthread_exit(NULL);
}

