//
// Created by Wojciech Sitek on 17/11/2019.
//

#ifndef AAL_GRAPHS_EDGE_H
#define AAL_GRAPHS_EDGE_H

#include "Color.h"
#include <memory>

class Edge{
    double capacity;
    std::shared_ptr<Edge> reverseEdge;
public:
    //        ---GETTERS & SETTERS---
    void setCapacity(double capacity);
    [[nodiscard]] double getCapacity() const;
    void scaleCapacity(double);

    void setReverseEdge(std::shared_ptr<Edge> reverseEdge);
    [[nodiscard]] std::shared_ptr<Edge> getReverseEdge() const;

    //        ---CONSTRUCTOR---
    explicit Edge(double capacity);

    //       ---DESTRUCTOR---
    virtual ~Edge(){
        reverseEdge.reset();
    }
};

#endif //AAL_GRAPHS_EDGE_H
