//
// Created by Wojtek on 15/11/2019.
//

#include "Graph.h"
#include "Vertice.h"
#include <forward_list>

#ifndef AAL_GRAPHS_CONTROLLER_H
#define AAL_GRAPHS_CONTROLLER_H


class Controller {
    Graph graph;
    std::forward_list<Vertice&>augmentingPath;
public:
    void load_data();
    bool existsAugmentingPath();
    void synchronizeFlowAndGraph();
    void outputResults();

};


#endif //AAL_GRAPHS_CONTROLLER_H
