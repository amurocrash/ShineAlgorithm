//
// Created by didi on 2018/2/5.
//

#ifndef SHINEALGORITHM_DENSEGRAPH_H
#define SHINEALGORITHM_DENSEGRAPH_H

#include <vector>
#include <iostream>
using namespace std;

class DenseGraph
{
private:
    int numOfVertex;
    int numOfEdge;
    bool isDirected;

    vector< vector<bool> > graph;

public:
    static const int ILLEGAL = -1;
    static const int HAS_EDGE = 0;
    static const int NO_EDGE = 1;

    DenseGraph(int numOfVertex, bool isDirected);
    ~DenseGraph();
    int getNumOfVertex();
    int getNumOfEdge();
    int hasEdge(int v, int w);
    void addEdge(int v, int w);

};


#endif //SHINEALGORITHM_DENSEGRAPH_H
