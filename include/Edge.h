//
// Created by Wojtek on 17/11/2019.
//

#ifndef AAL_GRAPHS_EDGE_H
#define AAL_GRAPHS_EDGE_H



class Edge{
    double capacity;
    double flow;
    struct Edge *reverseEdge;
    bool isVisited;

public:
    Edge(double capacity);

    void setReverseEdge(Edge *reverseEdge);

    Edge *getReverseEdge() const;

    virtual ~Edge(){}
};


#endif //AAL_GRAPHS_EDGE_H
