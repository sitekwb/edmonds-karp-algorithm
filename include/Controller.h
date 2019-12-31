//
// Created by Wojtek on 15/11/2019.
//

#ifndef AAL_GRAPHS_CONTROLLER_H
#define AAL_GRAPHS_CONTROLLER_H

#include "Graph.h"
#include "Vertice.h"
#include <forward_list>
#include <ostream>
#include <chrono>
#include <fstream>

class Controller {
    std::shared_ptr<Graph> graph;
public:
    Controller();
    explicit Controller(std::shared_ptr<Graph> graph);
    ///   ---METHODS---
    long long solve(bool debug = false);
    [[nodiscard]] const std::shared_ptr<Graph> &getGraph() const;
    void loadData(std::istream &stream);
    bool existsAugmentingPath();
    void synchronizeFlowAndGraph();
    void compareResults(std::istream &);

    friend std::ostream &operator<<(std::ostream &os, const Controller &controller);

    ///   ---DESTRUCTOR---
    virtual ~Controller() {}

};


#endif //AAL_GRAPHS_CONTROLLER_H
