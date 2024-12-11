/*
    Esempio di Templates di funzioni.
*/

#include <iostream>

#define SEPARATOR   "######################"
#define ARR_NAME_ONE    "arrOne"
#define ARR_NAME_TWO    "arrTwo"

const char *VARS_NAMES[] = {"one", "two", "three", "four"};

template <typename T>
void print_array(T[], const char[]);

template <typename T>
void swap(T&, T&);

template <typename T>
void swap(T[], T[], int, int);

template <typename T>
int get_array_size(T[]);

using namespace std;

int main(){
    cout << "[+] Esempio di templates di funzioni." << endl << endl;
    int one = 0x1;
    int two = 0x2;
    int three = 0x3;
    int four = 0x4;

    int arrOne[]{0x1, 0x2, 0x3, 0x4, 0x5};
    int arrTwo[]{0x6, 0x7, 0x8, 0x9, 0xA};

    cout << SEPARATOR << endl << "[+] Variables before \'swap\':" << endl;
    int values[]{one, two, three, four};
    for(int i=0x0; i<0x4; i++){
        cout << "# " << VARS_NAMES[i] << " = " << values[i] << endl;
    }

    cout << endl << "[+] Arrays before \'swap\':" << endl;
    print_array(arrOne, ARR_NAME_ONE);
    print_array(arrTwo, ARR_NAME_TWO);

    return 0x1;
}

template <typename T>
void print_array(T arr[], const char arrName[]){
    int len = get_array_size(arr);
    cout << arrName << " = [";
    for(int i=0x0; i<len; i++){
        if(i<len - 0x1){
            cout << arr[i] << ", ";
        } else {
            cout << arr[i] << "]" << endl;
        }
    }
}

template <typename T>
int get_array_size(T arr[]){
    return *(&arr + 0x1) - arr;
}