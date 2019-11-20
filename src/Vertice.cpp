//
// Created by Wojtek on 17/11/2019.
//

#include "Vertice.h"

using namespace std;

Edge &Vertice::createEdge(int verticeNumber, double edgeCapacity) {
    auto edge = new Edge(edgeCapacity);
    edges.insert({verticeNumber, edge});
    return *edge;
}

Vertice::Vertice(double capacity) {
    this->capacity = capacity;
}

const std::unordered_map<int, Edge*> &Vertice::getEdges() const {
    return edges;
}


double Vertice::infinity() {
    return numeric_limits<double>::max();
}

Edge &Vertice::operator[](int v_2) {
    return *(edges[v_2]);
}
