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
    ///   ---METHODS---
    void load_data(std::istream &stream);
    bool exists_augmenting_path();
    void synchronize_flow_and_graph();
    void output_results(std::ostream &stream);

    ///   ---DESTRUCTOR---
    virtual ~Controller() {}

};


#endif //AAL_GRAPHS_CONTROLLER_H
