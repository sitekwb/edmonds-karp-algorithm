//
// Created by Wojtek on 17/11/2019.
//

#ifndef AAL_GRAPHS_GRAPH_H
#define AAL_GRAPHS_GRAPH_H

#include <vector>
#include "Vertice.h"

class Graph {
    std::vector<Vertice*> vertices;

    Vertice &createInfiniteVertice();
public:
    void addVertice(Vertice&);
    Vertice &createS();
    Vertice &createT();
    Vertice &createSource();
    void createReceivers(int firstReceiverIndex, int receiversNumber);

    Edge &connect(int v_1, int v_2, double edgeCapacity, bool reverseEdge = true);
    void connectReceiversWithT(Vertice &t, int first_receiver_index);
    void createReverseEdges();
    Edge &createReverseEdge(int v_1, int v_2);

    virtual ~Graph(){
        for(auto v: vertices){
            delete v;
        }
    }

    int getSize();
    int getTNumber();

};


#endif //AAL_GRAPHS_GRAPH_H
