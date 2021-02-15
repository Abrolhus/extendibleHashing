#ifndef BUCKET_H
#define BUCKET_H
#include <list>
#include <map>
#include <iostream>
class Bucket {
    /* Balde que armazena chaves indexadas por hash
     */
    public:
        // void find(std::string);
        Bucket(int size, int depth);
        Bucket(int size);
        int insert(std::string key, std::string pseudoKey);
        bool isFull();
        int getDepth();
        int remove(std::string);
        void increaseDepth();
        std::map<std::string, std::string> map; // por enquanto vou deixar esse atributo como public pela comodidade; TODO: public method to access bucket's map


    private:
        int depth;
        int size;
        int getCurrentSize();

};
#endif

