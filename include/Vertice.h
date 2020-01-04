//
// Created by Wojtek on 17/11/2019.
//

#ifndef AAL_GRAPHS_VERTICE_H
#define AAL_GRAPHS_VERTICE_H

#include <unordered_map>
#include "Edge.h"
#include <cfloat>

/**
 * @class
 * Represents vertice with graph.
 * Has its capacity.
 * Stores map of adjacent edges.
 */
class Vertice {
    /// Each vertice has its capacity
    double capacity;

    /// Default white, changes in searching (BFS) or generating (randomly) augmenting path
    Color color;

    /// Default Vertice::noParent(), changes in searching or generating augmenting path
    int parentVertice;

    /// Hash map of edges
    std::unordered_map<int, std::shared_ptr<Edge>> edges;

public:
    //   ---STATIC METHODS---
    static double infinity();

    static int noParent();

    //   ---GETTERS & SETTERS---
    [[nodiscard]] double getCapacity() const;

    void incrementCapacity(double capacity);

    void reduceCapacity(double capacity);

    void scaleCapacity(double maxCapacity);

    [[nodiscard]] Color getColor() const;

    void setColor(Color color);

    [[nodiscard]] int getParentVertice() const;

    void setParentVertice(int parentVertice);

    bool hasParent();

    [[nodiscard]] const std::unordered_map<int, std::shared_ptr<Edge>> &getEdges() const;

    bool isConnected();

    bool isDisconnected();

    //   ---CONSTRUCTOR---
    explicit Vertice(double capacity);

    //   ---METHODS---
    std::shared_ptr<Edge> createEdge(int verticeNumber, double edgeCapacity);

    int getEdgesCount();

    bool issetEdge(int vIndex);

    //   ---OPERATORS---
    std::shared_ptr<Edge> operator[](int v_2);

    //   ---DESTRUCTOR---
    virtual ~Vertice() {
        edges.clear();
    }
};

#endif //AAL_GRAPHS_VERTICE_H
