#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <iostream>
#include <map>
#include <list>
#include "Bucket.h"
#include <vector>
#include <math.h>
#endif


class Directory {
    public:
        Directory(int bucketSize);
        Directory(int bucketSize, int pseudoKeySize);
        int insert(std::string key, std::string pseudoKey);
        bool findPseudoKey(std::string);
        void duplicateDirectory();
        int splitBucket(std::string pos);
        int getBucketSize();
        int getGlobalDepth();
        void printDirectory();
    private:
        int globalDepth;
        int maxDepth;
        int bucketSize;
        int pseudoKeySize;
        std::map<std::string, Bucket*> buckets;
        int changeBucketLink(std::string pos, Bucket*); // changes bucket pointer in certain pos
        std::string getNfirstBits(std::string pseudoKey);
        std::string getNfirstBits(std::string pseudoKey, int add);
        void moveBucket(std::string startingPos, std::string dst);
        void increaseGlobalDepth();
        void removeBucket(std::string pos);
        void addBucket(std::string pos);
        std::string intToBinaryString(unsigned long);
        void reorganizePointers(std::string pos, Bucket* p_OldBucket, Bucket* p_NewBucket);
};

