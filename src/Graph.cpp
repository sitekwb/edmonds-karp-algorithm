//
// Created by Wojtek on 17/11/2019.
//

#include <queue>
#include "Graph.h"

void Graph::addVertice(Vertice &vertice) {
    vertices.push_back(&vertice);
}

Vertice &Graph::createInfiniteVertice(){
    auto v = new Vertice(Vertice::infinity());
    vertices.push_back(v);
    return *v;
}

Vertice &Graph::createS() {
    return createInfiniteVertice();
}

Vertice &Graph::createT() {
    return createInfiniteVertice();
}

void Graph::connectReceiversWithT(Vertice &t, int first_receiver_index) {
    for(int i=first_receiver_index; i < vertices.size() - 1; ++i){
        connect(i, getTNumber(), Vertice::infinity(), false);
    }
}

void Graph::createReverseEdges() {
    //go through all vertices without s and t
    for(int vNum=0; vNum < vertices.size(); ++vNum){
        auto v = vertices[vNum];
        for(auto e: v->getEdges()){
            if(!e.second->getReverseEdge()){
                createReverseEdge(vNum, e.first);
            }
        }
    }
}

Edge &Graph::connect(int v_1, int v_2, double edgeCapacity, bool reverseEdge) {
    auto &edge = (*vertices[v_1]).createEdge(v_2, edgeCapacity);
    if(reverseEdge){
        createReverseEdge(v_1, v_2);
    }
    return edge;
}




Vertice &Graph::createSource() {
    auto &source = createInfiniteVertice();

    // connect with s
    auto &s = *(vertices[0]);
    int sourceNumber = getSize()-1;
    int sNumber = 0;
    connect(sNumber, sourceNumber, Vertice::infinity(), false);

    return source;
}

Edge &Graph::createReverseEdge(int v_1, int v_2) {
    Edge &edge = (*vertices[v_1])[v_2];
    Edge &reverseEdge = vertices[v_2]->createEdge(v_1, 0);

    reverseEdge.setReverseEdge(&edge);
    edge.setReverseEdge(&reverseEdge);
    return reverseEdge;
}

int Graph::getSize() {
    return vertices.size();
}

void Graph::createReceivers(int firstReceiverIndex, int receiversNumber) {
    int receiverFinish = firstReceiverIndex + receiversNumber;
    for(int vNum=firstReceiverIndex; vNum < receiverFinish; ++vNum){
        createInfiniteVertice();
    }
}

int Graph::getTNumber() {
    return getSize()-1;
}

void Graph::connectSourcesWithS() {
    for(int i=1; i < vertices.size(); ++i){
        connect(0, i, Vertice::infinity(), false);
    }
}

void Graph::createReceiversFlows(int receiversCount) {
    flows.resize(receiversCount, 0);
}

const std::vector<double> &Graph::getFlows() const {
    return flows;
}

/*
 * BFS
   dla każdego wierzchołka u z G:
        kolor[u] = biały
        odleglosc[u] = inf
        rodzic[u] = NIL
    kolor[s] = SZARY
    odleglosc[s] = 0
    rodzic[s] = NIL
    Q.push(s)
    dopóki kolejka Q nie jest pusta:
        u = Q.front()
        Q.pop()
        dla każdego v z listy sąsiedztwa u:
            jeżeli v jest biały:
                kolor[v] = SZARY
                odleglosc[v] = odleglosc[u] + 1
                rodzic[v] = u
                Q.push(v)
        kolor[u] = CZARNY
*/
bool Graph::searchAugmentingPath() {
    for(auto u: vertices){
        u->setColor(white);
        u->setParentVertice(Vertice::noParent());
    }
    auto &s = getS();
    s.setColor(grey);

    std::queue<std::pair<int, Vertice *>>queue;
    queue.push({0, &s});

    while(!queue.empty()){
        auto u = queue.front();
        queue.pop();
        for(auto edge: u.second->getEdges()){
            if(edge.second->getCapacity() == 0){
                continue;
            }
            auto v = std::make_pair(edge.first, vertices[edge.first]);
            if(v.second->getColor() == white){
                v.second->setColor(grey);
                v.second->setParentVertice(u.first);
                queue.push(v);
            }
        }
        u.second->setColor(black);
    }
    //BFS done

    currentFlow = std::numeric_limits<int>::max();
    int v = getTNumber();
    while(vertices[v]->hasParent()){
        int parentV = vertices[v]->getParentVertice();
        currentFlow = std::min(currentFlow, getEdge(parentV, v)->getCapacity());
        v = parentV;
        if( v == 0 ){
            break;
        }
    }
    // v==0 means that we found augmenting path from s to t
    return v == 0;
}

Vertice &Graph::getS() {
    return *(vertices[0]);
}

Edge *Graph::getEdge(int v1, int v2) {
    return &(*vertices[v1])[v2];
}

void Graph::synchronizeFlowAndGraph() {
    int v_num = getTNumber();
    do{
        int v_parent = vertices[v_num]->getParentVertice();
        auto &edge = (*vertices[v_parent])[v_num];
        edge.setCapacity(edge.getCapacity() - currentFlow);
        edge.getReverseEdge()->setCapacity(edge.getCapacity() + currentFlow);

        v_num = v_parent;
    }while(v_num != 0);

    updateFlow();
}

int Graph::getAugmentingPathReceiverNumber() {
    return vertices[getTNumber()]->getParentVertice();
}

void Graph::setFirstReceiverIndex(int firstReceiverIndex) {
    Graph::firstReceiverIndex = firstReceiverIndex;
}

void Graph::updateFlow() {
    flows[getAugmentingPathReceiverNumber() - firstReceiverIndex] += currentFlow;
}




