//
// Created by Wojtek on 17/11/2019.
//

#include <unordered_map>
#include "Edge.h"
#include <cfloat>

#ifndef AAL_GRAPHS_VERTICE_H
#define AAL_GRAPHS_VERTICE_H

class Vertice {
    double capacity;
    std::unordered_map<int, Edge&> edges;

public:
    static double infinity();

    Vertice(double capacity);
    Edge &createEdge(int verticeNumber, double edgeCapacity);

    virtual ~Vertice();

    const std::unordered_map<int, Edge&> &getEdges() const;
};


#endif //AAL_GRAPHS_VERTICE_H
