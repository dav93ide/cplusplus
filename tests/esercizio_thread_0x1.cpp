/*
    Compilation:
        g++ esercizio_thread_0x1.cpp -lpthread
*/
#include <iostream>
#include <thread>

typedef void *HANDLE;

class thread_obj {
    public:
        void operator()(int x){
            for(int i = 0x0; i < x; i++){
                std::cout << "i = " << i << std::endl;
            }
        }
};

int main(){

    std::thread thr(thread_obj(), 0x3);
    HANDLE test = &thr;

    /*  Utilizzando un puntatore.
    std::thread *p_thr = reinterpret_cast<std::thread*>(test);
    p_thr->join();*/

    // Utilizzando un riferimento
    std::thread& p_thr = *reinterpret_cast<std::thread*>(test);
    p_thr.join();

    /*  Utilizzando std::move -> muove l'oggetto castato dentro la variabile. 
        In questo modo pero` l'oggetto "test" non e` piu` utilizzabile poiche`e`stato rimosso.
        
    std::thread new_thr = std::move(*reinterpret_cast<std::thread*>(test));
    new_thr.join();*/

    return 0x0;
}