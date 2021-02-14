#include "Directory.h"

Directory::Directory(int bucketSize){
    this->globalDepth = 0;




}
int Directory::splitBucket(std::string pos){
    /* works for any bucketSize greater than 1
     */
    Bucket *p_oldBucket = (this->buckets.at(pos)); // copies bucket to oldBucket;
    Bucket *p_newBucket = new Bucket(this->getBucketSize());
    for (auto pairr : p_oldBucket->map) {
        auto pseudoKey = pairr.first; // autos usados para facilitar quando for reimplementado usand outro tipo de pseudoKey (no momento string)
        auto value = pairr.second;
        auto nBits = this->getNfirstBits(pseudoKey);
        if(nBits == pos){
            p_newBucket->insert(value, pseudoKey);
        }
    }
    changeBucketLink(pos, p_newBucket);
    return 0;
}
int Directory::getBucketSize(){
    return this->bucketSize;
}
int Directory::changeBucketLink(std::string pos, Bucket* p_newBucket){
    this->buckets.at(pos) = p_newBucket;
    return 0;
}

std::string Directory::getNfirstBits(std::string pseudoKey){
    return pseudoKey.substr(0, this->globalDepth);

}
int Directory::insert(std::string key, std::string pseudoKey){
    std::string pos = this->getNfirstBits(pseudoKey); // just the "important" part of the pseudoKey, e.g.: if globalDepth==2: 101011-> 10, 00101010-> 00
    Bucket* bucket = this->buckets.at(pos); // for clarity

    if (!bucket->isFull()) {
      // if bucket not full
        bucket->insert(key, pseudoKey);
    }
    else if(bucket->getDepth() < this->globalDepth){
        this->splitBucket(pos);
        this->insert(key, pseudoKey);
    }
    return 0;
}
