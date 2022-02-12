#include <string>


// String to integer conversion.
// Needed for running the elements on the above hash function
unsigned int strToInt(std::string element, int seed) {
    srand(seed);
    int value = 0;
    for (size_t i = 0; i < element.size(); i++) {
        value += element[i] * rand(); // diff hash for every index by mult. by index
    }
    return value;
}