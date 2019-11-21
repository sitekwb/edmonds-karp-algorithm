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
    Color color;
    int parentVertice;
public:
    double getCapacity() const;

    void reduceCapacity(double capacity);

private:
    std::unordered_map<int, Edge*> edges;

public:
    static double infinity();
    static int noParent();

    explicit Vertice(double capacity);

    Color getColor() const;

    void setColor(Color color);

    int getParentVertice() const;

    void setParentVertice(int parentVertice);

    bool hasParent();

    Edge &createEdge(int verticeNumber, double edgeCapacity);

    virtual ~Vertice(){
        for(auto e: edges){
            delete e.second;
        }
    }

    const std::unordered_map<int, Edge*> &getEdges() const;

    Edge &operator[](int v_2);
};


#endif //AAL_GRAPHS_VERTICE_H
