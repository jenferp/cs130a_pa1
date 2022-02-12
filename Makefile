CXX = g++
CXXFLAGS = -std=c++11 -g -Wimplicit-int-float-conversion -Wall -Wextra -Wno-unused-parameter -Wno-unused-private-field
all = PA1.out

PA1.out: PA1.o BloomFilter.o HashTable.o strToInt.o
	${CXX} ${CXXFLAGS} $^ -o $@

PA1.o: PA1.cpp
	${CXX} ${CXXFLAGS} $^ -c

BloomFilter.o: BloomFilter.cpp
	${CXX} ${CXXFLAGS} $^ -c

HashTable.o: HashTable.cpp
	${CXX} ${CXXFLAGS} $^ -c

strToInt.o: strToInt.cpp
	${CXX} ${CXXFLAGS} $^ -c

clean:
	rm -f *.out *.o
