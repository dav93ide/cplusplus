/*  
 *  #===========================#
 *  | Exercise 0x3 - Structures |
 *  #===========================#  
 *
 *  Compilation:
 *      g++ structures.cpp -o ex_0x3.out
 */

#include "ex_0x1_header.h"

int main(int argc, char *argv){

    // Classic C/C++ struct initialization
    person person0x1 = {
        "name0x1",
        "surname0x1",
        666
    };
    std::cout << "Name person0x1: " << person0x1.name << std::endl;             // Accessing structure object property "."
    std::cout << "Surname person0x1: " << person0x1.surname << std::endl;       // using the Member Selection via Object Name Operator
    std::cout << "Age person0x1: " << person0x1.age << std::endl << std::endl << std::endl;

    // C++11 list initalization
    person person0x2 = {"name0x2", "surname0x2", 333};
    std::cout << "Name person0x2: " << person0x2.name << std::endl;
    std::cout << "Surname person0x2: " << person0x2.surname << std::endl;
    std::cout << "Age person0x2: " << person0x2.age << std::endl << std::endl << std::endl;

    // C++11 list initalization with properties specification
    person person0x3 = {.name = "name0x3", .surname = "surname0x3", .age = 333};
    std::cout << "Name person0x3: " << person0x3.name << std::endl;
    std::cout << "Surname person0x3: " << person0x3.surname << std::endl;
    std::cout << "Age person0x3: " << person0x3.age << std::endl << std::endl << std::endl;

    // Pointer to person, initialized using 'person0x2' address
    person *p = &person0x2;        
    std::cout << "p pointed address: " << p << std::endl;

    // Get struct value from pointer
    std::cout << "p->name: " << p->name << std::endl << std::endl;

    // Get the first value in 'p->name' char array by dereferencing the pointer.
    // Pointer to array if used by name always points to the first element of the array.
    std::cout << "p->name: " << *p->name << std::endl << std::endl;
    
    // Get the second value in 'p->name' char array by dereferencing a offset to the pointer.
    std::cout << "p->name: " << *(p->name + sizeof(char)) << std::endl << std::endl;

}