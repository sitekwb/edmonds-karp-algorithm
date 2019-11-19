//
// Created by Wojtek on 17/11/2019.
//

#ifndef AAL_GRAPHS_GRAPH_H
#define AAL_GRAPHS_GRAPH_H

#include <vector>
#include "Vertice.h"

class Graph {
    std::vector<Vertice&> vertices;//TODO smart pointers

    Vertice &createInfiniteVertice();
public:
    void addVertice(Vertice&);
    Vertice &createS();
    Vertice &createT();

    void connect(int, int, double);
    void connectReceiversWithT(Vertice &t, int first_receiver_index);
    void createReverseEdges();

    virtual ~Graph();

};


#endif //AAL_GRAPHS_GRAPH_H
