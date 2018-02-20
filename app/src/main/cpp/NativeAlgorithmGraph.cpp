//
// Created by didi on 2018/2/5.
//

#include "NativeAlgorithmGraph.h"
#include "LogUtils.h"
#include "DenseGraph.h"
#include "SparseGraph.h"
#include <stack>
#include <queue>

//求连通分量
template <typename Graph>
class Component
{
private:
    Graph* graph;
    bool* visited;
    int* unionId;
    int numOfVertex;
    int count;

    void dfs(int i)
    {
        visited[i] = true;
        unionId[i] = count;

        typename Graph::Iterator itor(graph, i);
        for(int v = itor.begin(); !itor.end(); v = itor.next())
        {
            if(!visited[v])
            {
                dfs(v);
            }
        }
    }

public:
    Component(Graph* g) : graph(g)
    {
        this->numOfVertex = g->getNumOfVertex();
        visited = new bool[numOfVertex];
        unionId = new int[numOfVertex];
        count = 0;

        for(int i = 0; i < numOfVertex; i++)
        {
            visited[i] = false;
            unionId[i] = -1;
        }

        for(int i = 0; i < numOfVertex; i++)
        {
            if(!visited[i])
            {
                dfs(i);
                count++;
            }
        }
    }

    ~Component()
    {
        delete[] visited;
        delete[] unionId;
    }

    int getCount()
    {
        return count;
    }

    bool isConnect(int v, int w)
    {
        if(v < 0 || v >= numOfVertex)
        {
            return false;
        }

        if(w < 0 || w >= numOfVertex)
        {
            return false;
        }

        return unionId[v] == unionId[w];
    }
};

//深度优先遍历
template <typename Graph>
class Path
{
private:
    Graph* graph;
    int numOfVertex;
    //原点
    int vertex;
    bool* visited;
    int* from;

    void dfs(int v)
    {
        visited[v] = true;

        typename Graph::Iterator itor(graph, v);
        for(int nextV = itor.begin(); !itor.end(); nextV = itor.next())
        {
            if(!visited[nextV])
            {
                from[nextV] = v;
                dfs(nextV);
            }
        }
    }

public:
    Path(Graph* g, int vertex)
    {
        this->numOfVertex = g->getNumOfVertex();
        if(vertex < 0 || vertex >= numOfVertex)
        {
            return;
        }

        this->graph = g;
        this->vertex = vertex;

        visited = new bool[numOfVertex];
        from = new int[numOfVertex];
        for(int i = 0; i < numOfVertex; i++)
        {
            visited[i] = false;
            from[i] = -1;
        }

        dfs(vertex);
    }

    ~Path()
    {
        delete[] visited;
        delete[] from;
    }

    bool hasPath(int w)
    {
        if(w < 0 || w >= numOfVertex)
        {
            return false;
        }

        return visited[w];
    }

    int* path(int w, int& size)
    {
        if(w < 0 || w >= numOfVertex)
        {
            return NULL;
        }

        stack<int> stack;
        int p = w;
        while(p != -1)
        {
            stack.push(p);
            p = from[p];
        }

        size = stack.size();
        if(size == 0)
        {
            return NULL;
        }

        int* result = new int[size];
        for(int i = 0; i < size; i++)
        {
            int e = stack.top();
            result[i] = e;
            stack.pop();
        }

        return result;
    }

    void showPath(int w)
    {
        int* result;
        int size;
        result = path(w, size);

        if(result == NULL)
        {
            LogUtils::w("no path");
            return;
        }

        LogUtils::w("Path as below:");
        for(int i = 0; i < size; i++)
        {
            LogUtils::w("node -> %d", result[i]);
        }

    }

    void showFrom()
    {
        for(int i = 0; i < numOfVertex; i++)
        {
            LogUtils::w("from -> %d", from[i]);
        }
    }
};

//广度优先遍历
template <typename Graph>
class ShortestPath
{
private:
    Graph* graph;
    int numOfVertex;
    int vertex;
    bool* visited;
    int* from;
    int* order;

public:
    ShortestPath(Graph* g, int vertex)
    {
        this->numOfVertex = g->getNumOfVertex();
        if(vertex < 0 || vertex >= numOfVertex)
        {
            return;
        }

        this->graph = g;
        this->vertex = vertex;
        visited = new bool[numOfVertex];
        from = new int[numOfVertex];
        order = new int[numOfVertex];

        for(int i = 0; i < numOfVertex; i++)
        {
            visited[i] = false;
            from[i] = -1;
            order[i] = -1;
        }

        queue<int> queue;

        queue.push(vertex);
        visited[vertex] = true;
        order[vertex] = 0;

        while(!queue.empty())
        {
            int v = queue.front();
            queue.pop();

            typename Graph::Iterator itor(graph, v);
            for(int nextV = itor.begin(); !itor.end(); nextV = itor.next())
            {
                if(!visited[nextV])
                {
                    queue.push(nextV);
                    visited[nextV] = true;
                    from[nextV] = v;
                    order[nextV] = order[v] + 1;
                }
            }
        }

    }

    ~ShortestPath()
    {
        delete[] visited;
        delete[] from;
        delete[] order;
    }

    bool hasPath(int w)
    {
        if(w < 0 || w >= numOfVertex)
        {
            return false;
        }

        return visited[w];
    }

    int* path(int w, int& size)
    {
        if(w < 0 || w >= numOfVertex)
        {
            return NULL;
        }

        stack<int> stack;
        int p = w;
        while(p != -1)
        {
            stack.push(p);
            p = from[p];
        }

        size = stack.size();
        if(size == 0)
        {
            return NULL;
        }

        int* result = new int[size];
        for(int i = 0; i < size; i++)
        {
            int e = stack.top();
            result[i] = e;
            stack.pop();
        }

        return result;
    }

    void showPath(int w)
    {
        int* result;
        int size;
        result = path(w, size);

        if(result == NULL)
        {
            LogUtils::w("no path");
            return;
        }

        LogUtils::w("Shortest Path as below:");
        for(int i = 0; i < size; i++)
        {
            LogUtils::w("node -> %d", result[i]);
        }

    }

    void showFrom()
    {
        for(int i = 0; i < numOfVertex; i++)
        {
            LogUtils::w("from -> %d", from[i]);
        }
    }

    int getPathLength(int w)
    {
        if(w < 0 || w >= numOfVertex)
        {
            return -1;
        }

        return order[w];
    }
};


void test(JNIEnv* env, jclass type)
{
    int numOfVertex = 7;
    int numOfEdge = 8;

    int v[] = {0, 0, 0, 0, 3, 3, 4, 4};
    int w[] = {1, 2, 5, 6, 4, 5, 5, 6};

//    int numOfVertex = 13;
//    int numOfEdge = 13;
//
//    int v[] = {0, 4, 0, 9, 6, 5, 0, 11, 9, 0, 7, 9, 5};
//    int w[] = {5, 3, 1, 12, 4, 4, 2, 12, 10, 6, 8, 11, 3};

    SparseGraph* sg = new SparseGraph(numOfVertex, false);
    for(int i = 0;i < numOfEdge; i++)
    {
        sg->addEdge(*(v + i), *(w + i));
    }

    for(int _v = 0; _v < numOfVertex; _v++)
    {
        SparseGraph::Iterator* itor = new SparseGraph::Iterator(sg, _v);
        for (int _w = itor->begin(); !itor->end(); _w = itor->next())
        {
            LogUtils::w("v -> %d connect to %d", _v, _w);
        }

        delete itor;
    }

    Component<SparseGraph>* component = new Component<SparseGraph>(sg);
    LogUtils::w("Component -> %d", component->getCount());
    delete component;

    Path<SparseGraph>* path = new Path<SparseGraph>(sg, 0);
    path->showPath(6);
    delete path;

    ShortestPath<SparseGraph>* sPath = new ShortestPath<SparseGraph>(sg, 0);
    sPath->showPath(6);
    delete sPath;

    delete sg;
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
