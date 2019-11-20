//
// Created by Wojtek on 15/11/2019.
//

#include "Controller.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

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
void Controller::load_data(std::istream &stream){
    int sourceCount;
    stream >> sourceCount;

    int valveCount;
    stream >> valveCount;

    int receiversCount;
    stream >> receiversCount;

    if(!stream){
        throw exception();
    }

    graph.createS();

    //go to new line
    string str;
    getline(stream, str);

    //create sources
    for(int i=0; i < sourceCount; ++i){
        auto &vertice = graph.createSource();

        if(!getline(stream, str)){
            throw exception();
        }
        stringstream ss(str);

        int verticeNumber;
        double edgeCapacity;

        while((ss >> verticeNumber && ss >> edgeCapacity) || !ss.eof()){
            vertice.createEdge(verticeNumber, edgeCapacity);
        }
    }


    //create valves
    for(int i=0; i<valveCount; ++i){
        getline(stream, str);
        stringstream ss(str);

        double capacity;
        ss >> capacity;

        auto vertice = new Vertice(capacity);
        graph.addVertice(*vertice);

        int verticeNumber;
        double edgeCapacity;

        while((ss >> verticeNumber && ss >> edgeCapacity) || !ss.eof()){
            vertice->createEdge(verticeNumber, edgeCapacity);
        }
    }

    int firstReceiverIndex = sourceCount + valveCount + 1;

    graph.createReceivers(firstReceiverIndex, receiversCount);

    auto t = graph.createT();

    graph.connectReceiversWithT(t, firstReceiverIndex);

    graph.createReverseEdges();

    graph.createReceiversFlows(receiversCount);
}

bool Controller::existsAugmentingPath(){
    return graph.searchAugmentingPath();
}
void Controller::synchronizeFlowAndGraph(){
    //TODO
}
void Controller::outputResults(ostream &stream){
    int i = 0;
    double flowSum = 0;
    for(auto flow: graph.getFlows()){
        stream << setw(3) << ++i << ": " << flow << endl;
        flowSum += flow;
    }
    stream << "FLOW SUM = " << flowSum << endl;
}