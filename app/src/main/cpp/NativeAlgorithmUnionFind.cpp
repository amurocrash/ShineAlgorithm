//
// Created by didi on 2018/2/4.
//

#include "NativeAlgorithmUnionFind.h"
#include "LogUtils.h"
#include "NativeArrayUtils.h"
#include <ctime>
#include <iostream>
#include <cstdlib>

class UnionFind1
{
private:
    int* id;
    int count;

    bool isValid(int p)
    {
        if(p < 0 || p >= count)
        {
            return false;
        }

        return true;
    }

public:
    UnionFind1(int count)
    {
        this->count = count;
        id = new int[count];
        for(int i = 0; i < count; i++)
        {
            id[i] = i;
        }
    }

    ~UnionFind1()
    {
        delete [] id;
    }

    int find(int p)
    {
        if(!isValid(p))
        {
            return -1;
        }

        return id[p];
    }

    bool isConnect(int p, int q)
    {
        int pId = find(p);
        int qId = find(q);
        if(pId == -1 || qId == -1)
        {
            return false;
        }

        return pId == qId;
    }

    void unionElements(int p, int q)
    {
        int pId = find(p);
        int qId = find(q);

        if(pId == -1 || qId == -1)
        {
            return;
        }

        if(pId == qId)
        {
            return;
        }

        for(int i = 0; i < count; i++)
        {
            if(id[i] == pId)
            {
                id[i] = qId;
            }
        }
    }

    void show()
    {
        NativeArrayUtils::showArray("------------", id, count);
    }

};

//improved by node
class UnionFind2
{
private:
    int* id;
    int count;

    bool isValid(int p)
    {
        if(p < 0 || p >= count)
        {
            return false;
        }

        return true;
    }

public:
    UnionFind2(int count)
    {
        this->count = count;
        id = new int[count];
        for(int i = 0; i < count; i++)
        {
            id[i] = i;
        }
    }

    ~UnionFind2()
    {
        delete[] id;
    }

    int find(int p)
    {
        if(!isValid(p))
        {
           return -1;
        }

        while(p != id[p])
        {
            p = id[p];
        }

        return p;

    }

    bool isConnect(int p, int q)
    {
        int pRoot = find(p);
        int qRoot = find(q);

        if(pRoot == -1 || qRoot == -1)
        {
            return false;
        }

        return pRoot == qRoot;
    }

    void unionElements(int p, int q)
    {
        int pRoot = find(p);
        int qRoot = find(q);

        if(pRoot == -1 || qRoot == -1)
        {
            return;
        }

        if(pRoot == qRoot)
        {
            return;
        }

        id[pRoot] = qRoot;
    }
};

//improved by node and size
class UnionFind3
{
private:
    int* id;
    int* size;
    int count;

    bool isValid(int p)
    {
        if(p < 0 || p >= count)
        {
            return false;
        }

        return true;
    }

public:
    UnionFind3(int count)
    {
        this->count = count;
        id = new int[count];
        size = new int[count];
        for(int i = 0; i < count; i++)
        {
            id[i] = i;
            size[i] = 1;
        }
    }

    ~UnionFind3()
    {
        delete[] id;
        delete[] size;
    }

    int find(int p)
    {
        if(!isValid(p))
        {
            return -1;
        }

        while(p != id[p])
        {
            p = id[p];
        }

        return p;
    }

    bool isConnect(int p, int q)
    {
        int pRoot = find(p);
        int qRoot = find(q);
        if(pRoot == -1 || qRoot == -1)
        {
            return false;
        }

        return pRoot == qRoot;
    }

    void unionElements(int p, int q)
    {
        int pRoot = find(p);
        int qRoot = find(q);

        if(pRoot == -1 || qRoot == -1)
        {
            return;
        }

        if(pRoot == qRoot)
        {
            return;
        }

        if(size[pRoot] > size[qRoot])
        {
            id[qRoot] = pRoot;
            size[pRoot] += size[qRoot];
        }
        else
        {
            id[pRoot] = qRoot;
            size[qRoot] += size[pRoot];
        }

    }
};

class UnionFind4
{
private:
    int* id;
    int* rank;
    int count;

    bool isValid(int p)
    {
        if(p < 0 || p >= count)
        {
            return false;
        }

        return true;
    }

public:
    UnionFind4(int count)
    {
        this->count = count;
        id = new int[count];
        rank = new int[count];

        for(int i = 0; i < count; i++)
        {
            id[i] = i;
            rank[i] = 1;
        }
    }

    ~UnionFind4()
    {
        delete[] id;
        delete[] rank;
    }

    int find(int p)
    {
        if(!isValid(p))
        {
            return -1;
        }

        while(p != id[p])
        {
            id[p] = id[id[p]];
            p = id[p];
        }

        return p;
    }

    bool isConnect(int p, int q)
    {
        int pRoot = find(p);
        int qRoot = find(q);

        if(pRoot == -1 || qRoot == -1)
        {
            return false;
        }

        return pRoot == qRoot;
    }

    void unionElements(int p, int q)
    {
        int pRoot = find(p);
        int qRoot = find(q);

        if(pRoot == -1 || qRoot == -1)
        {
            return;
        }

        if(pRoot == qRoot)
        {
            return;
        }

        if(rank[pRoot] > rank[qRoot])
        {
            id[qRoot] = pRoot;
        }
        else if(rank[pRoot] < rank[qRoot])
        {
            id[pRoot] = qRoot;
        }
        else
        {
            id[pRoot] = qRoot;
            rank[qRoot] += 1;
        }

    }

};

static int n = 10000;

void unionFindBase(JNIEnv* env, jclass type)
{
    srand((unsigned)time(NULL));


    UnionFind1 uf = UnionFind1(n);
    time_t startTime = clock();
    for(int i = 0; i < n; i++)
    {
        int a = rand() % n;
        int b = rand() % n;
        uf.unionElements(a, b);
    }

    for(int i = 0; i < n; i++)
    {
        int a = rand() % n;
        int b = rand() % n;
        uf.isConnect(a, b);
    }

    time_t endTime = clock();

    LogUtils::w("union find base cost time %lf", double(endTime - startTime)/CLOCKS_PER_SEC);

}

void unionFindPro(JNIEnv* env, jclass type)
{
    srand((unsigned)time(NULL));

    UnionFind2 uf = UnionFind2(n);
    time_t startTime = clock();
    for(int i = 0; i < n; i++)
    {
        int a = rand() % n;
        int b = rand() % n;
        uf.unionElements(a, b);
    }

    for(int i = 0; i < n; i++)
    {
        int a = rand() % n;
        int b = rand() % n;
        uf.isConnect(a, b);
    }

    time_t endTime = clock();

    LogUtils::w("union find pro cost time %lf", double(endTime - startTime)/CLOCKS_PER_SEC);
}

void unionFindProBySize(JNIEnv* env, jclass type)
{
    srand((unsigned)time(NULL));

    UnionFind3 uf = UnionFind3(n);
    time_t startTime = clock();
    for(int i = 0; i < n; i++)
    {
        int a = rand() % n;
        int b = rand() % n;
        uf.unionElements(a, b);
    }

    for(int i = 0; i < n; i++)
    {
        int a = rand() % n;
        int b = rand() % n;
        uf.isConnect(a, b);
    }

    time_t endTime = clock();

    LogUtils::w("union find pro by size cost time %lf", double(endTime - startTime)/CLOCKS_PER_SEC);
}

void unionFindProByRank(JNIEnv* env, jclass type)
{
    srand((unsigned)time(NULL));

    UnionFind4 uf = UnionFind4(n);
    time_t startTime = clock();
    for(int i = 0; i < n; i++)
    {
        int a = rand() % n;
        int b = rand() % n;
        uf.unionElements(a, b);
    }

    for(int i = 0; i < n; i++)
    {
        int a = rand() % n;
        int b = rand() % n;
        uf.isConnect(a, b);
    }

    time_t endTime = clock();

    LogUtils::w("union find pro by rank cost time %lf", double(endTime - startTime)/CLOCKS_PER_SEC);
}

static const char* const registerClassName =
        "com/zhaohui/core/algorithm/AlgorithmUnionFind";

static const JNINativeMethod registerMethods[] = {
        {"unionFindBase", "()V", (void*)unionFindBase},
        {"unionFindPro", "()V", (void*)unionFindPro},
        {"unionFindProBySize", "()V", (void*)unionFindProBySize},
        {"unionFindProByRank", "()V", (void*)unionFindProByRank}
};

int NativeAlgorithmUnionFind::registerNatives(JNIEnv *env)
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