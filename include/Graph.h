//
// Created by Wojtek on 17/11/2019.
//

#ifndef AAL_GRAPHS_GRAPH_H
#define AAL_GRAPHS_GRAPH_H

#include <vector>
#include <forward_list>
#include "Vertice.h"

class Graph {
    std::vector<Vertice*> vertices;
    std::vector<double>flows;
    std::forward_list<int>augmentingPath;
public:
    const std::vector<double> &getFlows() const;

private:

    Vertice &createInfiniteVertice();
public:
    void addVertice(Vertice&);
    Vertice &createS();
    Vertice &createT();
    Vertice &createSource();
    void createReceivers(int firstReceiverIndex, int receiversNumber);

    Edge &connect(int v_1, int v_2, double edgeCapacity, bool reverseEdge = true);
    void connectSourcesWithS();
    void connectReceiversWithT(Vertice &t, int first_receiver_index);
    void createReverseEdges();
    Edge &createReverseEdge(int v_1, int v_2);

    void createReceiversFlows(int receiversCount);

    bool searchAugmentingPath();

    virtual ~Graph(){
        for(auto v: vertices){
            delete v;
        }
    }

    int getSize();
    int getTNumber();
    Vertice &getS();

};


#endif //AAL_GRAPHS_GRAPH_H
