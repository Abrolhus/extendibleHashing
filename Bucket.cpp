#include "Bucket.h"

int Bucket::getCurrentSize(){
    return this->map.size();
}
bool Bucket::isFull(){
    if(this->getCurrentSize() == this->size)
        return false;
    return true;
}
int Bucket::getDepth(){
    return this->depth;
}
int Bucket::insert(std::string key, std::string pseudoKey){
    if(this->getCurrentSize() == this->size){
        return -1;
    }
    if(this->map.find(pseudoKey){
            return -2;
    }
    this->keys.at(pseudoKey) = key;


    return 0;
}
