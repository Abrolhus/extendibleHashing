#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "Directory.h"
#include "Bucket.h"
#include <vector>
#include <strings.h>
#include <bitset>
using namespace std;
// using std namespace only on main function.
std::string exampleHashFunction(std::string str){
    //cout << str << ": " << intToBinaryString(str[0]) << endl;
      std::string bin = "";
      for(auto c : str){
            bin += '0' + (c%2); // char % 2 = 0 or 1; '0' + 1 = '1'
      }
    // return {intToBinaryString(str[0])}; // quickFix from coc.nvim. Dont know what this actually does
      return bin;
 }
std::vector<std::string> randomPseudoKeysGenerator(int n, int length){
      string intToBinaryString( unsigned long n );
      std::vector<std::string> keys;
      std::vector<std::string> allPossibleStrings;
      int size = pow(2, length);
      if(length > 15){
            std::cout << "too large" << std::endl;
            return keys;
      }
      else if(size < n){
            std::cout << "not enough length" << std::endl;
            return keys;
      }
      std::cout << size;
      int num;
      std::string str = ""; // string conversion
      for(int i = 0; i < size; i++){
            // std::string bits =  std::bitset< 10 >(i).to_string();
            std::string bits = intToBinaryString(i);
            // std::cout << bits.length();
            std::string str0 = "";
            for(int j = 0; j < length - bits.length(); j++){
                  str0 += '0';
            }
            str = str0 + bits;
            allPossibleStrings.push_back(str);
      }
      std::cout << "allPossibleStrings" << std::endl;
      // for(auto c : allPossibleStrings){
            // std::cout << " " + c;
      // }
      int index;
      std::string aux;
      for(int i = 0; i < n; i++){
            index = rand()%(size - i) + i;
            aux = allPossibleStrings[i];
            allPossibleStrings[i] = allPossibleStrings[index];
            keys.push_back(allPossibleStrings[i]);
            allPossibleStrings[index] = aux;
      }
      // for(auto str : keys){
            // std::cout << str << std::endl;
      // }
      return keys;
}
std::string hashFunction(std::string str){
      return str;
}
int main(int argc, const char** argv){

      string intToBinaryString( unsigned long n );
      srand(time(nullptr));
      int bucketSize;
      int pseudoKeySize;
      cout << "bucketSize: ";
      cin >> bucketSize;
      cout << "pseudoKeySize: ";
      cin >> pseudoKeySize;

    Directory* dir = new Directory(bucketSize, pseudoKeySize);
    // vector<string> nomes {"Paula", "Joao", "Carlos", "Jefferson", "Rafael", "Marcos", "Janette"};
    vector<string> pseudoKeys = randomPseudoKeysGenerator(100, pseudoKeySize);
      std::string bits =  std::bitset< 8 >(14).to_string();
    // std::string bits = intToBinaryString(153);
    for(auto psdkey : pseudoKeys){
          cout << psdkey << ", ";
    }
    cout << endl;
    for(auto nome : pseudoKeys){
        dir->insert(nome, nome);
    }
    dir->printDirectory();

    return 0;
}
string intToBinaryString( unsigned long n )
{

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
