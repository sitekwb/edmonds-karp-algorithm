#include <iostream>
#include "include/Controller.h"

int main(int argc, char *argv[]) {
    auto c = new Controller;

    c->load_data();

    while(c->existsAugmentingPath()) {
        c->synchronizeFlowAndGraph();
    }

    c->outputResults();

    delete c;

    return 0;
}