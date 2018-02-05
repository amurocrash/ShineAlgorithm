//
// Created by didi on 2018/2/5.
//

#include "NativeAlgorithmGraph.h"
#include "LogUtils.h"
#include "DenseGraph.h"

void test(JNIEnv* env, jclass type)
{

}

static const char* const registerClassName =
        "com/zhaohui/core/algorithm/AlgorithmGraph";

static const JNINativeMethod registerMethods[] = {
        {"test", "()V", (void*)test},
};

int NativeAlgorithmGraph::registerNatives(JNIEnv *env)
{
    jclass registerClass = env->FindClass(registerClassName);

    if(registerClass == NULL)
    {
        LogUtils::w("Algorithm Union Find can not find class");
        return -1;
    }

    jint isRegisterSuccess = env->RegisterNatives(
            registerClass,
            registerMethods,
            sizeof(registerMethods) / sizeof(registerMethods[0]));

    if(isRegisterSuccess < 0)
    {
        LogUtils::w("Algorithm Union Find can not find methods");
        return -1;
    }

    return 0;

}

//#include <vector>
//#include <iostream>
//using namespace std;
//
////稠密图
//class DenseGraph
//{
//private:
//    int numOfVertex;
//    int numOfEdge;
//    bool isDirected;
//
//    vector<vector<bool>> graph;
//
//public:
//    DenseGraph(int numOfVertex, bool isDirected)
//    {
//        this->numOfVertex = numOfVertex;
//        this->numOfEdge = 0;
//        this->isDirected = isDirected;
//
//        for(int i = 0; i < numOfVertex; i++)
//        {
//            graph.push_back(vector<bool>(numOfVertex, false));
//        }
//    }
//
//    ~DenseGraph()
//    {
//
//    }
//
//    int getNumOfVertex()
//    {
//        return numOfVertex;
//    }
//
//    int getNumOfEdge()
//    {
//        return numOfEdge;
//    }
//
//    static const int ILLEGAL = -1;
//    static const int HAS_EDGE = 0;
//    static const int NO_EDGE = 1;
//
//    int hasEdge(int v, int w)
//    {
//        if(v < 0 || v >= numOfVertex)
//        {
//            return ILLEGAL;
//        }
//
//        if(w < 0 || w >= numOfVertex)
//        {
//            return ILLEGAL;
//        }
//
//        if(graph[v][w])
//        {
//            return HAS_EDGE;
//        }
//        else
//        {
//            return NO_EDGE;
//        }
//    }
//
//    void addEdge(int v, int w)
//    {
//        if(hasEdge(v, w) == ILLEGAL)
//        {
//            return;
//        }
//
//        if(hasEdge(v, w) == HAS_EDGE)
//        {
//            return;
//        }
//
//        graph[v][w] = true;
//        if(!isDirected)
//        {
//            graph[w][v] = true;
//        }
//
//        numOfEdge++;
//    }
//};