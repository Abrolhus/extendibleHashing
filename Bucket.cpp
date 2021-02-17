#include "Bucket.h"

Bucket::Bucket(int size, int depth){
    this->size = size;
    this->depth = depth;
}
Bucket::Bucket(int size, int depth, int pseudoKeySize){
    this->size = size;
    this->depth = depth;
    this->pseudoKeySize = pseudoKeySize;
}
Bucket::Bucket(int size){
    this->size = size;
    this->depth = 1;
}
int Bucket::getCurrentSize(){
    return this->map.size();
}
bool Bucket::isFull(){
    if(this->getCurrentSize() == this->size)
        return true;
    return false;
}
int Bucket::getDepth(){
    return this->depth;
}
void Bucket::increaseDepth(){
    this->depth++;
}
int Bucket::remove(std::string pseudoKey){
    return -1 + this->map.erase(pseudoKey); // returns 0 if one member erased; // TODO: handle exceptions
}
int Bucket::insert(std::string value, std::string pseudoKey){
    if(this->getCurrentSize() == this->size){
        return -1;
    }
    if(this->map.find(pseudoKey) != this->map.end()){
            return -2;
    }
    //this->map.at(pseudoKey) = key;
    this->map.insert({pseudoKey, value});
    return 0;
}
