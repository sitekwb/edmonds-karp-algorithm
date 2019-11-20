#include "Controller.h"
#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {
    auto c = new Controller;

    std::fstream file_stream(argv[1], std::fstream::in);

    c->load_data(file_stream);

    file_stream.close();

    while(c->existsAugmentingPath()) {
        c->synchronizeFlowAndGraph();
    }

    c->outputResults(std::cout);

    delete c;

    return 0;
}