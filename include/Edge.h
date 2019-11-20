//
// Created by Wojtek on 17/11/2019.
//

#ifndef AAL_GRAPHS_EDGE_H
#define AAL_GRAPHS_EDGE_H


#include "Color.h"

class Edge{
    double capacity;
    double flow;
    Edge *reverseEdge;
public:
    Edge(double capacity);

    void setReverseEdge(Edge *reverseEdge);

    Edge *getReverseEdge() const;

    virtual ~Edge(){}
};


#endif //AAL_GRAPHS_EDGE_H
