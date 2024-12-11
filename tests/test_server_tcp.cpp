/*
    # Compilation:
        g++ test_server_tcp.cpp -o test_server_tcp.out ../ServerTCP/ServerTCP.cpp -pthread

    # Compilation with _DEBUG:
        g++ test_server_tcp.cpp -o test_server_tcp.out ../ServerTCP/ServerTCP.cpp -pthread -D_DEBUG
*/
#include "../ServerTCP/ServerTCP.h"

#define HOST "127.0.0.1"
#define PORT 6666

int main(){
    ServerTCP server = ServerTCP(strdup(HOST), PORT);
#ifdef _DEBUG
    std::cout << "_DEBUG defined" << std::endl;
#else
    std::cout << "_DEBUG undefined" << std::endl;
#endif
    server.start();
}