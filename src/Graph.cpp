//
// Created by Wojtek on 17/11/2019.
//

#include <queue>
#include "Graph.h"
#include <memory>
#include <iomanip>
#include <exception>

std::shared_ptr<Vertice> Graph::addVertice(std::shared_ptr<Vertice> vertice) {
    vertices.push_back(vertice);
    return vertice;
}

std::shared_ptr<Vertice> Graph::createInfiniteVertice(){
    auto v = std::make_shared<Vertice>(Vertice::infinity());
    vertices.push_back(v);
    return v;
}

std::shared_ptr<Vertice> Graph::createS() {
    return createInfiniteVertice();
}

std::shared_ptr<Vertice> Graph::createT() {
    return createInfiniteVertice();
}

void Graph::connectReceiversWithT(int first_receiver_index, double flow) {
    for(int i=first_receiver_index; i < vertices.size() - 1; ++i){
        connect(i, getTNumber(), flow, false);
    }
}

void Graph::createReverseEdges() {
    //go through all vertices without s and t
    for(int vNum=0; vNum < vertices.size(); ++vNum){
        auto v = vertices[vNum];
        for(const auto& e: v->getEdges()){
            ++edgesCount;
            if(!e.second->getReverseEdge()){
                createReverseEdge(vNum, e.first);
            }
        }
    }
}

std::shared_ptr<Edge> Graph::connect(int v_1, int v_2, double edgeCapacity, bool reverseEdge) {
    auto edge = (*vertices[v_1]).createEdge(v_2, edgeCapacity);
    if(reverseEdge){
        createReverseEdge(v_1, v_2);
    }
    return edge;
}

std::shared_ptr<Vertice> Graph::createValve(double capacity){
    return addVertice(std::make_shared<Vertice>(capacity));
}


std::shared_ptr<Vertice> Graph::createSource(double capacity) {
    auto source = addVertice(std::make_shared<Vertice>(capacity));

    // connect with s
    int sourceNumber = getSize()-1;
    int sNumber = 0;
    connect(sNumber, sourceNumber, Vertice::infinity(), false);

    return source;
}

std::shared_ptr<Edge> Graph::createReverseEdge(int v_1, int v_2) {
    auto edge = (*vertices[v_1])[v_2];
    auto reverseEdge = vertices[v_2]->createEdge(v_1, 0);

    reverseEdge->setReverseEdge(edge);
    edge->setReverseEdge(reverseEdge);
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
    for(const auto& u: vertices){
        u->setColor(WHITE);
        u->setParentVertice(Vertice::noParent());
    }
    auto s = getS();
    s->setColor(GREY);

    std::queue<std::pair<int, std::shared_ptr<Vertice>>>queue;
    queue.push({0, s});

    while(!queue.empty()){
        auto u = queue.front();
        queue.pop();
        for(const auto& edge: u.second->getEdges()){
            auto v = std::make_pair(edge.first, vertices[edge.first]);
            if(edge.second->getCapacity() == 0 || v.second->getCapacity() == 0){
                continue;
            }
            if(v.second->getColor() == WHITE){
                v.second->setColor(GREY);
                v.second->setParentVertice(u.first);
                queue.push(v);
            }
        }
        u.second->setColor(BLACK);
    }
    //BFS done

    currentFlow = std::numeric_limits<double>::max();
    int v = getTNumber();
    while(vertices[v]->hasParent()){
        int parentV = vertices[v]->getParentVertice();
        currentFlow = std::min({currentFlow, getEdge(parentV, v)->getCapacity(), vertices[v]->getCapacity()});
        v = parentV;
        if( v == 0 ){
            break;
        }
    }
    // v==0 means that we found augmenting path from s to t
    return v == 0;
}

std::shared_ptr<Vertice> Graph::getS() {
    return vertices[0];
}

std::shared_ptr<Edge> Graph::getEdge(int v1, int v2) {
    return (*vertices[v1])[v2];
}

void Graph::synchronizeFlowAndGraph() {
    int v_num = getTNumber();
    do{
        int v_parent = vertices[v_num]->getParentVertice();
        auto edge = (*vertices[v_parent])[v_num];

        vertices[v_num]->reduceCapacity(currentFlow);
        edge->setCapacity(edge->getCapacity() - currentFlow);
        edge->getReverseEdge()->setCapacity(edge->getCapacity() + currentFlow);

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

Graph::Graph(int sourceCount, int valveCount, int receiverCount) {
    createS();

    for(int i=0 ; i<sourceCount; ++i) {
        createSource(0);
    }

    for(int i=0; i<valveCount; ++i){
        addVertice(std::make_shared<Vertice>(0));
    }

    firstReceiverIndex = sourceCount + valveCount + 1;

    createReceivers(firstReceiverIndex, receiverCount);

    createT();

    connectReceiversWithT(firstReceiverIndex, 0);

    flows.resize(receiverCount);
}

const std::vector<std::shared_ptr<Vertice>> &Graph::getVertices() const {
    return vertices;
}

Graph::Graph() {
    firstReceiverIndex = 0;
    currentFlow = 0;
}

int Graph::getSourceCount() {
    return vertices[0]->getEdgesCount();
}

int Graph::getValveCount() {
    return firstReceiverIndex - getSourceCount();
}

int Graph::getReceiverCount() {
    return vertices.size() - firstReceiverIndex - 1;
}

int Graph::getFirstReceiverIndex() const {
    return firstReceiverIndex;
}

std::shared_ptr<Vertice> Graph::createVertice(double capacity, bool isValve) {
    return (isValve) ? createValve(capacity) : createSource(capacity);
}

void Graph::incrementFlow(int index, double value) {
    if(index < 0 || index >= flows.size()){
        throw std::out_of_range("increment flow exception with index="+std::to_string(index)+" and flow.size()="+std::to_string(flows.size()));
    }
    flows[index] += value;
}

void Graph::incrementCurrentFlow(double value) {
    currentFlow += value;
}

std::ostream &operator<<(std::ostream &stream, const Graph &graph) {
    int i = 0;
    double flowSum = 0;
    for (auto flow: graph.getFlows()) {
        stream << std::setw(3) << ++i << ": " << flow << std::endl;
        flowSum += flow;
    }
    stream << "SUM: " << flowSum << std::endl;

    return stream;
}

void Graph::scaleFlows(double maxCapacity) {
    for(double &flow: flows){
        flow /= maxCapacity;
    }
    currentFlow /= maxCapacity;
}

int Graph::getEdgesCount() const {
    return edgesCount;
}




