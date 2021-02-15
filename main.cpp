#include <iostream>
#include "Directory.h"
#include "Bucket.h"
#include <vector>
using namespace std;
string intToBinaryString( unsigned long n ) {

      /*
      * Create char array of size = 32+1
      * (1 for null terminated string) =33 to
      * accommodate 32 byte chars as unsigned long range
      *  0 to 4,294,967,295 can be accommodated int to it
      *
      * Size of unsigned long is 4 bytes, hence for
      * 32 byte char array, we need to multiply by 8
      */

      char     bArray[ (sizeof( unsigned long ) * 8) + 1 ];

      //index = 32 to fetch each 32 slots
      unsigned index  = sizeof( unsigned long ) * 8;

      char temp =0;
      bArray[ index ] = '\0';

      do{

            //bArary[ --index ] = '0' + (n & 1);

            //Breaking above line to understand better.
            temp = (n & 1); // Finding 0 or 1 in LSB
            // Adding ASCII 0 to convert Binary to ASCII
            temp = temp + '0';

            // Copying final ASCII equivalent BIT value (0 or 1)
            bArray[ --index ] = temp;

            //In while expression :n >>= 1 or equivalent to it is n =n>>1
            //can be used. Shifting the Value to RIGHT by one
            //to check the NEXT LSB bit.
            //Exits when n becomes ZERO.

      }while (n >>= 1);

      //bArray contains base address. So, jump to
      //base address + current index to fetch
      //the binary representation.


      return string( bArray + index );
}
std::string hashFunction(std::string str){
    //cout << str << ": " << intToBinaryString(str[0]) << endl;
    return {intToBinaryString(str[0])}; // quickFix from coc.nvim. Dont know what this actually does
 }
int main(int argc, const char** argv){
    Directory* dir = new Directory(3);
    vector<string> nomes {"Paula", "Joao", "Carlos", "Jefferson", "Rafael", "Marcos", "Janette"};
    cout << string("Paula").substr(0, 0) << "jjjjjjj" << endl;
    for(auto nome : nomes){
        dir->insert(nome, hashFunction(nome));
    }
    dir->printDirectory();

    return 0;
}
