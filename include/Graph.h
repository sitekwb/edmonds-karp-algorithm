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
public:
    const std::vector<Vertice *> &getVertices() const;

private:
    std::vector<double>flows;
    int firstReceiverIndex;

    double currentFlow;

    Vertice &createInfiniteVertice();
public:
    Graph();

    /**
     * Create empty graph without edges
     * @param sourceCount number of sources
     * @param valveCount number of valves
     * @param receiverCount number of receivers
     */
    Graph(int sourceCount, int valveCount, int receiverCount);

    void setFirstReceiverIndex(int firstReceiverIndex);
    int getFirstReceiverIndex() const;

    const std::vector<double> &getFlows() const;

    int getSize();

    int getTNumber();

    Vertice &getS();

    int getAugmentingPathReceiverNumber();

    Edge *getEdge(int v1, int v2);

    Edge &createReverseEdge(int v_1, int v_2);

    int getSourceCount();
    int getValveCount();
    int getReceiverCount();





    Vertice &addVertice(Vertice&);
    Vertice &createS();
    Vertice &createT();
    Vertice &createSource(double capacity);
    Edge &connect(int v_1, int v_2, double edgeCapacity, bool reverseEdge = true);



    void updateFlow();
    void createReceivers(int firstReceiverIndex, int receiversNumber);
    void connectReceiversWithT(Vertice &t, int first_receiver_index, double flow = Vertice::infinity());
    void createReverseEdges();
    void createReceiversFlows(int receiversCount);
    bool searchAugmentingPath();
    void synchronizeFlowAndGraph();

    virtual ~Graph(){
        for(auto it = vertices.begin(); it != vertices.end(); ++it){
            delete *it;
        }
    }


};


#endif //AAL_GRAPHS_GRAPH_H
