#include <Edge.h>
#include <Vertice.h>

#include "Edge.h"

Edge::Edge(double capacity) {
    setCapacity(capacity);
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
    if(capacity < 0){
        throw std::out_of_range("Capacity less than 0");
    }
    this->capacity = capacity;
}

void Edge::scaleCapacity(const double maxCapacity) {
    if(maxCapacity <= 0){
        throw std::out_of_range("Scaled capacity out of range");
    }
    if (capacity != Vertice::infinity()) {
        capacity /= maxCapacity;
    }
}
