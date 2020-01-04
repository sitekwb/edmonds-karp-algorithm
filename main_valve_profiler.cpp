#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include "Solver.h"
#include "Generator.h"
#include <iomanip>

using namespace std;

int main(int argc, char *argv[]) {
    try{
        if(argc != 4){
            throw invalid_argument("Required 3 arguments (outputFile, startValveCount, iterationCount). Given "+to_string(argc-1)+". Preferred values: valve_profiler_stats.txt 1000 5000");
        }

        ofstream fs(argv[1]);

        int valveCount = atoi(argv[2]);
        for(int i=1; i <= atoi(argv[3]); ++i, valveCount+=1000) {
            int sourceCount = valveCount/100;
            int receiverCount = valveCount/100;
            int augmentingPathCount = valveCount/i/10;
            double averageAugmentingPathLength = (double)i*100;
            double augmentingPathLengthStandardDeviation = averageAugmentingPathLength/100;

            Generator generator(sourceCount, valveCount, receiverCount, augmentingPathCount,
                                averageAugmentingPathLength, augmentingPathLengthStandardDeviation);
            generator.generateGraph();
            Solver controller(generator.getGraph());
            auto time = controller.solve();
            fs   << valveCount << ';' << controller.getGraph()->getEdgesCount() << ';' << time << endl;
            cout << setw(6) << valveCount << ';' << setw(6) << controller.getGraph()->getEdgesCount() << ';' << setw(12) << time << endl;
        }
        fs.close();

    }
    catch (exception &e) {
        cout << e.what();
        return 1;
    }

    return 0;
}