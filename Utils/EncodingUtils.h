#include <string>
#include <string.h>

namespace EncodingUtils {

    void xorCypher(int key, std::string &str);

    void encodeString(int key, std::string &str);

    void decodeString(int key, std::string &str);

}