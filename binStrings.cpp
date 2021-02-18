#include "binStrings.h"

std::string intToBinString(int num){

    /* https://stackoverflow.com/a/8238746
     * Converts int to binary (string) with 31 bits
     * e.g.: input: 37, output: 000000000...00100101
     * max num = 2^31 -1;
     */
    std::string binary("");
    int mask = 1;
    for(int i = 0; i < 31; i++){
    if ((mask & num) >= 1)
        binary = "1"+binary;
    else
        binary = "0"+binary;
    mask<<=1;
    }
    return binary;
}
std::string intToBinString(int num, int length){
    /* https://stackoverflow.com/a/8238746
     * converts int to binary, but with given length instead of 31 bits
     * e.g.: input: (37, 8), output: 00100101
     *       input: (6, 8),  output: 00000110
     */
    std::string binary("");
    int mask = 1;
    for(int i = 0; i < length; i++){
    if ((mask & num) >= 1)
        binary = "1"+binary;
    else
        binary = "0"+binary;
    mask<<=1;
    }
    return binary;
}
std::string intToBinString(int num, int length, std::string prefix){
    /* https://stackoverflow.com/a/8238746
     * converts int to binary, but with given length instead of 31 bits
     * e.g.: input: (37, 8), output: 00100101
     *       input: (6, 8),  output: 00000110
     */
    std::string binary(prefix);
    int mask = 1;
    for(int i = 0; i < length - prefix.length(); i++){
    if ((mask & num) >= 1)
        binary = "1"+binary;
    else
        binary = "0"+binary;
    mask<<=1;
    }
    return binary;
}
