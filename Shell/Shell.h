#include <iostream>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

#define BUFFER_LENGTH   128

namespace Shell {
    std::string exec_command(const char *cmd);
}