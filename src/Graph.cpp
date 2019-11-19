//
// Created by Wojtek on 17/11/2019.
//

#include <Graph.h>

#include "Graph.h"

void Graph::addVertice(Vertice &vertice) {
    vertices.push_back(vertice);
}

Vertice &Graph::createInfiniteVertice(){
    auto v = new Vertice(Vertice::infinity());
    vertices.push_back(v);
    return *v;
}

Vertice &Graph::createS() {
    return createInfiniteVertice();
}

Vertice &Graph::createT() {
    return createInfiniteVertice();
}

void Graph::connectReceiversWithT(Vertice &t, int first_receiver_index) {
    for(int i=first_receiver_index; i < vertices.size() - 1; ++i){

    }
}

void Graph::createReverseEdges() {
    for(int vNum=0; vNum < vertices.size(); ++vNum){
        auto v = vertices[vNum];
        for(auto e: v.getEdges()){
            if(!e.second.getReverseEdge()){
                // e.first is v2_number
                auto reverseEdge = vertices[e.first].createEdge(vNum);
                reverseEdge.setReverseEdge(&(e.second));
                e.second.setReverseEdge(&reverseEdge);
            }
        }
    }
}

Edge &Graph::connect(int v1_num, int v2_num, double edgeCapacity) {
    return vertices[v1_num].createEdge(v2_num, edgeCapacity);
}

Graph::~Graph() {
    for(auto v: vertices){
        delete &v;
    }
}


