#ifndef AAL_GRAPHS_GRAPH_H
#define AAL_GRAPHS_GRAPH_H

#include <vector>
#include <unordered_map>
#include <memory>
#include <ostream>
#include "Vertice.h"

/**
 * @class
 * Represents graph.
 * Stores graph as vector of vertices with adjacent edges.
 * @see README.md
 */
class Graph {
    /// Vector of vertices in order: s, sources, valves, receivers, t
    std::vector<std::shared_ptr<Vertice>> vertices;

    /// Array of flows with size of receiver count
    std::vector<double> flows;

    int firstReceiverIndex;

    double currentFlow;

    int edgesCount = 0;

    /// Creates vertice with infinite capacity
    std::shared_ptr<Vertice> createInfiniteVertice();

public:
    /// ----- CONSTRUCTORS -----

    /// Default constructor
    Graph();

    /**
     * Create empty graph without edges
     * @param sourceCount number of sources
     * @param valveCount number of valves
     * @param receiverCount number of receivers
     */
    Graph(int sourceCount, int valveCount, int receiverCount);

    /// ----- GETTERS & SETTERS -----
    void setFirstReceiverIndex(int firstReceiverIndex);

    [[nodiscard]] int getFirstReceiverIndex() const;

    [[nodiscard]] const std::vector<double> &getFlows() const;

    [[nodiscard]] const std::vector<std::shared_ptr<Vertice>> &getVertices() const;

    void incrementFlow(int index, double value);

    void incrementCurrentFlow(double value);

    int getSize();

    [[nodiscard]] int getEdgesCount() const;

    int getTNumber();

    std::shared_ptr<Vertice> getS();

    int getAugmentingPathReceiverNumber();

    std::shared_ptr<Edge> getEdge(int v1, int v2);

    int getSourceCount();

    int getValveCount();

    int getReceiverCount();

    void scaleFlows(double maxCapacity);

    /// ----- METHODS -----
    std::shared_ptr<Edge> createReverseEdge(int v_1, int v_2);

    std::shared_ptr<Vertice> addVertice(std::shared_ptr<Vertice>);

    std::shared_ptr<Vertice> createS();

    std::shared_ptr<Vertice> createT();

    std::shared_ptr<Vertice> createSource(double capacity);

    std::shared_ptr<Vertice> createValve(double capacity);

    std::shared_ptr<Vertice> createVertice(double capacity, bool isValve = true);

    std::shared_ptr<Edge> connect(int v_1, int v_2, double edgeCapacity, bool reverseEdge = true);

    void updateFlow();

    void createReceivers(int firstReceiverIndex, int receiversNumber);

    void connectReceiversWithT(int first_receiver_index, double flow = Vertice::infinity());

    void createReverseEdges();

    void createReceiversFlows(int receiversCount);

    bool searchAugmentingPath();

    void synchronizeFlowAndGraph();

    void clearFlows();

    /// ----- DESTRUCTOR -----
    virtual ~Graph() {
        vertices.clear();
    }

    /// Print results
    friend std::ostream &operator<<(std::ostream &os, const Graph &graph);
};


#endif //AAL_GRAPHS_GRAPH_H
