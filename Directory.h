#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <iostream>
#include <map>
#include <list>
#include "Bucket.h"
#endif


class Directory {
    public:
        Directory(int bucketSize);
        int insert(std::string key, std::string pseudoKey);
        bool findPseudoKey(std::string);
        int duplicateDirectory();
        int splitBucket(std::string pos);
        int getBucketSize();
    private:
        int globalDepth;
        int maxDepth;
        int bucketSize;
        std::map<std::string, Bucket*> buckets;
        int changeBucketLink(std::string pos, Bucket*); // changes bucket pointer in certain pos
        std::string getNfirstBits(std::string pseudoKey);
};

