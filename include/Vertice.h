//
// Created by Wojtek on 17/11/2019.
//

#ifndef AAL_GRAPHS_VERTICE_H
#define AAL_GRAPHS_VERTICE_H

#include <unordered_map>
#include "Edge.h"
#include <cfloat>

class Vertice {
    double capacity;
    Color color;
    int parentVertice;
    std::unordered_map<int, Edge*> edges;

public:
    //   ---STATIC METHODS---
    static double infinity();
    static int noParent();

    //   ---GETTERS & SETTERS---
    double getCapacity() const;
    void reduceCapacity(double capacity);

    Color getColor() const;
    void setColor(Color color);

    int getParentVertice() const;
    void setParentVertice(int parentVertice);
    bool hasParent();

    const std::unordered_map<int, Edge*> &getEdges() const;

    //   ---CONSTRUCTOR---
    explicit Vertice(double capacity);

    //   ---METHODS---
    Edge &createEdge(int verticeNumber, double edgeCapacity);

    //   ---OPERATORS---
    Edge &operator[](int v_2);

    //   ---DESTRUCTOR---
    virtual ~Vertice(){
        for(auto e: edges){
            delete e.second;
        }
    }
};

#endif //AAL_GRAPHS_VERTICE_H
