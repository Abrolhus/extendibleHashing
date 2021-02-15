#include "Directory.h"

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
int Directory::splitBucket(std::string pos){
    /* works for any bucketSize greater than 1
     * split bucket in 2 increasing both old and new bucket depth
     */
    std::cout << "antes de antes do for" << std::endl;
    Bucket *p_oldBucket = this->buckets.at(pos); // copies bucket to oldBucket;
    Bucket *p_newBucket = new Bucket(this->getBucketSize(), p_oldBucket->getDepth());
    std::cout << "antes do for" << std::endl;
    std::vector<std::string> pseudoKeysToRemove; // cant remove easilly during for loop;
    for (auto pairr : p_oldBucket->map) {
        auto pseudoKey = pairr.first; // autos usados para facilitar quando for reimplementado usand outro tipo de pseudoKey (no momento string)
        auto value = pairr.second;
        auto nBits = this->getNfirstBits(pseudoKey);
        if(nBits == pos){
            p_newBucket->insert(value, pseudoKey);
            pseudoKeysToRemove.push_back(pseudoKey);
            // p_oldBucket->remove(pseudoKey);
        }
    }
    for(auto pseudoKey : pseudoKeysToRemove){
        p_oldBucket->remove(pseudoKey);
    }
    std::cout << "passou do for" << std::endl;
    p_oldBucket->increaseDepth();
    p_newBucket->increaseDepth();
    changeBucketLink(pos, p_newBucket);
    return 0;
}

void Directory::increaseGlobalDepth(){
    this->globalDepth++;
}
void Directory::duplicateDirectory(std::string pos){
    /* splits each bucket in directory
     */
    this->printDirectory();
    std::cout << "increaseDepth" << std::endl;
    this->increaseGlobalDepth();
    auto copyBuckets = this->buckets;
    for(auto pairr : copyBuckets){ // pairr ao inves de pair soh pra nao confundir a sintaxe da IDE
        // std::cout << "0";
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
        // std::cout << "1";
        this->buckets.insert({oldKey + "0", p_oldBucket}); // inserts both old and new bucket to the new corresponding positions
        this->buckets.insert({oldKey + "1", p_oldBucket}); // TODO: aumentar grau de abstracao
        std::cout << " remooving" << std::endl;
        this->removeBucket(oldKey);
        std::cout << "removed" << std::endl;
        // this->moveBucket(pos, pos + "0"); // moves bucket from e.g 1111 to 11110
    }
    std::cout << "Done duplicating" << std::endl;
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
    std::cout << "nFirstBits:" << pseudoKey.substr(0, this->globalDepth + 0) << std::endl;
    return pseudoKey.substr(0, this->globalDepth + 0);

}
std::string Directory::getNfirstBits(std::string pseudoKey, int add){
    return pseudoKey.substr(0, this->globalDepth + 0 + add);

}
int Directory::insert(std::string key, std::string pseudoKey){
    std::string pos = this->getNfirstBits(pseudoKey); // just the "important" part of the pseudoKey, e.g.: if globalDepth==2: 101011-> 10, 00101010-> 00
    Bucket* bucket = this->buckets.at(pos); // for clarity

    if (!bucket->isFull()) {
      // if bucket not full
        bucket->insert(key, pseudoKey);
    }
    else if(bucket->getDepth() < this->globalDepth){ // if bucket is full but depth is lower than globalDepth
        std::cout << " split!!!!" << std::endl;
        this->splitBucket(pos);
        this->insert(key, pseudoKey);
    }
    else {
        std::cout << "duplicateDirectory!" << std::endl;
        this->duplicateDirectory(pos);
        std::cout << "nfb: " << this->getNfirstBits(pseudoKey) << std::endl;
        this->splitBucket(this->getNfirstBits(pseudoKey)); // duplicateDirectory increases globalDepth, so getNfirstBits is called again
        this->insert(key, pseudoKey);
    }

    return 0;
}
void Directory::addBucket(std::string pos){
    this->buckets.insert({pos, new Bucket(this->getBucketSize(), 1)}); // std::map insert
}
void Directory::printDirectory(){
  Bucket *p_OldBucket = nullptr;
  for (auto pairr : this->buckets) {
    if (pairr.second == p_OldBucket){
    std::cout << "\t" << pairr.first << "(" << pairr.second->getDepth() << ") " << std::endl;
        continue;
    }
    std::cout << pairr.first << "(" << pairr.second->getDepth() << ") " << " ---> ";
    for (auto pairr2 : pairr.second->map) {
      std::cout << pairr2.first << ":" << pairr2.second << ", ";
    }
    if(pairr.second->map.empty()){
        std::cout << "empty! ";
    }
    std::cout << std::endl;
    p_OldBucket = pairr.second;
    }

}
