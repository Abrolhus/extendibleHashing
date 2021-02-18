#include <iostream>
#include <fstream>
#include <unistd.h>
#include <ios>
#include "binStrings.h"
#include <stdlib.h>
#include <math.h>
#include "Directory.h"
#include "Bucket.h"
#include <vector>
#include <strings.h>
#include <bitset>
using namespace std;
// using std namespace only on main function.
int main(int argc, const char** argv){

    std::vector<std::string> randomPseudoKeysGenerator(int n, int length);
    std::vector<std::string> randomPseudoKeysGenerator(int n, int length, std::string prefix);
    std::vector<std::string> randomPseudoKeysGenerator(int n, int length);
    std::string exampleHashFunction(std::string str);
    srand(time(nullptr));
    int bucketSize;
    int pseudoKeySize;
    cout << "bucketSize: ";
    cin >> bucketSize;
    cout << "pseudoKeySize: ";
    cin >> pseudoKeySize;
    int numPseudoKeys = 500;

    Directory dir = Directory(bucketSize, pseudoKeySize);
    vector<string>* pseudoKeys = new vector<std::string>;
    *pseudoKeys = randomPseudoKeysGenerator(numPseudoKeys, pseudoKeySize);

    for(auto nome : *pseudoKeys){
        dir.insert(nome, nome); // pseudoKey: nome (string), valor a ser armazenado: nome (string)
    }
    dir.printDirectory();
    cout << "Fator de Carga: " << dir.getFatorDeCarga() << endl;
    cout << "Espaco Ocupado: " << numPseudoKeys << "strings (Pseudo-chaves)"<< endl;
    delete pseudoKeys;

    Directory dir2 = Directory(bucketSize, pseudoKeySize);
    auto pseudoKeys2 = randomPseudoKeysGenerator(numPseudoKeys, pseudoKeySize, "110");
    for(auto nome : pseudoKeys2){
        dir2.insert(nome, nome); // pseudoKey: nome (string), valor a ser armazenado: nome (string)
    }
    dir2.printDirectory();
    cout << "Fator de Carga: " << dir2.getFatorDeCarga() << endl;
    cout << "Espaco Ocupado: " << numPseudoKeys << "strings (Pseudo-chaves)"<< endl;

    return 0;
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
      int num;
      std::string str = ""; // string conversion
      for(int i = 0; i < size; i++){
            std::string bits = intToBinString(i, length);
            allPossibleStrings.push_back(bits);
      }
      int index;
      std::string aux;
      for(int i = 0; i < n; i++){
            index = rand()%(size - i) + i;
            aux = allPossibleStrings[i];
            allPossibleStrings[i] = allPossibleStrings[index];
            keys.push_back(allPossibleStrings[i]);
            allPossibleStrings[index] = aux;
      }
      return keys;
}
std::vector<std::string> randomPseudoKeysGenerator(int n, int length, std::string prefix){
      std::vector<std::string> keys;
      std::vector<std::string> allPossibleStrings;
      int size = pow(2, length - prefix.length()+1);
      if(length > 15){
            std::cout << "too large" << std::endl;
            return keys;
      }
      else if(size < n){
            std::cout << "not enough length" << std::endl;
            return keys;
      }
      int num;
      std::string str = ""; // string conversion
      for(int i = 0; i < size; i++){
            std::string bits = intToBinString(i, length - prefix.length());
            allPossibleStrings.push_back(prefix + bits);
      }
      int index;
      std::string aux;
      for(int i = 0; i < n; i++){
            index = rand()%(size - i) + i;
            aux = allPossibleStrings[i];
            allPossibleStrings[i] = allPossibleStrings[index];
            keys.push_back(allPossibleStrings[i]);
            allPossibleStrings[index] = aux;
      }
      return keys;
}
std::string exampleHashFunction(std::string str){
    //cout << str << ": " << intToBinaryString(str[0]) << endl;
      std::string bin = "";
      for(auto c : str){
            bin += '0' + (c%2); // char % 2 = 0 or 1; '0' + 1 = '1'
      }
    // return {intToBinaryString(str[0])}; // quickFix from coc.nvim. Dont know what this actually does
      return bin;
 }
std::string hashFunction(std::string str){
      return str;
}
