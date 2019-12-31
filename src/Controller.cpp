//
// Created by Wojtek on 15/11/2019.
//

#include "Controller.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <fstream>

using namespace std;

/**
     * DATA
     * (liczba źródeł) 2
     * (liczba zaworów) 2
     * (liczba punktów odbioru) 2
     * (w1) 3 c13 4 c14
     * (w2) 4 c24
     * (w3) c3 5 c35
     * (w4) c4 5 c45 6 c46
*/
void Controller::loadData(std::istream &stream) {
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

bool Controller::existsAugmentingPath() {
    return graph->searchAugmentingPath();
}

void Controller::synchronizeFlowAndGraph() {
    graph->synchronizeFlowAndGraph();
}

// print stats
ostream &operator<<(ostream &str, const Controller &controller) {
    str << controller.getGraph();
    return str;
}

void Controller::compareResults(istream &originalResultsFileStream) {
    stringstream results;
    results << *this;

    while(!originalResultsFileStream.eof()){
        string originalWord, word;
        originalResultsFileStream >> originalWord;
        results >> word;
        double originalValue = 1, value = 1;
        try{
            originalValue = stod(originalWord);
            value = stod(word);

            double error = (originalValue == 0) ? (value - originalValue) : (value - originalValue)/originalValue;
            if(error > 0.01){
                cout << "Blad przekroczyl 1%. Wynosi " << error*100 << "%." << endl;
                break;
            }
        }
        catch(invalid_argument &e){
            // if it is not double then do nothing
        }
    }
}


Controller::Controller(std::shared_ptr<Graph> graph) : graph(graph) {
    graph->createReverseEdges();
}

Controller::Controller() : graph(std::make_shared<Graph>()){

}

long long Controller::solve(bool debug) {
    if(debug) {
        int i = 1;
        while (existsAugmentingPath()) {
            synchronizeFlowAndGraph();
            if (i % 10 == 0) {
                cout << "Augmenting path no. " << i << endl;
            }
            i++;
        }
        return 0;
    }
    auto t1 = std::chrono::steady_clock::now();
    while (existsAugmentingPath()) {
        synchronizeFlowAndGraph();
    }
    auto t2 = std::chrono::steady_clock::now();
    return (t2 - t1).count();
}

const shared_ptr<Graph> &Controller::getGraph() const {
    return graph;
}
