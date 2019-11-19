//
// Created by Wojtek on 15/11/2019.
//

#include "../include/Controller.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

/**
     * DATA
     * (liczba źródeł) 2
     * (pierwszy punkt odbioru) 5 (liczba punktów odbioru) 2
     * (w1) 3 c13 4 c14
     * (w2) 4 c24
     * (w3) c3 5 c35
     * (w4) c4 5 c45 6 c46
     */
void Controller::load_data(){
    int source_count;
    cin>>source_count;

    int first_receiver_index;
    cin>>first_receiver_index;

    graph.createS();


    for(int i=0; i<source_count; ++i){
        auto vertice = graph.createSource();

        string str;
        if(!getline(cin, str)){
            throw exception();
        }
        stringstream ss(str);

        int verticeNumber;
        double edgeCapacity;

        while(ss >> verticeNumber || ss >> edgeCapacity || !ss.eof()){
            vertice.createEdge(verticeNumber, edgeCapacity);
        }
    }

    //create vertices
    string str;
    while(getline(cin, str)){
        stringstream ss(str);

        double capacity;
        ss >> capacity;

        auto vertice = new Vertice(capacity);
        graph.addVertice(*vertice);

        int verticeNumber;
        double edgeCapacity;

        while(ss >> verticeNumber || ss >> edgeCapacity || !ss.eof()){
            vertice->createEdge(verticeNumber, edgeCapacity);
        }
    }

    auto t = graph.createT();

    graph.connectReceiversWithT(t, first_receiver_index);

    graph.createReverseEdges();
}

bool Controller::existsAugmentingPath(){
    //TODO
    return false;
}
void Controller::synchronizeFlowAndGraph(){
    //TODO
}
void Controller::outputResults(){
    //TODO
}