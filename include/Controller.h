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
public:
    void load_data(std::istream &stream);
    bool existsAugmentingPath();
    void synchronizeFlowAndGraph();
    void outputResults(std::ostream &stream);

    virtual ~Controller() {}

};


#endif //AAL_GRAPHS_CONTROLLER_H
