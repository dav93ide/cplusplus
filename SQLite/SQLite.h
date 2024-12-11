#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "sqlite3.h"

class SQLite {
    private:
        sqlite3 *mDb;
        const char *mDbPath;
        
        char *mErrMsg;

    public:sqlite3_stmt *mStmt;
        SQLite(const char *path);
        ~SQLite();
        sqlite3 *getDb();
        sqlite3_stmt *getStmt();
        char *getErrMsg();

        const char *getSqliteErrMsg();

        int init();
        void free();
        int exec(char *sql);
        int exec(char *sql, int callback(void *NotUsed, int argc, char **argv, char **azColName));
        int getLastInsertRowId();
        int prepareV2(char *sql);
        void bindInt(int index, int value);             // index = indice parametro SQL         value = valore parametro
        int bindParameterIndex(const char *param);
        int step();
        const unsigned char *getColumnText(int index);

        void close();

};