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
    double currentFlow;

    Vertice &createInfiniteVertice();
public:
    void setFirstReceiverIndex(int firstReceiverIndex);
    const std::vector<double> &getFlows() const;
    int getSize();
    int getTNumber();
    Vertice &getS();
    int getAugmentingPathReceiverNumber();
    Edge *getEdge(int v1, int v2);
    Edge &createReverseEdge(int v_1, int v_2);


    Vertice &addVertice(Vertice&);
    Vertice &createS();
    Vertice &createT();
    Vertice &createSource(double capacity);
    Edge &connect(int v_1, int v_2, double edgeCapacity, bool reverseEdge = true);

    void updateFlow();
    void createReceivers(int firstReceiverIndex, int receiversNumber);
    void connectReceiversWithT(Vertice &t, int first_receiver_index);
    void createReverseEdges();
    void createReceiversFlows(int receiversCount);
    bool searchAugmentingPath();
    void synchronizeFlowAndGraph();

    virtual ~Graph(){
        for(auto v: vertices){
            delete v;
        }
    }


};


#endif //AAL_GRAPHS_GRAPH_H
