//
// Created by Wojtek on 17/11/2019.
//

#ifndef AAL_GRAPHS_GRAPH_H
#define AAL_GRAPHS_GRAPH_H

#include <vector>
#include <unordered_map>
#include "Vertice.h"

class Graph {
    std::vector<Vertice*> vertices;
    std::vector<double>flows;
    int firstReceiverIndex;
public:
    void setFirstReceiverIndex(int firstReceiverIndex);
    void updateFlow();
private:
    double currentFlow;

    Vertice &createInfiniteVertice();
public:
    const std::vector<double> &getFlows() const;
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
    Edge *getEdge(int v1, int v2);

    void synchronizeFlowAndGraph();

    virtual ~Graph(){
        for(auto v: vertices){
            delete v;
        }
    }

    int getSize();
    int getTNumber();
    Vertice &getS();
    int getAugmentingPathReceiverNumber();

};


#endif //AAL_GRAPHS_GRAPH_H
