#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <list>
#include <vector>

class HashTable {
    private:
        std::vector<std::vector<std::string> > table;
        int q; // the size of the hash table (prime number)
        int getHash(int x); // for h(x) = x mod q, x := value
        int seed;

public:
    HashTable(int q);

    void remove(std::string element);
    bool find(std::string element);
    bool deleteItem(std::string element);
};

#endif
