//
// Created by Amuro on 2018/1/26.
//

#include "NativeAlgorithmHeapSort.h"
#include "LogUtils.h"
#include "NativeArrayUtils.h"

/**
 * array's index from 1 not 0;
 */
class MaxHeap
{
private:
    int* data;
    int count;
    int capacity;

    void shiftUp(int pos)
    {
        int parentIndex = pos / 2;

        while(parentIndex > 0 && data[parentIndex] < data[pos])
        {
            NativeArrayUtils::swap(data[pos], data[parentIndex]);
            pos = parentIndex;
            parentIndex = pos / 2;
        }
    }

    void shiftDown(int pos)
    {
        while(2 * pos <= count)
        {
            int leftChildIndex = 2 * pos;
            int rightChildIndex = leftChildIndex + 1;
            int result = leftChildIndex;
            if(rightChildIndex <= count && data[rightChildIndex] > data[leftChildIndex])
            {
                result = rightChildIndex;
            }

            if(data[pos] >= data[result])
            {
                break;
            }

            NativeArrayUtils::swap(data[pos], data[result]);
            pos = result;
        }
    }

public:
    MaxHeap(int capacity)
    {
        data = new int[capacity + 1];
        this->capacity = capacity;
        count = 0;
    }

    MaxHeap(int* arr, int length)
    {
        data = new int[length + 1];
        for(int i = 0; i < length;i++)
        {
            data[i + 1] = arr[i];
        }
        count = length;
        capacity = length;

        for(int i = count/ 2; i >= 1; i--)
        {
            shiftDown(i);
        }
    }

    ~MaxHeap()
    {
        delete[] data;
    }

    int size()
    {
        return count;
    }

    bool isEmpty()
    {
        return count == 0;
    }

    int insert(int d)
    {
        if(count >= capacity)
        {
            return false;
        }

        data[count + 1] = d;
        count++;
        shiftUp(count);

        return true;
    }

    int extract()
    {
        int ret = data[1];
        NativeArrayUtils::swap(data[1], data[count]);
        count--;
        shiftDown(1);

        return ret;
    }

    void showData()
    {
        for(int i = 1; i <= count; i++)
        {
            LogUtils::w("Data in max heap is -> %d", data[i]);
        }

    }
};

class IndexMaxHeap
{
private:
    int *data;
    int *index;
    int count;
    int capacity;

    void shiftUp(int pos)
    {
        int parentIndex = pos / 2;

        while (parentIndex > 0 && data[index[parentIndex]] < data[index[pos]])
        {
            NativeArrayUtils::swap(index[parentIndex], index[pos]);
            pos = parentIndex;
            parentIndex = pos / 2;
        }
    }

    void shiftDown(int pos)
    {
        while(pos * 2 <= count)
        {
            int leftChildIndex = pos * 2;
            int rightChildIndex = leftChildIndex + 1;
            int result = leftChildIndex;

            if(rightChildIndex <= count &&
                    data[index[rightChildIndex]] > data[index[leftChildIndex]])
            {
                result = rightChildIndex;
            }

            if(data[index[pos]] >= data[index[result]])
            {
                break;
            }

            NativeArrayUtils::swap(index[pos], index[result]);
            pos = result;

        }
    }

public:
    IndexMaxHeap(int capacity) {
        this->capacity = capacity;
        this->count = 0;
        data = new int[capacity + 1];
        index = new int[capacity + 1];
    }

    ~IndexMaxHeap() {
        delete[] data;
        delete[] index;
    }

    int size() {
        return count;
    }

    bool isEmpty() {
        return count == 0;
    }

    int insert(int d) {
        if (count >= capacity) {
            return false;
        }

        count++;
        data[count] = d;
        index[count] = count;
        shiftUp(count);

        return true;
    }

    int extract()
    {
        int ret = data[index[1]];
        NativeArrayUtils::swap(index[1], index[count]);
        count--;
        shiftDown(1);

        return ret;
    }

    void showData()
    {
        for(int i = 1; i <= count; i++)
        {
            LogUtils::w("Data in index max heap is -> %d", data[index[i]]);
        }

    }
};

void sortNormal(JNIEnv* env, jclass type, jintArray origin)
{
    int length = env->GetArrayLength(origin);
    if(origin == NULL || length <= 1)
    {
        return;
    }

    jint* pOrigin = env->GetIntArrayElements(origin, NULL);
    MaxHeap* maxHeap = new MaxHeap(length);
    for(int i = 0; i < length; i++)
    {
        maxHeap->insert(pOrigin[i]);
    }

    for(int i = length - 1; i >= 0; i--)
    {
        pOrigin[i] = maxHeap->extract();
    }

    env->ReleaseIntArrayElements(origin, pOrigin, 0);

}

void sortHeapify(JNIEnv* env, jclass type, jintArray origin)
{
    int length = env->GetArrayLength(origin);
    if(origin == NULL || length <= 1)
    {
        return;
    }

    jint* pOrigin = env->GetIntArrayElements(origin, NULL);

    MaxHeap* maxHeap = new MaxHeap(pOrigin, length);
    for(int i = length - 1; i >= 0; i--)
    {
        pOrigin[i] = maxHeap->extract();
    }

    env->ReleaseIntArrayElements(origin, pOrigin, 0);

}

void sortIndexHeap(JNIEnv* env, jclass type, jintArray origin)
{
    int length = env->GetArrayLength(origin);
    if(origin == NULL || length <= 1)
    {
        return;
    }

    jint* pOrigin = env->GetIntArrayElements(origin, NULL);

    IndexMaxHeap* indexMaxHeap = new IndexMaxHeap(length);
    for(int i = 0; i < length; i++)
    {
        indexMaxHeap->insert(pOrigin[i]);
    }

    for(int i = length - 1; i >= 0; i--)
    {
        pOrigin[i] = indexMaxHeap->extract();
    }

    env->ReleaseIntArrayElements(origin, pOrigin, 0);

}

static const char* const registerClassName =
        "com/zhaohui/core/algorithm/AlgorithmHeapSort";

static const JNINativeMethod registerMethods[] = {
        {"sortNormal", "([I)V", (void*)sortNormal},
        {"sortHeapify", "([I)V", (void*)sortHeapify},
        {"sortIndexHeap", "([I)V", (void*)sortIndexHeap}
};

int NativeAlgorithmHeapSort::registerNatives(JNIEnv *env)
{
    jclass classForRegister = env->FindClass(registerClassName);

    if(classForRegister == NULL)
    {
        LogUtils::w("Algorithm heap sort can not find class");
        return -1;
    }

    jint isRegisterSuccess = env->RegisterNatives(
            classForRegister,
            registerMethods,
            sizeof(registerMethods) / sizeof(registerMethods[0]));

    if(isRegisterSuccess < 0)
    {
        LogUtils::w("Algorithm heap sort can not find methods");
        return -1;
    }

    return 0;
}