//
// Created by Wojtek on 17/11/2019.
//

#include "Graph.h"

void Graph::addVertice(Vertice &vertice) {
    vertices.push_back(&vertice);
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
        connect(i, getTNumber(), Vertice::infinity(), false);
    }
}

void Graph::createReverseEdges() {
    for(int vNum=0; vNum < vertices.size(); ++vNum){
        auto v = vertices[vNum];
        for(auto e: v->getEdges()){
            if(!e.second->getReverseEdge()){
                createReverseEdge(vNum, e.first);
            }
        }
    }
}

Edge &Graph::connect(int v_1, int v_2, double edgeCapacity, bool reverseEdge) {
    auto &edge = (*vertices[v_1]).createEdge(v_2, edgeCapacity);
    if(reverseEdge){
        createReverseEdge(v_1, v_2);
    }
    return edge;
}




Vertice &Graph::createSource() {
    auto &source = createInfiniteVertice();

    // connect with s
    auto &s = *(vertices[0]);
    int sourceNumber = getSize()-1;
    int sNumber = 0;
    connect(sNumber, sourceNumber, Vertice::infinity(), false);

    return source;
}

Edge &Graph::createReverseEdge(int v_1, int v_2) {
    Edge &edge = (*vertices[v_1])[v_2];
    Edge &reverseEdge = vertices[v_2]->createEdge(v_1, 0);

    reverseEdge.setReverseEdge(&edge);
    edge.setReverseEdge(&reverseEdge);
    return reverseEdge;
}

int Graph::getSize() {
    return vertices.size();
}

void Graph::createReceivers(int firstReceiverIndex, int receiversNumber) {
    int receiverFinish = firstReceiverIndex + receiversNumber;
    for(int vNum=firstReceiverIndex; vNum < receiverFinish; ++vNum){
        createInfiniteVertice();
    }
}

int Graph::getTNumber() {
    return getSize()-1;
}




