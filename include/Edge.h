//
// Created by Wojciech Sitek on 17/11/2019.
//

#ifndef AAL_GRAPHS_EDGE_H
#define AAL_GRAPHS_EDGE_H

#include "Color.h"

class Edge{
    double capacity;
    Edge *reverseEdge;
public:
    //        ---GETTERS & SETTERS---
    void setCapacity(double capacity);
    double getCapacity() const;
    void scaleCapacity(double);

    void setReverseEdge(Edge *reverseEdge);
    Edge *getReverseEdge() const;

    //        ---CONSTRUCTOR---
    explicit Edge(double capacity);

    //       ---DESTRUCTOR---
    virtual ~Edge() = default;
};

#endif //AAL_GRAPHS_EDGE_H
