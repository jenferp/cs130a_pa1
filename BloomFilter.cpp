// BloomFilter.cpp
#include "BloomFilter.h"
#include "strToInt.h"
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <stdlib.h>

// std::vector<int> primes;

// p := probability of false positive
// m := expected number of strings to be inserted
// c := scale factor of bloom filter size
// d := scale factor of number of hash functions
BloomFilter::BloomFilter(float p, int m, float c, float d) {
    this->p = p;
    this->m = m;
    this->c = c;
    this->d = d;
    

    this->size = bloomFilterSize(p, m, c);
    this->q = hashTableSize(size);

    ht = new HashTable(q);
    num = numHashFunctions(size, m, d);
    // primes.clear();
    generatePrime(num);
    this->p = powf((float)1 - expf(-(float)num * (float)m / (float)size), (float)num); // given equation

    srand(std::time(nullptr));
    this->seed = rand();

    // initialize to bit array have all 0s, corresp. to an empty bloom filter
    // using char instead of int to save space (single byte v. 4 bytes)
    filter = new bool [size]; 
    for (int i = 0; i < size; i++) {
        filter[i] = 0;
    }
}

int BloomFilter::hashTableSize(int size) {
  int i = 0;
  while(!isPrime(size + i))
    i++;
  return size + i;
}

// Insert a string into the bloom filter.
void BloomFilter::insert(std::string element) {
    // int value = strToInt(element, seed);
    //std::cout << value << "hello" << std::endl;
    (*ht).deleteItem(element);
    for (int i = 0; i < num; i++) {
        int index = hash(strToInt(element, seed), i); // put value into hash function
        if (filter[index] == false)
            filter[index] = true; // set bit to 1 -> in the filter
        //std::cout << index << std::endl;
    }
}

// Delete an element from the bloom filter.
// This will use an auxiliary hash table. defined below.
void BloomFilter::remove(std::string element) {
    (*ht).remove(element);
}

// Return true if the element is in the bloom filter.
// otherwise return false.
bool BloomFilter::find(std::string element) {
    int value = strToInt(element, seed);
    for (int i = 0; i < num; i++) {
        int index = hash(value, i);
        if (filter[index] == false) {
            return false;
        }
    }
    if ((*ht).find(element)) { // check that it's not in the hash table either
        return false;
    }
    return true;
}

// Compute the bloom filter size based on the false positive probability desired.
// and the expected number of strings to be inserted.
// Scale the computed size by 'c' (for experimental purposes).
// p := probability of false positive
// m := expected number of strings to be inserted
// c := scale factor of bloom filter size
int BloomFilter::bloomFilterSize(float p, int m, float c) {
    int n = -(float)m * logf(p) / pow(logf(2), 2); // given equation
    return n * (int)c; // bits
}

// Compute the number of hash functions to use based on the bloom filter size,
// and the expected number of strings to be inserted.
// Scale the computed size by 'd' (for experimental purposes).
// n := bloom filter size
// m := expected number of strings to be inserted
// d := scale factor of bloom filter size
int BloomFilter::numHashFunctions(int n, int m, float d) {
    int k = ceil(((float)n * (float)logf(2)) / (float)m); // given equation
    return k * (int)d;
}

// num := number of functions I want to generate
// prime that is bigger than the number
int BloomFilter::generatePrime(int num) {
    int x = 0;
    while (!isPrime(num+x)) {
        x++;
    }
    return num+x;
}

// helper function for generatePrime
bool BloomFilter::isPrime(int x) {
    for (int i = 2; i <= ceil((double)x/2.0); i++) {
        if (x % i == 0)
            return false;
    }
    return true;
}

// Family of hash functions
// The index specifies which hash functions should be used
int BloomFilter::hash(unsigned int element, int index) {
    srand(seed);
    for (int i = 0; i < index; i++) {
        rand();
    }
    int i = rand();
    int j = rand();
    return (i * element + j) % this->size;
}

// Testing
void BloomFilter::print() {
    for (int i = 0; i < size; i++) {
        std::cout << filter[i];
    }
    std::cout << std::endl;
}