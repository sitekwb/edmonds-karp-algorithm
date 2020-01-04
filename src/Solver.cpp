#include "Solver.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <fstream>

using namespace std;

void Solver::loadData(std::istream &stream) {
    int sourceCount;
    stream >> sourceCount;

    int valveCount;
    stream >> valveCount;

    int receiversCount;
    stream >> receiversCount;

    if (!stream) {
        throw exception();
    }

    graph->createS();

    //go to new line
    string str;
    getline(stream, str);


    //create sources and valves
    for (int i = 0; i < sourceCount + valveCount; ++i) {
        getline(stream, str);
        stringstream ss(str);

        double capacity;
        ss >> capacity;

        auto vertice = graph->createVertice(capacity, i >= sourceCount);

        int verticeNumber;
        double edgeCapacity;
        while ((ss >> verticeNumber && ss >> edgeCapacity) || !ss.eof()) {
            vertice->createEdge(verticeNumber, edgeCapacity);
        }
    }

    int firstReceiverIndex = sourceCount + valveCount + 1;
    graph->setFirstReceiverIndex(firstReceiverIndex);

    graph->createReceivers(firstReceiverIndex, receiversCount);

    graph->createT();

    graph->connectReceiversWithT(firstReceiverIndex);

    graph->createReverseEdges();

    graph->createReceiversFlows(receiversCount);
}

bool Solver::existsAugmentingPath() {
    return graph->searchAugmentingPath();
}

void Solver::synchronizeFlowAndGraph() {
    graph->synchronizeFlowAndGraph();
}

ostream &operator<<(ostream &str, const Solver &controller) {
    str << *(controller.getGraph());
    return str;
}

double Solver::compareResults(istream &originalResultsFileStream) {
    stringstream results;
    results << *this;

    while (!originalResultsFileStream.eof()) {
        string originalWord, word;
        originalResultsFileStream >> originalWord;
        results >> word;
        double originalValue = 1, value = 1;
        try {
            originalValue = stod(originalWord);
            value = stod(word);

            double error = (originalValue == 0) ? (value - originalValue) : (value - originalValue) / originalValue;
            if (error > 0.01) {
                return error * 100;
            }
        }
        catch (invalid_argument &e) {
            // if it is not double then do nothing
        }
    }
    return 0;
}


Solver::Solver(std::shared_ptr<Graph> graph) : graph(graph) {
    graph->clearFlows();
    graph->createReverseEdges();
}

Solver::Solver() : graph(std::make_shared<Graph>()) {

}

long long Solver::solve() {
    auto t1 = std::chrono::steady_clock::now();
    while (existsAugmentingPath()) {
        synchronizeFlowAndGraph();
    }
    auto t2 = std::chrono::steady_clock::now();
    return (t2 - t1).count();
}

const shared_ptr<Graph> &Solver::getGraph() const {
    return graph;
}
