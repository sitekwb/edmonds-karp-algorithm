//
// Created by Wojtek on 19/11/2019.
//

#include "Edge.h"

Edge::Edge(double capacity){
    this->capacity = capacity;
    this->flow = 0;
    this->reverseEdge = nullptr;
}

Edge *Edge::getReverseEdge() const {
    return reverseEdge;
}

void Edge::setReverseEdge(Edge *reverseEdge) {
    this->reverseEdge = reverseEdge;
}

