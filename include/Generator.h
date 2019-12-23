//
// Created by Wojtek on 30/11/2019.
//

#ifndef AAL_GRAPHS_GENERATOR_H
#define AAL_GRAPHS_GENERATOR_H


#include "Graph.h"
#include <random>
#include <ostream>


class Generator {
    /**
     * Graph built by generator
     */
    Graph graph;

    /**
     * Input parameters of generator
     */
    int sourceCount, valveCount, receiverCount, augmentingPathCount;

    std::default_random_engine generator;
    std::normal_distribution<double> augmentingPathDistribution;
    std::uniform_real_distribution<double> flowDistribution;
    std::uniform_int_distribution<int> sourceDistribution;
    std::uniform_int_distribution<int> valveDistribution;
    std::uniform_int_distribution<int> receiverDistribution;

    /**
     * Count of disconnected valves needed to make graph connected in the end
     */
     int disconnectedValves;

     /**
      * Adds one augmenting path
      * @see Generator#augmentingPathCount lowered by 1
      * @see Generator#disconnectedValves lowered
      * @see Generator#graph updated
      */
     void addAugmentingPath();
     int nextValveIndex();
     void connectValves(Vertice &valve1, int valve2Index, double flow);
     double getMaxCapacity();
     /**
      * Goes through all graph and divides each capacity by maxCapacity
      * Objective: all capacities scaled to 0-1
      * @see #generateGraph
      */
     void scaleCapacity(double maxCapacity);
public:
    Generator(int sourceCount, int valveCount, int receiverCount, int augmentingPathCount, double averageAugmentingPathLength, double augmentingPathLengthStandardDeviation);
    void generateGraph();

    friend std::ostream &operator<<(std::ostream &os, const Generator &generator);
};


#endif //AAL_GRAPHS_GENERATOR_H
