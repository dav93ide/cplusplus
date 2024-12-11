/**
 *  COMPILAZIONE:
 *      g++ main.cpp sqlite3.o -I/sqlite3.h SQLite.cpp -ldl -pthread
 * */

#include "SQLite.h"
#include <iostream>

#define DB_PATH "/home/z3r0/Desktop/Doing/Linux/SQLite/test_db"
#pragma once;

using namespace std;

int callback(void *NotUsed, int argc, char **argv, char **azColName);

int main(){

    SQLite slite = SQLite(DB_PATH);
    if(slite.init() != SQLITE_OK){
        std::cout << "Error: " << slite.getSqliteErrMsg();
        slite.close();
    }

    char *sql = "DROP TABLE IF EXISTS Cars;" 
                "CREATE TABLE Cars(Id INT, Name TEXT, Price INT);" 
                "INSERT INTO Cars VALUES(1, 'Audi', 52642);" 
                "INSERT INTO Cars VALUES(2, 'Mercedes', 57127);" 
                "INSERT INTO Cars VALUES(3, 'Skoda', 9000);" 
                "INSERT INTO Cars VALUES(4, 'Volvo', 29000);" 
                "INSERT INTO Cars VALUES(5, 'Bentley', 350000);" 
                "INSERT INTO Cars VALUES(6, 'Citroen', 21000);" 
                "INSERT INTO Cars VALUES(7, 'Hummer', 41400);" 
                "INSERT INTO Cars VALUES(8, 'Volkswagen', 21600);";
    /*if(slite.exec(sql) != SQLITE_OK){
        std::cout << "Error: " << slite.getErrMsg();
        slite.close();
    }*/

    std::cout << "Last ID: " << slite.getLastInsertRowId() << " ID" << std::endl << std::endl;


    char *sql2 = "SELECT * FROM Cars";

    /*if(slite.exec(sql2, callback) != SQLITE_OK){
        std::cout << "Error: " << slite.getErrMsg();
        slite.close();
    }*/


    char *sql3 = "SELECT Id, Name FROM Cars WHERE Id = ?";
    if(slite.prepareV2(sql3) == SQLITE_OK){
        slite.bindInt(1, 3);
    } else {
        std::cout << "Error: " << slite.getSqliteErrMsg();
    }
    
    if(slite.step() == SQLITE_ROW){
        std::cout << "Result = "<< std::endl << slite.getColumnText(0x0) << std::endl << slite.getColumnText(0x1) << std::endl;
    }







    char *sql4 = "SELECT Id, Name FROM Cars WHERE Id = @id";
    if(slite.prepareV2(sql4) == SQLITE_OK){
        int index = slite.bindParameterIndex("@id");
        int value = 4;
        slite.bindInt(index, value);
    }


    if(slite.step() == SQLITE_ROW){
        std::cout << "Result = "<< std::endl << slite.getColumnText(0x0) << std::endl << slite.getColumnText(0x1) << std::endl;
    }








    slite.close();
    return 0x0;
}

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    
    NotUsed = 0;
    
    for (int i = 0; i < argc; i++) {

        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    
    printf("\n");
    
    return 0;
}