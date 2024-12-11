#include "Shell.h"

std::string Shell::exec_command(const char *cmd){
    std::array<char, BUFFER_LENGTH> buffer;
    std::string result;

    /*
        unique_ptr  ->  Puntatore "intelligente" che possiede e gestisce un altro oggetto attraverso un puntatore e che si disfa dell'oggetto
                            quando l'unique_ptr va fuori dallo scope. L'oggetto viene disfato nel caso in cui:
                                - viene distrutto l'oggetto gestito dall'unique_ptr
                                - oppure l'oggetto gestito dall'unique_ptr viene assegnato ad un altro puntatore attraverso l'operatore= oppure "reset()".

        FILE        ->  Tipo di oggetto che identifica uno stream e contiene le informazioni necessarie per controllarlo, incluso il puntatore al suo buffer,
                            il suo indicatore della posizione e tutti i suoi indicatori di stato.

        decltype    ->  Ispeziona il tipo dichiarato di un'entita`o il tipo e la categoria di valore di un'espressione.

        pipe()      ->  Utilizzato per passare informazioni da un processo ad un altro. E` uni-direzionale.
                        Concettualmente una "pipe" e`una connessione tra due processi, ad esempio lo standard output di un processo diventa lo standard input
                            dell'altro processo.

        popen()     ->  Apre un processo creando una pipe, forkando ed invocando la Shell. 
                            Primo argomento e`il comando in una stringa null-terminata, il secondo argomento e` 'w' o 'r' rispettivamente per "sola-scrittura" o "sola-lettura".
    
    */
    // In pratica apre un processo assegnando la pipe ritornata ad un "unique_ptr" (cui tipo e`FILE ossia un oggetto stream)
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if(!pipe){
        //throw std::runtime_error("popen() failed!");
        return "popen() failed!";
    }
    // Finche`leggo dati dalla pipe continuo a scriverli in "result".
    while(fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr){
        result += buffer.data();
    }
    return result;
}