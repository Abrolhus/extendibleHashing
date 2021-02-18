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
std::string hashFunction(std::string str){
      return str;
}
int main(int argc, const char** argv){

    void mem_usage(double& vm_usage, double& resident_set);
    string intToBinaryString( unsigned long n );
    srand(time(nullptr));
    int bucketSize;
    int pseudoKeySize;
    double vm, rss;
    cout << "bucketSize: ";
    cin >> bucketSize;
    cout << "pseudoKeySize: ";
    cin >> pseudoKeySize;
    cout << intToBinString(37, 8) << endl;
    mem_usage(vm, rss);
    cout << "Virtual Memory: " << vm << "\nResident set size: " << rss << endl;

    Directory dir = Directory(bucketSize, pseudoKeySize);
    // vector<string> nomes {"Paula", "Joao", "Carlos", "Jefferson", "Rafael", "Marcos", "Janette"};
    vector<string>* pseudoKeys = new vector<std::string>;
    *pseudoKeys = randomPseudoKeysGenerator(100, pseudoKeySize);
    // std::string bits = intToBinaryString(153);
    for(auto psdkey : *pseudoKeys){
          cout << psdkey << ", ";
    }
    cout << endl;
    for(auto nome : *pseudoKeys){
        dir.insert(nome, nome);
    }
    dir.printDirectory();
    delete pseudoKeys;
    mem_usage(vm, rss);
    cout << "Virtual Memory: " << vm << "\nResident set size: " << rss << endl;
    size_t memDir = sizeof dir;
    cout

    int aux;
    cout << "Paused ";
    cin >> aux;

    return 0;
}
void mem_usage(double& vm_usage, double& resident_set) {
   vm_usage = 0.0;
   resident_set = 0.0;
   ifstream stat_stream("/proc/self/stat",ios_base::in); //get info from proc
   //create some variables to get info
   string pid, comm, state, ppid, pgrp, session, tty_nr;
   string tpgid, flags, minflt, cminflt, majflt, cmajflt;
   string utime, stime, cutime, cstime, priority, nice;
   string O, itrealvalue, starttime;
   unsigned long vsize;
   long rss;
   stat_stream >> pid >> comm >> state >> ppid >> pgrp >> session >> tty_nr
   >> tpgid >> flags >> minflt >> cminflt >> majflt >> cmajflt
   >> utime >> stime >> cutime >> cstime >> priority >> nice
   >> O >> itrealvalue >> starttime >> vsize >> rss; // don't care about the rest
   stat_stream.close();
   long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // for x86-64 is configured to use 2MB pages
   vm_usage = vsize / 1024.0;
   resident_set = rss * page_size_kb;
}
