/*
    Esempio di invocazione di una funzione mediante un puntatore-a-funzione.
*/

#include <iostream>
#include <limits>

int f_a(int);
int f_b(int);

int fun(int, int (*f) (int));

int main(){
    using namespace std;
    int val = 0x0;

    while(true){
        try{
            cout << "[?] Insert int value: ";
            cin >> val;
            if(val == 0x0){
                throw exception();
            } else {
                break;
            }
        } catch(...){
            cerr << "[!] Wrong value!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    cout << "[+] Calling function \'fun\', using a pointer to function, with value:" << val << endl << endl;

    int (*mFun) (int, int (*f) (int)) = fun;
    cout << "[+] fun stored at address: " << &mFun << endl;

    cout << "[+] res fun(val, f_a): " << (*mFun) (val, f_a) << endl << "[+] res fun(val, f_b): " << (*mFun) (val, f_b) << endl;

    return 0x0;
}

int f_a(int i){
    return i*0x2;
}

int f_b(int i){
    return i*0xA;
}

int fun(int val, int (*f) (int)){
    return (*f) (val);
}