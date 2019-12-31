//
// Created by Wojtek on 17/11/2019.
//

#include "Vertice.h"

using namespace std;

std::shared_ptr<Edge> Vertice::createEdge(int verticeNumber, double edgeCapacity) {
    auto edge = make_shared<Edge>(edgeCapacity);
    edges[verticeNumber] = edge;
    return edge;
}

Vertice::Vertice(double capacity) {
    this->capacity = capacity;
    this->color = WHITE;
    this->parentVertice = noParent();
}

const std::unordered_map<int, shared_ptr<Edge>> &Vertice::getEdges() const {
    return edges;
}


double Vertice::infinity() {
    return numeric_limits<double>::max();
}

std::shared_ptr<Edge> Vertice::operator[](int v_2) {
    return edges[v_2];
}

Color Vertice::getColor() const {
    return color;
}

void Vertice::setColor(Color color) {
    Vertice::color = color;
}

int Vertice::getParentVertice() const {
    return parentVertice;
}

void Vertice::setParentVertice(int parentVertice) {
    Vertice::parentVertice = parentVertice;
}

int Vertice::noParent() {
    return -1;
}

bool Vertice::hasParent() {
    return parentVertice != -1;
}

double Vertice::getCapacity() const {
    return capacity;
}

void Vertice::reduceCapacity(double capacity) {
    this->capacity -= capacity;
}

int Vertice::getEdgesCount() {
    return edges.size();
}

bool Vertice::issetEdge(int vIndex) {
    return edges.find(vIndex) != edges.cend();
}

void Vertice::incrementCapacity(double capacity) {
    Vertice::capacity += capacity;
}

void Vertice::scaleCapacity(double maxCapacity) {
    if(capacity != Vertice::infinity()) {
        capacity /= maxCapacity;
    }
}

bool Vertice::isDisconnected() {
    return !isConnected();
}

bool Vertice::isConnected() {
    return getEdgesCount() > 0;
}
