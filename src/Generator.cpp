//
// Created by Wojtek on 30/11/2019.
//
#include <Generator.h>

using namespace std;

Generator::Generator(int _sourceCount, int _valveCount, int _receiverCount, int _augmentingPathCount,
                     double _averageAugmentingPathLength, double _augmentingPathLengthStandardDeviation)
        : sourceCount(_sourceCount), valveCount(_valveCount), receiverCount(_receiverCount),
          augmentingPathCount(_augmentingPathCount) {
    disconnectedValves = _valveCount;

    graph = Graph(sourceCount, valveCount, receiverCount);

    augmentingPathDistribution = normal_distribution<double>(_averageAugmentingPathLength,
                                                             _augmentingPathLengthStandardDeviation);
    sourceDistribution = uniform_int_distribution<int>(1, sourceCount);
    flowDistribution = uniform_real_distribution<double>(0, 1);
    valveDistribution = uniform_int_distribution<int>(1 + sourceCount, sourceCount + valveCount);
    valveDistribution = uniform_int_distribution<int>(sourceCount + valveCount + 1, graph.getSize() - 2);

}

void Generator::generateGraph() {
    //to stop generating augmenting paths we need all valves connected and augmentingPathCount zeroed
    while (disconnectedValves > 0 || augmentingPathCount > 0) {
        addAugmentingPath();
    }

    //TODO scale graph
}

void Generator::addAugmentingPath() {
    int augmentingPathLength = (int) augmentingPathDistribution(generator);
    int sourceIndex = sourceDistribution(generator);
    double flow = flowDistribution(generator);
    auto vertices = graph.getVertices();

    auto source = vertices[sourceIndex];
    //find first valve
    int valveIndex = nextValveIndex();
    //connect source with first valve
    connectValves(*source, valveIndex, flow);
    //set parents - (it has to be path, so we shouldn't visit valve two times)
    vertices[valveIndex]->setParentVertice(Vertice::noParent());
    //connect rest of valves
    for (int oldValveIndex = valveIndex; augmentingPathLength > 0; --augmentingPathLength, oldValveIndex = valveIndex) {
        int valveIndex = nextValveIndex();
        auto valve1 = vertices[oldValveIndex];
        connectValves(*valve1, valveIndex, flow);
        //set parents
        vertices[valveIndex]->setParentVertice(oldValveIndex);
    }
    //connect last valve with receiver
    int receiverIndex = receiverDistribution(generator);
    connectValves(*(vertices[valveIndex]), receiverIndex, flow);
    //connect receiver with t
    connectValves(*(vertices[receiverIndex]), graph.getTNumber(), flow);
    //set white valves
    while(vertices[valveIndex]->hasParent()){
        vertices[valveIndex]->setColor(WHITE);
        int tmpIndex = vertices[valveIndex]->getParentVertice();
        vertices[valveIndex]->setParentVertice(Vertice::noParent());
        valveIndex = tmpIndex;
    }
}

int Generator::nextValveIndex() {
    auto vertices = graph.getVertices();
    int valveIndex = valveDistribution(generator);
    if (disconnectedValves > 0) {
        while (vertices[valveIndex]->getEdgesCount() > 0 || vertices[valveIndex]->getColor() != WHITE) {
            valveIndex = valveDistribution(generator);
        }
    }

    graph.getVertices()[valveIndex]->setColor(GREY);
    return valveIndex;
}

void Generator::connectValves(Vertice &valve1, int valve2Index, double flow) {
    auto vertices = graph.getVertices();
    auto valve2 = *(vertices[valve2Index]);
    if (valve1.issetEdge(valve2Index)) {
        auto edge = valve1[valve2Index];
        edge.setCapacity(edge.getCapacity() + flow);
    } else {
        valve1.createEdge(valve2Index, flow);
    }
    valve1.incrementCapacity(flow);
    valve2.incrementCapacity(flow);
}
