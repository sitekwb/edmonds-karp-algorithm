#include "Generator.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    try{
        if(argc != 9){
            throw invalid_argument("Required eight arguments (graph_output_file, results_output_file, sourceCount, valveCount, receiverCount, augmentingPathCount, averageAugmentingPathLength, augmentingPathLengthStandardDeviation). Given "+to_string(argc-1)+".");
        }

        fstream output_file_stream(argv[1], fstream::out);
        fstream results_file_stream(argv[2], fstream::out);

        Generator generator(atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), atoi(argv[6]), stod(argv[7]), stod(argv[8]));

        output_file_stream.exceptions (ifstream::failbit | ifstream::badbit );

        generator.generateGraph();

        cout << generator;
        cout << generator.getGraph();

        output_file_stream << generator;
        results_file_stream << generator.getGraph();
    }
    catch (exception &e) {
        cout << e.what();
        return 1;
    }

    return 0;
}