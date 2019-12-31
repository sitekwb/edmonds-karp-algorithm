#include "Controller.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    try{
        Controller controller;

        if(argc > 5 || argc < 3){
            throw invalid_argument("Required from two to four arguments (input_file, stats_file, [original_results_file, results_file]). Given "+to_string(argc-1)+".");
        }

        // load data
        ifstream inputFileStream(argv[1]);
        inputFileStream.exceptions (ifstream::failbit | ifstream::badbit );
        controller.loadData(inputFileStream);
        inputFileStream.close();
        cout << "Data loaded" << endl;

        // solve graph
        controller.solve();
        cout << "Graph solved";

        // compare with original results
        if(argc >= 4) {
            ifstream originalResultsFileStream(argv[3]);
            controller.compareResults(originalResultsFileStream);
            originalResultsFileStream.close();
            cout << "Compared with original results";
        }

        // save results to file
        if(argc == 5){
            ofstream resultsFileStream(argv[4]);
            resultsFileStream << controller.getGraph();
            resultsFileStream.close();
            cout << "Results saved";
        }

        cout << controller.getGraph();
    }
    catch (exception &e) {
        cout << e.what();
        return 1;
    }

    return 0;
}