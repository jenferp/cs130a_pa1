// main.cpp setup.txt input.txt successfulSearch.txt failedSearch.txt remove.txt
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include "BloomFilter.h"
#include "HashTable.h"

using namespace std;

int main(int argc, char** argv) {
    // return 0;

    // BloomFilter filter (0.4, 10000, 1.0, 1.0);
    // cout << "word 1:" << endl;
    // filter.insert("nap");
    // cout << filter.find("nap");
    // cout << "word 2:" << endl;
    // filter.insert("roue");
    // cout << filter.find ("roue");
    // cout << "word 3:" << endl;
    // filter.insert("railers");
    // cout << filter.find("railers");
    // cout << filter.find("bell") <<endl;
    // return 0;

    if (argc != 7) {
        cout << "Must have 6 arguments" << endl;
        return 1;
    }

    int tfpos = 0; // total num false positives over all phases
    int tfneg = 0; //           false negatives
    string falsePositives;
    string line = "";

    ifstream inFile1 (argv[1]); // setup.txt
    ifstream inFile2 (argv[2]); // input.text
    ifstream inFile3 (argv[3]); // successfulSearch.txt
    ifstream inFile4 (argv[4]); // failedSearch.txt
    ifstream inFile5 (argv[5]); // remove.txt

    // Output File
    ofstream outFile;
    string testNum = argv[6];
    string outFilename = "output" + testNum + ".txt";
    outFile.open(outFilename);

    float p = 0.5;
    float c = 1.0;
    float d = 1.0;
    int m = 0;

    if (inFile1.is_open() && inFile1.good()) {
        if (getline(inFile1, line))
            p = stof(line);
        if (getline(inFile1, line))
            m = stoi(line);
        if (getline(inFile1, line))
            c = stof(line);
        if (getline(inFile1, line))
            d = stof(line);
    } else if (inFile1.fail()) {
        cout << "Could not open file" << argv[1];
    }

    // Before the start of testing
    outFile << "Experiment for the values of:" << endl;
    outFile << "p = " << p << endl;
    outFile << "c = " << c << endl;
    outFile << "d = " << d << endl;
    BloomFilter testFilter (p, m, c, d);
    int s = testFilter.bloomFilterSize(p, m, c);
    // int q = testFilter.numHashFunctions(s, m, d);
    int q = testFilter.hashTableSize(s);
    outFile << "q = " << q << endl;

    for (int phase = 1; phase <= 10; phase++) {
        int fpos = 0, fneg = 0;

        for (int j = 0; j < 1000; j++) {
            getline(inFile2, line);
            // std::cout << "inserting " << line << std::endl;
            testFilter.insert(line);
        }

        for (int l = 0; l < 100; l++) {
            // Find words that should return TRUE
            getline(inFile3, line);
            if (!testFilter.find(line)) {
                // std::cout << "false neg: " << line << std::endl;
                fneg += 1 ;
                tfneg += 1 ;
            }

            // Find words that should return FALSE
            getline(inFile4, line);
            if (testFilter.find(line)) {
                fpos += 1;
                falsePositives += line + "\n";
                tfpos += 1;
            }
        }

         // Remove words
        for (int k = 0; k < 10; k++) {
            getline(inFile5, line);
            // std::cout << "Removing " << line << std::endl;
            // testFilter.remove(line);
        }
        // On each phase of testing
        outFile << "Phase " << phase << ":" << endl;
        outFile << "Number of false negatives :" << endl;
        outFile << fneg << endl;
        outFile << "Number of false positives :" << endl;
        outFile << fpos << endl;
        outFile << "Probability of false positives :" << endl;
        outFile << fpos / 100.0 << endl;
        outFile << "False Positive Elements :" << endl;
        outFile << falsePositives << endl;
    }

    // inFile1.close();
    // inFile2.close();
    // inFile3.close();
    // inFile4.close();
    // inFile5.close();
    
    // After all 10 phases, print the total statistics:
    outFile << "Number of false negatives:" << endl;
    outFile << tfneg << endl;
    outFile << "Number of false positives:" << endl;
    outFile << tfpos << endl;
    outFile << "Probability of false positives:" << endl;
    outFile << tfpos / 1000.0 << endl;

    // outFile.close();

    return 0;
}