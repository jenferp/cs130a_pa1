// HashTable.cpp 
#include "HashTable.h"
#include "BloomFilter.h"
#include "strToInt.h"
#include <iostream>

// Separate Chaining Hash Table
// This will be used for your removed elements of the bloom filter
// q := the size of the hash table (prime number)
HashTable::HashTable(int q) {
    this->q = q;
    // table.resize(q);
    srand(std::time(nullptr));
    this->seed = rand();
    table = std::vector<std::vector<std::string> >();
    //std::cout << "table size: " << table.size() << std::endl;
    //std::cout << "q: " << q << std::endl;
}

// Function for implementing the separate chaining hash table
int HashTable::getHash(int x) {
    return (x % q);
}
// Insert a string into the hash table.
void HashTable::remove(std::string element) {
    int index = getHash(strToInt(element, seed));
    //std::cout << "index: " << index << std::endl;
    table[index].push_back(element);
}

// Return true if the element is in the hash table,
// otherwise return false.
bool HashTable::find(std::string element) {
    int index = getHash(strToInt(element, seed));
    // for (std::vector<std::string>::iterator i = table[index].begin(); i != table[index].end(); i++) {
    //     if (*i == element) {
    //         return true;
    //     }
    // }
    return false;
}

bool HashTable::deleteItem(std::string element) {
    int index = getHash(strToInt(element, seed));
    // for (std::vector<std::string>::iterator i = table[index].begin(); i != table[index].end(); i++) {
    //     if (*i == element) {
    //         table[index].erase(i);
    //         return true;
    //     }
    // }
    return false;
}