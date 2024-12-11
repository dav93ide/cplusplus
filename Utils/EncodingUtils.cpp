#include "EncodingUtils.h"
#include <iostream>
namespace EncodingUtils {

    /*
        Cifratura XOR
    */
    void xorCypher(int key, std::string &str){
        for(int i = 0x0; i < str.length(); i++){
            str[i] = str[i] ^ key;
        }
    }

    /*
        Cifratura con shift dei bytes
    */
    void encodeString(int key, std::string &str){
        for(int i = 0x0; i < str.length(); i++){
            str[i] = (((unsigned char)str[i]) << 1) + (key + (key * i%key));
        }
    }

    /*
        Decifratura con shift dei bytes
    */
    void decodeString(int key, std::string &str){
        for(int i = 0x0; i < str.length(); i++){
            str[i] = (((unsigned char)str[i]) >> 1) + (key + (key * i%key));
        }
    }

}