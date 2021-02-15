#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <iostream>
#include <map>
#include <list>
#include "Bucket.h"
#include <vector>
#endif


class Directory {
    public:
        Directory(int bucketSize);
        int insert(std::string key, std::string pseudoKey);
        bool findPseudoKey(std::string);
        void duplicateDirectory(std::string pos);
        int splitBucket(std::string pos);
        int getBucketSize();
        void printDirectory();
    private:
        int globalDepth;
        int maxDepth;
        int bucketSize;
        std::map<std::string, Bucket*> buckets;
        int changeBucketLink(std::string pos, Bucket*); // changes bucket pointer in certain pos
        std::string getNfirstBits(std::string pseudoKey);
        std::string getNfirstBits(std::string pseudoKey, int add);
        void moveBucket(std::string startingPos, std::string dst);
        void increaseGlobalDepth();
        void removeBucket(std::string pos);
        void addBucket(std::string pos);
};

