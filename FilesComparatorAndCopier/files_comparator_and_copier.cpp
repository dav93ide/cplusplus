/*
    #############################
    # Files Comparator & Copier #
    ######################################################################################################################
    # Compara i files tra il percorso 1 e il percorso 2 mostrando le differenze o copiandoli dal percorso 1 al percorso 2.
    #
    # Compilation: g++ files_comparator.cpp FilesComparator.cpp -o files_comparator.out
    ######################################################################################################################
*/
#include <string>
#include <pwd.h>
#include <vector>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include "FilesComparatorAndCopier.h"
#include <iostream>

int main(int argc, char **argv){
    std::cout <<    "##########################################\n" <<
                    "#       Files Comparator & Copier        #\n" <<
                    "##########################################\n" <<
                    "#\n" << 
                    "# Usage: files_comparator_and_copier.out path1 path2 modality levelOfDeep\n" <<
                    "#\n" << 
                    "# Modality: 1] files & dirs 2] only dirs 3] only files 4] copy files\n" <<
                    "#\n" << 
                    "# levelOfDeep: max level of deep to print files" << 
                    "#\n" << 
                    "##########################################\n\n\n";

    std::string p1, p2;
    int modality, levelOfDeep;
    if(argc == 0x5){
        p1 = argv[0x1];
        p2 = argv[0x2];
        modality = argv[0x3][0x0] - 48;
        levelOfDeep = atoi(argv[0x4]);
    } else {
        std::cout << "[?] Insert Path One: ";
        std::cin >> p1;
        std::cout << "\n[?] Insert Path Two: ";
        std::cin >> p2;
        std::cout << "\n[?] Insert Modality: ";
        std::cin >> modality;
        std::cout << "\n[?] Insert levelOfDeep: ";
        std::cin >> levelOfDeep;
        std::cout << "\n\n\n";
    }
    std::cout << "[+] Path One: " << p1 << "\n[+] Path Two: " << p2 << std::endl << std::endl;

    Dir *main = FilesComparator::compare_files_of_paths(p1, p2);

    std::cout <<    "#########################################\n" <<
                    "# Files Differences Between The 2 Paths #\n" <<
                    "#########################################\n\n";

    if(modality == MOD_COPY_FILES){
        FilesComparator::copy_files(*main, p2);
    } else { 
        FilesComparator::print_formatted_results(*main, 0x0, modality, levelOfDeep, 0x0);
    }

    std::cout <<    "\n#######################################\n";

    return 0x1;
}
