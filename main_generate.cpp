#include "Generator.h"
#include "Solver.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <sstream>

using namespace std;

/// Generation of graph from given attributes and check if its solving is correct
int main(int argc, char *argv[]) {
    try{
        if(argc != 9){
            throw invalid_argument("Required eight arguments (graph_output_file, results_output_file, sourceCount, valveCount, receiverCount, augmentingPathCount, averageAugmentingPathLength, augmentingPathLengthStandardDeviation). Given "+to_string(argc-1)+".");
        }

        ofstream output_file_stream(argv[1]);
        ofstream results_file_stream(argv[2]);
        stringstream originalResultsStream;

        Generator generator(atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), atoi(argv[6]), stod(argv[7]), stod(argv[8]));

        output_file_stream.exceptions (ifstream::failbit | ifstream::badbit );

        generator.generateGraph();

        output_file_stream << generator;
        results_file_stream << *generator.getGraph();
        originalResultsStream << *generator.getGraph();

        // solve graph
        Solver solver(generator.getGraph());
        auto time = solver.solve();
        cout << "Graph solved with time " << time << endl;

        // compare with original results
        double error = solver.compareResults(originalResultsStream);
        if(error != 0){
            cout << "Error! " << error << "%" << endl;
        }
        else{
            cout << "Correct!" << endl;
        }
    }
    catch (exception &e) {
        cout << e.what();
        return 1;
    }

    return 0;
}