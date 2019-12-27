#include "Generator.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    try{
        if(argc != 8){
            throw invalid_argument("Required six arguments (file, sourceCount, valveCount, receiverCount, augmentingPathCount, averageAugmentingPathLength, augmentingPathLengthStandardDeviation). Given "+to_string(argc-1)+".");
        }

        fstream file_stream(argv[1], fstream::out);

        Generator generator(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), stod(argv[6]), stod(argv[7]));

        file_stream.exceptions ( ifstream::failbit | ifstream::badbit );

        generator.generateGraph();

        //cout << generator;
        file_stream << generator;
    }
    catch (exception &e) {
        cerr << e.what();
        return 1;
    }

    return 0;
}