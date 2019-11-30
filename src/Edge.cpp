//
// Created by Wojtek on 19/11/2019.
//

#include <Edge.h>

#include "Edge.h"

Edge::Edge(double capacity){
    this->capacity = capacity;
    this->reverseEdge = nullptr;
}

Edge *Edge::getReverseEdge() const {
    return reverseEdge;
}

void Edge::setReverseEdge(Edge *reverseEdge) {
    this->reverseEdge = reverseEdge;
}

double Edge::getCapacity() const {
    return capacity;
}

void Edge::setCapacity(double capacity) {
    Edge::capacity = capacity;
}
