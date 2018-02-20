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

    class Iterator
    {
    private:
        DenseGraph& _graph;
        int vertex;
        int index;

    public:
        Iterator(DenseGraph &g, int vertex):_graph(g)
        {
            this->vertex = vertex;
            this->index = 0;
        }

        int begin()
        {
            index = -1;
            return next();
        }

        int next()
        {
            for(index += 1; index < _graph.graph[vertex].size(); index++)
            {
                if(_graph.graph[vertex][index])
                {
                    return index;
                }
            }

            return -1;
        }

        bool end()
        {
            return index >= _graph.getNumOfVertex();
        }
    };

};


#endif //SHINEALGORITHM_DENSEGRAPH_H
