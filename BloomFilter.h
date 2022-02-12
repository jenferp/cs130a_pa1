#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H

#include <cstdint>
#include <string>
#include <vector>
#include "HashTable.h"
#include <stdlib.h>
#include <ctime>
#include <array>

class BloomFilter {
    float p; // probability of false positives
    int m; // expected number of strings to be inserted
    float c; // scale factor of bloom filter size
    float d; // scale factor of number of hash functions
    int num;
    bool* filter;
    int size;
    HashTable* ht; // auxiliary hash table
    int seed;

public:
    int q;
    BloomFilter(float p, int m, float c, float d);

    int hashTableSize(int size);
    void insert(std::string element);
    void remove(std::string element);
    bool find(std::string element);
    int hash(unsigned int element, int index);
    int bloomFilterSize(float p, int m, float c);
    int numHashFunctions(int n, int m, float d);
    int generatePrime(int num);
    bool isPrime(int x);
    void print();
};

#endif
