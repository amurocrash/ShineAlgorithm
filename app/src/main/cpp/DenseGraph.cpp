//
// Created by didi on 2018/2/5.
//

#include "DenseGraph.h"

DenseGraph::DenseGraph(int numOfVertex, bool isDirected)
{
    this->numOfVertex = numOfVertex;
    this->numOfEdge = 0;
    this->isDirected = isDirected;

    for(int i = 0; i < numOfVertex; i++)
    {
        graph.push_back(vector<bool>(numOfVertex, false));
    }
}

DenseGraph::~DenseGraph()
{

}

int DenseGraph::getNumOfVertex()
{
    return numOfVertex;
}

int DenseGraph::getNumOfEdge()
{
    return numOfEdge;
}

int DenseGraph::hasEdge(int v, int w)
{
    if(v < 0 || v >= numOfVertex)
    {
        return ILLEGAL;
    }

    if(w < 0 || w >= numOfVertex)
    {
        return ILLEGAL;
    }

    if(graph[v][w])
    {
        return HAS_EDGE;
    }
    else
    {
        return NO_EDGE;
    }
}

void DenseGraph::addEdge(int v, int w)
{

    int hasEdge = DenseGraph::hasEdge(v, w);
    if(hasEdge == ILLEGAL)
    {
        return;
    }

    if(hasEdge == HAS_EDGE)
    {
        return;
    }

    graph[v][w] = true;
    if(!isDirected)
    {
        graph[w][v] = true;
    }

    numOfEdge++;
}