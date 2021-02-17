#include "Directory.h"
#include <bitset>
#include <math.h>
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

Directory::Directory(int bucketSize){
    /* inicializa o diretory com 1 de depth e com 2 buckets;
     */
    this->bucketSize = bucketSize;
    this->globalDepth = 1;
    // this->buckets.insert({"0", new Bucket(this->getBucketSize())}); // std::map insert
    // this->buckets.insert({"1", new Bucket(this->getBucketSize())});
    this->addBucket("0");
    this->addBucket("1");
}
Directory::Directory(int bucketSize, int pseudoKeySize){
    /* inicializa o diretory com 1 de depth e com 2 buckets;
     */
    this->bucketSize = bucketSize;
    this->globalDepth = 1;
    this->pseudoKeySize = pseudoKeySize;
    // this->buckets.insert({"0", new Bucket(this->getBucketSize())}); // std::map insert
    // this->buckets.insert({"1", new Bucket(this->getBucketSize())});
    this->addBucket("0");
    this->addBucket("1");
}
int Directory::splitBucket(std::string pos){
    /* works for any bucketSize greater than 1
     * split bucket in 2 increasing both old and new bucket depth
     */
    // if(this->buckets.find(pos) == buckets.end()){
        // std::cout << "Nao encontrado!" << std::endl;
        // return -1;
    // }
    std::cout << "Spliting at pos: " << pos << std::endl;
    Bucket *p_oldBucket = this->buckets.at(pos); // copies bucket to oldBucket;
    Bucket *p_newBucket = new Bucket(this->getBucketSize(), p_oldBucket->getDepth());
    std::vector<std::string> pseudoKeysToRemove; // cant remove easilly during for loop;
    for (auto pairr : p_oldBucket->map) {
        auto pseudoKey = pairr.first; // autos usados para facilitar quando for reimplementado usand outro tipo de pseudoKey (no momento string)
        auto value = pairr.second;
        // std::string nBits = this->getNfirstBits(pseudoKey, -this->globalDepth +  p_oldBucket->getDepth()+1);
        // std::string pattern = this->getNfirstBits(pos, -this->globalDepth + p_oldBucket->getDepth()) + pos.at(p_oldBucket->getDepth());
        std::string nBits = pseudoKey.substr(0, p_oldBucket->getDepth()+1);
        std::string pattern = pseudoKey.substr(0, p_oldBucket->getDepth()+0) + '0';
        std::cout << "pattern: " << pattern << std::endl;
        if(nBits == pattern){
            p_newBucket->insert(value, pseudoKey);
            pseudoKeysToRemove.push_back(pseudoKey);
            // p_oldBucket->remove(pseudoKey);
        }
    }

    std::cout << "To remove: " << std::endl;
    for(auto pseudoKey : pseudoKeysToRemove){
        std::cout << pseudoKey << ", ";
        p_oldBucket->remove(pseudoKey);
    }
    std::cout << std::endl;
    p_oldBucket->increaseDepth();
    p_newBucket->increaseDepth();
    std::cout << "newBucket: " << std::endl;
    for(auto pairr2 : p_newBucket->map){
        std::cout << pairr2.first << ", ";
    }
    std::cout << std::endl;
    std::cout << "oldBucket: " << std::endl;
    for(auto pairr3 : p_oldBucket->map){
        std::cout << pairr3.first << ", ";
    }
    std::cout << std::endl;
    changeBucketLink(pos, p_newBucket);
    return 0;
}

void Directory::increaseGlobalDepth(){
    this->globalDepth++;
}
void Directory::duplicateDirectory(){
    /* splits each bucket in directory
     */
    this->increaseGlobalDepth();
    auto copyBuckets = this->buckets;
    for(auto pairr : copyBuckets){ // pairr ao inves de pair soh pra nao confundir a sintaxe da IDE
        std::string oldKey = pairr.first;
        Bucket* p_oldBucket = pairr.second;
        // Bucket* p_newBucket = new Bucket(this->getBucketSize());
        // for(auto bucketPairr : p_oldBucket->map){ // again, TODO: mark Bucket::map as private
            // auto pseudoKey = bucketPairr.first; //str
            // auto value = bucketPairr.second;
            // if(getNfirstBits(pseudoKey) == getNfirstBits(pseudoKey, -1) + "1"){ //
                // p_newBucket->insert(value, pseudoKey);
                // p_oldBucket->remove(pseudoKey);
            // }
        // }
        this->buckets.insert({oldKey + '0', p_oldBucket}); // inserts both old and new bucket to the new corresponding positions
        this->buckets.insert({oldKey + '1', p_oldBucket}); // TODO: aumentar grau de abstracao
        this->removeBucket(oldKey);
        std::cout << "duplicating " << oldKey << "-> " << oldKey + '0' << ", " << oldKey + '1' << std::endl;
        // this->moveBucket(pos, pos + "0"); // moves bucket from e.g 1111 to 11110
    }
    this->printDirectory();

}
void Directory::removeBucket(std::string pos){
    this->buckets.erase(pos);
}
int Directory::getBucketSize(){
    return this->bucketSize;
}
int Directory::changeBucketLink(std::string pos, Bucket* p_newBucket){
    this->buckets.at(pos) = p_newBucket;
    return 0;
}

std::string Directory::getNfirstBits(std::string pseudoKey){
    // std::cout << "nFirstBits:" << pseudoKey.substr(0, this->globalDepth + 0) << std::endl;
    return pseudoKey.substr(0, this->globalDepth + 0);

}
std::string Directory::getNfirstBits(std::string pseudoKey, int add){
    return pseudoKey.substr(0, this->globalDepth + 0 + add);

}
int Directory::insert(std::string key, std::string pseudoKey){
    std::cout << "inserindo " << pseudoKey << std::endl;
    std::string pos = this->getNfirstBits(pseudoKey); // just the "important" part of the pseudoKey, e.g.: if globalDepth==2: 101011-> 10, 00101010-> 00
    Bucket* bucket = this->buckets.at(pos); // for clarity

    if (!bucket->isFull()) {
      // if bucket not full
        bucket->insert(key, pseudoKey);
    }
    else{
        if(bucket->getDepth() < this->globalDepth){ // if bucket is full but depth is lower than globalDepth
            std::cout << bucket->getDepth() << " < " << this->globalDepth << std::endl;
            this->splitBucket(pos);
            std::cout << "bucket split" << std::endl;
            this->printDirectory();
            this->insert(key, pseudoKey);
            return 0;
        }
        else {
            this->duplicateDirectory();
            this->splitBucket(this->getNfirstBits(pseudoKey)); // duplicateDirectory increases globalDepth, so getNfirstBits is called again
            std::cout << "bucket split" << std::endl;
            this->printDirectory();
            this->insert(key, pseudoKey);
        }
    }

    return 0;
}
void Directory::addBucket(std::string pos){
    this->buckets.insert({pos, new Bucket(this->getBucketSize(), 1, this->pseudoKeySize)}); // std::map insert
}
void Directory::printDirectory(){
  Bucket *p_OldBucket = nullptr;
  std::cout << "GlobalDepth: " << this->globalDepth << std::endl;
  for (auto pairr : this->buckets) {
    auto prefix = pairr.first.substr(0, pairr.second->getDepth());
    auto rest = pairr.first.substr(pairr.second->getDepth());

    if (pairr.second == p_OldBucket){
    //std::cout << "\t" << pairr.first << "(" << pairr.second->getDepth() << ") " << std::endl;
    std::cout << "    " << CYAN << prefix << RESET << rest << "(" << pairr.second->getDepth() << ") "<< std::endl;
        continue;
    }
    // std::cout << pairr.first << "(" << pairr.second->getDepth() << ") " << " ---> ";
    std::cout << std::endl;
    std::cout << BOLDCYAN << prefix << RESET << rest << "(" << pairr.second->getDepth() << ") " << " ---> ";
    for (auto pairr2 : pairr.second->map) {
      // std::cout << pairr2.first << ":" << pairr2.second << ", ";
        auto pkPrefix = pairr2.first.substr(0, pairr.second->getDepth());
        auto pkRest = pairr2.first.substr(pairr.second->getDepth());
      std::cout << RED << pkPrefix << RESET << pkRest<< ", ";
    }
    if(pairr.second->map.empty()){
        std::cout << "empty! ";
    }
    std::cout << std::endl;
    p_OldBucket = pairr.second;
    }

}
int Directory::getGlobalDepth(){
    return this->globalDepth;
}
void Directory::reorganizePointers(std::string pattern, std::string pos, Bucket* p_OldBucket, Bucket* p_NewBucket){
    /* for instance,
     *  bucket with depth = 2
     *    0100xxx = 0101xxx = 0110xxx = 0111xxx ;
     *    you are willing to redistribute its keys to 2 buckets (itself and a brand new one) with depth = 3;
     *    0100xxx = 0101xxx ;
     *    0110xxx = 0111xxx ;
     */
    int newDepth = p_OldBucket->getDepth() + 1;
    int oldDepth = p_OldBucket->getDepth();
    std::string oldPattern = pos.substr(0, oldDepth) + '1';
    std::string newPattern = pos.substr(0, oldDepth) + '0';
    for(int i = 0; i < pow(2, this->getGlobalDepth() - newDepth); i++){
        std::string binaryString = intToBinaryString(i);
        std::string missingZeros = "";
        for(int j = 0; j < (this->getGlobalDepth() - newDepth) - binaryString.size(); i++){
            missingZeros += '0';
        }
        std::string pos = newPattern + binaryString + missingZeros +
                          std::to_string(binaryString.size());
    }

}
std::string Directory::intToBinaryString( unsigned long n )
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


      return std::string( bArray + index );
}
