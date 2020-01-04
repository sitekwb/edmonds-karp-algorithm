#include <iostream>
#include <sstream>
#include <stdexcept>
#include "Solver.h"
#include "Generator.h"

using namespace std;

/// Counts how many solutions differ from generations
/// Saves time of computation to research complexity
int main(int argc, char *argv[]) {
    try{
        if(argc != 4){
            throw invalid_argument("Required 3 arguments (outputFile, startValveCount, iterationCount). Given "+to_string(argc-1)+".");
        }

        double errorSum = 0;
        int errorCount = 0;
        const int iterationCount = atoi(argv[3]);
        int valveCount = atoi(argv[2]);
        ofstream fs(argv[1]);
        for(int i=1; i <= iterationCount; ++i, valveCount += 10) {
            int sourceCount = valveCount/10;
            int receiverCount = sourceCount;
            int augmentingPathCount = sourceCount;
            double averageAugmentingPathLength = sourceCount;
            double augmentingPathLengthStandardDeviation = sourceCount/5;

            Generator generator(sourceCount, valveCount, receiverCount, augmentingPathCount,
                                averageAugmentingPathLength, augmentingPathLengthStandardDeviation);
            generator.generateGraph();

            // save original results
            stringstream originalResultsStream;
            originalResultsStream << *generator.getGraph();

            // solve graph
            Solver solver(generator.getGraph());
            auto time = solver.solve();
            fs << valveCount << ';' << solver.getGraph()->getEdgesCount() << ';' << time << endl;

            // compare with original results
            double error = solver.compareResults(originalResultsStream);
            errorSum += error;
            errorCount += (error != 0);
            cout << i << ":   -------   error = " << error << endl;
        }
        fs.close();
        cout << "Average error sum = " << errorSum / iterationCount << "%" << endl;
        cout << "Error count       = " << errorCount << " / " << iterationCount << endl;
    }
    catch (exception &e) {
        cout << e.what();
        return 1;
    }

    return 0;
}