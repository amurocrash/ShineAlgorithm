//
// Created by didi on 2018/2/5.
//

#ifndef SHINEALGORITHM_SPARSEGRAPH_H
#define SHINEALGORITHM_SPARSEGRAPH_H

#include <vector>
#include <iostream>
#include "LogUtils.h"

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
    void show();

    class Iterator
    {
    private:
        SparseGraph* _graph;
        int vertex;
        int index;

    public:
        Iterator(SparseGraph* g, int vertex):_graph(g)
        {
            this->vertex = vertex;
            this->index = 0;
        }

        int begin()
        {
            index = 0;
            int size = _graph->graph[vertex].size();
//            LogUtils::w("size -> %d", size);
            if(size > 0)
            {
                int b = _graph->graph[vertex][0];
//                LogUtils::w("b -> %d", b);
                return b;
            }

            return -1;
        }

        int next()
        {
            index++;

            if(index < _graph->graph[vertex].size())
            {
                return _graph->graph[vertex][index];
            }

            return -1;
        }

        bool end()
        {
            return index >= _graph->graph[vertex].size();
        }
    };
};


#endif //SHINEALGORITHM_SPARSEGRAPH_H
