//
// Created by didi on 2018/2/5.
//

#include "SparseGraph.h"

SparseGraph::SparseGraph(int numOfVertex, bool isDirected)
{
    this->numOfVertex = numOfVertex;
    this->numOfEdge = 0;
    this->isDirected = isDirected;

    for(int i = 0; i < numOfVertex; i++)
    {
        graph.push_back(vector<int>());
    }
}

SparseGraph::~SparseGraph()
{
}

int SparseGraph::getNumOfVertex()
{
    return numOfVertex;
}

int SparseGraph::getNumOfEdge()
{
    return numOfEdge;
}

int SparseGraph::hasEdge(int v, int w)
{
    if(v < 0 || v >= numOfVertex)
    {
        return ILLEGAL;
    }

    if(w < 0 || w >= numOfVertex)
    {
        return ILLEGAL;
    }

    for(int i = 0; i < graph[v].size(); i++)
    {
        if(graph[v][i] == w)
        {
            return HAS_EDGE;
        }

    }

    return NO_EDGE;
}

void SparseGraph::addEdge(int v, int w)
{
    int hasEdge = SparseGraph::hasEdge(v, w);

    if(ILLEGAL == hasEdge || HAS_EDGE == hasEdge)
    {
        return;
    }

    graph[v].push_back(w);
    if(v != w && !isDirected)
    {
        graph[w].push_back(v);
    }

    numOfEdge++;

}

void SparseGraph::show()
{
    for(int v = 0; v < numOfVertex; v++)
    {
        for(int w = 0; w < graph[v].size(); w++)
        {
            LogUtils::w("%d, %d", v, graph[v][w]);
        }
    }
}
