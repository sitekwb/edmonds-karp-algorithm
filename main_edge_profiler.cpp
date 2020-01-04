#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include "Solver.h"
#include "Generator.h"
#include <iomanip>

using namespace std;

/// Increasing edge count and counting solving times
int main(int argc, char *argv[]) {
    try{
        if(argc != 4){
            throw invalid_argument("Required 3 arguments (outputFile, startValveCount, iterationCount). Given "+to_string(argc-1)+".");
        }

        ofstream fs(argv[1]);

        int valveCount = atoi(argv[2]);
        int augmentingPathCount = 100;
        for(int i=1; i <= atoi(argv[3]); ++i, valveCount+=100, augmentingPathCount+=500) {
            int sourceCount = valveCount/100;
            int receiverCount = valveCount/100;
            double averageAugmentingPathLength = 100;
            double augmentingPathLengthStandardDeviation = 10;

            Generator generator(sourceCount, valveCount, receiverCount, augmentingPathCount,
                                averageAugmentingPathLength, augmentingPathLengthStandardDeviation);
            generator.generateGraph();
            Solver solver(generator.getGraph());
            auto time = solver.solve();
            fs << valveCount << ';' << solver.getGraph()->getEdgesCount() << ';' << time << endl;
            cout << setw(6) << valveCount << ';' << setw(6) << solver.getGraph()->getEdgesCount() << ';' << setw(13) << time << endl;
        }
        fs.close();

    }
    catch (exception &e) {
        cout << e.what();
        return 1;
    }

    return 0;
}