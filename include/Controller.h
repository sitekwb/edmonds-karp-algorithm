//
// Created by Wojtek on 15/11/2019.
//

#ifndef AAL_GRAPHS_CONTROLLER_H
#define AAL_GRAPHS_CONTROLLER_H

#include "Graph.h"
#include "Vertice.h"
#include <forward_list>

class Controller {
    Graph graph;
    std::forward_list<int>augmentingPath;
public:
    void load_data();
    bool existsAugmentingPath();
    void synchronizeFlowAndGraph();
    void outputResults();

    virtual ~Controller() {}

};


#endif //AAL_GRAPHS_CONTROLLER_H
