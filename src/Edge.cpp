//
// Created by Wojtek on 19/11/2019.
//

#include <Edge.h>
#include <Vertice.h>

#include "Edge.h"

Edge::Edge(double capacity) {
    this->capacity = capacity;
    this->reverseEdge = nullptr;
}

std::shared_ptr<Edge> Edge::getReverseEdge() const {
    return reverseEdge;
}

void Edge::setReverseEdge(std::shared_ptr<Edge> reverseEdge) {
    this->reverseEdge = reverseEdge;
}

double Edge::getCapacity() const {
    return capacity;
}

void Edge::setCapacity(double capacity) {
    Edge::capacity = capacity;
}

void Edge::scaleCapacity(double maxCapacity) {
    if (capacity != Vertice::infinity()) {
        capacity /= maxCapacity;
    }
}
