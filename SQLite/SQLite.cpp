#include "SQLite.h"

SQLite::SQLite(const char *path){
    mDbPath = path;
}

SQLite::~SQLite(){

}

sqlite3 *SQLite::getDb(){
    return mDb;
}

sqlite3_stmt *SQLite::getStmt(){
    return mStmt;
}

char *SQLite::getErrMsg(){
    return mErrMsg;
}

const char *SQLite::getSqliteErrMsg(){
    return sqlite3_errmsg(mDb);
}

int SQLite::init(){
    return sqlite3_open(mDbPath, &mDb);
}

void SQLite::free(){
    sqlite3_free(mErrMsg);
}

int SQLite::exec(char *sql){
    return sqlite3_exec(mDb, sql, 0x0, 0x0, &mErrMsg);
}

int SQLite::exec(char *sql, int callback(void *NotUsed, int argc, char **argv, char **azColName)){
    return sqlite3_exec(mDb, sql, callback, 0x0, &mErrMsg);
}

int SQLite::getLastInsertRowId(){
    return sqlite3_last_insert_rowid(mDb);
}

int SQLite::prepareV2(char *sql){
    return sqlite3_prepare_v2(mDb, sql, -0x1, &mStmt, 0x0);
}

void SQLite::bindInt(int index, int value){
    sqlite3_bind_int(mStmt, index, value);
}

int SQLite::bindParameterIndex(const char *param){
    return sqlite3_bind_parameter_index(mStmt, param);
}

int SQLite::step(){
    return sqlite3_step(mStmt);
}

const unsigned char *SQLite::getColumnText(int index){
    return sqlite3_column_text(mStmt, index);
}

void SQLite::close(){
    sqlite3_finalize(mStmt);
    sqlite3_close(mDb);
}