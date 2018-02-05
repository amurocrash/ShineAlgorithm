//
// Created by didi on 2018/2/5.
//

#ifndef SHINEALGORITHM_SPARSEGRAPH_H
#define SHINEALGORITHM_SPARSEGRAPH_H

#include <vector>
#include <iostream>
using namespace std;


class SparseGraph
{
private:
    int numOfVertex;
    int numOfEdge;
    bool isDirected;

    vector< vector<int> > graph;

public:
    static const int ILLEGAL = -1;
    static const int HAS_EDGE = 0;
    static const int NO_EDGE = 1;

    SparseGraph(int numOfVertex, bool isDirected);
    ~SparseGraph();
    int getNumOfVertex();
    int getNumOfEdge();
    int hasEdge(int v, int w);
    void addEdge(int v, int w);
};


#endif //SHINEALGORITHM_SPARSEGRAPH_H
