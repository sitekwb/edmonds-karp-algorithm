#include "Solver.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    try{
        Solver solver;

        if(argc > 2){
            throw invalid_argument("Required 0 or 1 argument [results_file]. Given "+to_string(argc-1)+".");
        }

        // load data
        solver.loadData(cin);
        cout << "Data loaded" << endl;

        // solve graph
        auto time = solver.solve();
        cout << "Graph solved with time " << time << endl;

        // save results to file
        if(argc == 2){
            ofstream resultsFileStream(argv[1]);
            resultsFileStream << *solver.getGraph();
            resultsFileStream.close();
            cout << "Results saved" << endl;
        }
        cout << "RESULTS: " << endl;
        cout << *solver.getGraph();
    }
    catch (exception &e) {
        cout << e.what();
        return 1;
    }

    return 0;
}