//
// Created by Wojtek on 30/11/2019.
//
#include <Generator.h>

using namespace std;

Generator::Generator(int _sourceCount, int _valveCount, int _receiverCount, int _augmentingPathCount,
                     double _averageAugmentingPathLength, double _augmentingPathLengthStandardDeviation)
        : sourceCount(_sourceCount), valveCount(_valveCount), receiverCount(_receiverCount),
          augmentingPathCount(_augmentingPathCount),
          graph(_sourceCount, _valveCount, _receiverCount) {

    disconnectedValves = _valveCount;

    augmentingPathDistribution = normal_distribution<double>(_averageAugmentingPathLength,
                                                             _augmentingPathLengthStandardDeviation);
    sourceDistribution = uniform_int_distribution<int>(1, sourceCount);
    flowDistribution = uniform_real_distribution<double>(0, 1);
    valveDistribution = uniform_int_distribution<int>(1 + sourceCount, sourceCount + valveCount);
    receiverDistribution = uniform_int_distribution<int>(sourceCount + valveCount + 1, graph.getSize() - 2);

}

void Generator::generateGraph() {
    //to stop generating augmenting paths we need all valves connected and augmentingPathCount zeroed
    while (disconnectedValves > 0 || augmentingPathCount-- > 0) {
        addAugmentingPath();
    }

    // scale graph capacities to [0-1]
    // O(2(V+E))
    scaleCapacity(getMaxCapacity());
}



void Generator::addAugmentingPath() {
    // RANDOM GENERATION
    int augmentingPathLength = (int) augmentingPathDistribution(generator);
    int sourceIndex = sourceDistribution(generator);
    double flow = flowDistribution(generator);

    // INITIALIZATION
    auto vertices = graph.getVertices();
    auto source = vertices[sourceIndex];
    // connect SOURCE <-> VALVE1
    int valveIndex = nextValveIndex();
    connectValves(*source, valveIndex, flow);
    vertices[valveIndex]->setParentVertice(Vertice::noParent());
    // connect VALVES
    for (int oldValveIndex = valveIndex; augmentingPathLength > 0; --augmentingPathLength, oldValveIndex = valveIndex) {
        // get two valves
        auto valve1 = vertices[oldValveIndex];
        valveIndex = nextValveIndex();

        // connect + setparent
        connectValves(*valve1, valveIndex, flow);
        vertices[valveIndex]->setParentVertice(oldValveIndex);
    }
    //connect last valve with receiver
    int receiverIndex = receiverDistribution(generator);
    connectValves(*(vertices[valveIndex]), receiverIndex, flow);
    //connect receiver with t
    connectValves(*(vertices[receiverIndex]), graph.getTNumber(), flow);

    // RESET COLORS
    while(valveIndex != Vertice::noParent()){
        vertices[valveIndex]->setColor(WHITE);
        int tmpIndex = vertices[valveIndex]->getParentVertice();
        vertices[valveIndex]->setParentVertice(Vertice::noParent());
        valveIndex = tmpIndex;
    }
}

int Generator::nextValveIndex() {
    auto vertices = graph.getVertices();
    int valveIndex = disconnectedValveIndex;
    // if left disconnected then we search for disconnected, and it must be white
    if(disconnectedValves > 0){
        --disconnectedValves;
        while(vertices[valveIndex]->isConnected() || vertices[valveIndex]->getColor() != WHITE){
            ++valveIndex;
        }
        disconnectedValveIndex = valveIndex + 1;
    }
    else {
        do {
            valveIndex = valveDistribution(generator);
        } while (vertices[valveIndex]->getColor() != WHITE);
    }

    // it is used by our augmenting path, so it should be grey
    graph.getVertices()[valveIndex]->setColor(GREY);
    return valveIndex;
}

void Generator::connectValves(Vertice &valve1, int valve2Index, double flow) {
    auto vertices = graph.getVertices();
    auto &valve2 = *(vertices[valve2Index]);
    if (valve1.issetEdge(valve2Index)) {
        auto edge = valve1[valve2Index];
        edge.setCapacity(edge.getCapacity() + flow);
    } else {
        valve1.createEdge(valve2Index, flow);
    }
    valve1.incrementCapacity(flow);
    valve2.incrementCapacity(flow);
}

double Generator::getMaxCapacity() {
    double maxCapacity = 0;
    for(auto v: graph.getVertices()){
        if(v->getCapacity() != Vertice::infinity() && v->getCapacity() > maxCapacity){
            maxCapacity = v->getCapacity();
        }
        for(auto e: v->getEdges()){
            if(e.second->getCapacity() != Vertice::infinity() && e.second->getCapacity() > maxCapacity){
                maxCapacity = e.second->getCapacity();
            }
        }
    }
    return maxCapacity;
}

void Generator::scaleCapacity(double maxCapacity){
    for(auto v: graph.getVertices()){
        v->scaleCapacity(maxCapacity);
        for(auto e: v->getEdges()){
            e.second->scaleCapacity(maxCapacity);
        }
    }
}

/*
     (liczba źródeł) 2
     (liczba zaworów) 2
     (liczba punktów odbioru) 2
     (w1) 3 c13 4 c14
     (w2) 4 c24
     (w3) c3 5 c35
     (w4) c4 5 c45 6 c46
 */
ostream &operator<<(ostream &str, const Generator &generator) {
    auto graph = generator.graph;
    str << generator.sourceCount   << endl;
    str << generator.valveCount    << endl;
    str << generator.receiverCount << endl;

    auto firstValveIt = graph.getVertices().begin() + (graph.getSourceCount() + 1);
    // SOURCES
    for(auto sourceIt = graph.getVertices().begin() + 1; sourceIt != firstValveIt; ++sourceIt){
        for(auto edge: (*sourceIt)->getEdges()){
            str << edge.first << ' ' << edge.second->getCapacity() << ' ';
            // it is allowed to push space at the end, because Controller#load_data gets all line and extracts it to stringstream
        }
        str << endl;
    }

    auto firstReceiverIt = graph.getVertices().begin() + graph.getFirstReceiverIndex();
    // VALVES
    for(auto valveIt = firstValveIt; valveIt != firstReceiverIt; ++valveIt){
        str << (*valveIt)->getCapacity() << ' ';

        for(auto edge: (*valveIt)->getEdges()){
            str << edge.first << ' ' << edge.second->getCapacity() << ' ';
        }
        str << endl;
    }
    return str;
}
