//
// Created by Amuro on 2018/1/23.
//

#include <jni.h>
#include "LogUtils.h"
#include "NativeAlgorithmBaseSort.h"
#include "NativeArrayUtils.h"

void bubbleSort(JNIEnv *env, jclass type, jintArray origin)
{
    jint *pOrigin = env->GetIntArrayElements(origin, NULL);
    int length = env->GetArrayLength(origin);

    for(int i = length - 1; i > 0; i--)
    {
        int j = 0;
        while(j < i)
        {
            if(pOrigin[j] > pOrigin[j + 1])
            {
                NativeArrayUtils::swap(pOrigin[j], pOrigin[j + 1]);
            }

            j++;
        }
    }

    env->ReleaseIntArrayElements(origin, pOrigin, 0);

}

void selectionSort(JNIEnv* env, jclass type, jintArray origin)
{
    jint* pOrigin = env->GetIntArrayElements(origin, NULL);
    int length = env->GetArrayLength(origin);

    for(int i = 0; i < length - 1; i++)
    {
        int minPos = i;
        for(int j = i + 1;j < length; j++)
        {
            if(pOrigin[minPos] > pOrigin[j])
            {
                minPos = j;
            }
        }

        if(minPos != i)
        {
            NativeArrayUtils::swap(pOrigin[i], pOrigin[minPos]);
        }

    }

    env->ReleaseIntArrayElements(origin, pOrigin, 0);

}

void insertSort(JNIEnv* env, jclass type, jintArray origin)
{
    jint* pOrigin = env->GetIntArrayElements(origin, NULL);
    int length = env->GetArrayLength(origin);

    for(int i = 1; i < length; i++)
    {
        int pos = i - 1;
        int temp = pOrigin[i];
        for(int j = i - 1; j >= 0; j--)
        {
            if(pOrigin[j] > temp)
            {
                pOrigin[j + 1] = pOrigin[j];
                pos = j;
            }
        }

        if(pos != (i - 1))
        {
            NativeArrayUtils::swap(pOrigin[pos], temp);
        }
    }

    env->ReleaseIntArrayElements(origin, pOrigin, 0);
}

void realMerge(int* arr, int left, int mid, int right)
{
    int i = left;
    int j = mid + 1;
    int k = left;

    int length = right - left + 1;
    int* temp = new int[length];
    for(;k < left + length; k++)
    {
        if(i <= mid && j <= right)
        {
            if(arr[i] < arr[j])
            {
                temp[k - left] = arr[i];
                i++;
            }
            else if(arr[i] >= arr[j])
            {
                temp[k - left] = arr[j];
                j++;
            }
        }
        else if(i > mid)
        {
            temp[k - left] = arr[j];
            j++;
        }
        else if(j > right)
        {
            temp[k - left] = arr[i];
            i++;
        }

    }

    for(int x = left; x <= right; x++)
    {
        arr[x] = temp[x - left];
    }

}

void realMerge2(int* arr, int left, int mid, int right)
{
    int length = right - left + 1;
    int temp[length];
    for(int i = left; i <= right;i++)
    {
        temp[i - left] = arr[i];
    }

    int i = left;
    int j = mid + 1;
    for(int k = left; k <= right; k++)
    {
        if(i > mid)
        {
            arr[k] = temp[j - left];
            j++;
        }
        else if(j > right)
        {
            arr[k] = temp[i - left];
            i++;
        }
        else if(temp[i - left] < temp[j - left])
        {
            arr[k] = temp[i - left];
            i++;
        }
        else
        {
            arr[k] = temp[j - left];
            j++;
        }
    }
}

void _mergeSort(int* arr, int left, int right)
{
    if(left >= right)
    {
        return;
    }

    int mid = (left + right) / 2;
    _mergeSort(arr, left, mid);
    _mergeSort(arr, mid + 1, right);
    realMerge(arr, left, mid, right);
}

void mergeSort(JNIEnv* env, jclass type, jintArray origin)
{
    jint* pOrigin = env->GetIntArrayElements(origin, NULL);
    int length = env->GetArrayLength(origin);

    _mergeSort(pOrigin, 0, length - 1);

    env->ReleaseIntArrayElements(origin, pOrigin, 0);

}

int partition(int* arr, int left, int right)
{
    int v = arr[left];

    int j = left;
    for(int i = left + 1; i <= right; i++)
    {
        if(arr[i] < v)
        {
            NativeArrayUtils::swap(arr[j+1], arr[i]);
            j++;
        }
    }

    NativeArrayUtils::swap(arr[left], arr[j]);

    return j;
}

void _quickSort(int* arr, int left, int right)
{
    if(left >= right)
    {
        return;
    }

    int pos = partition(arr, left, right);
    _quickSort(arr, left, pos - 1);
    _quickSort(arr, pos + 1, right);

}

void quickSort(JNIEnv* env, jclass type, jintArray origin)
{
    jint* pOrigin = env->GetIntArrayElements(origin, NULL);
    int length = env->GetArrayLength(origin);

    _quickSort(pOrigin, 0, length - 1);

    env->ReleaseIntArrayElements(origin, pOrigin, 0);
}

void _improvedQuickSort(int* arr, int left, int right)
{
    if(left >= right)
    {
        return;
    }

    int v = arr[left];
    int lt = left;
    int gt = right + 1;
    int i = left + 1;
    while(i < gt)
    {
        if(arr[i] < v)
        {
            NativeArrayUtils::swap(arr[lt+1], arr[i]);
            lt++;
            i++;
        }
        else if(arr[i] > v)
        {
            NativeArrayUtils::swap(arr[gt - 1], arr[i]);
            gt--;
        }
        else
        {
            i++;
        }
    }

    NativeArrayUtils::swap(arr[left], arr[lt]);
    _improvedQuickSort(arr, left, lt - 1);
    _improvedQuickSort(arr, gt, right);
}

void improvedQuickSort(JNIEnv* env, jclass type, jintArray origin)
{
    jint* pOrigin = env->GetIntArrayElements(origin, NULL);
    int length = env->GetArrayLength(origin);

    _improvedQuickSort(pOrigin, 0, length - 1);

    env->ReleaseIntArrayElements(origin, pOrigin, 0);
}

static const char* const registerClassName =
        "com/zhaohui/core/algorithm/AlgorithmBaseSort";

static const JNINativeMethod registerMethods[] = {
        {"bubbleSort", "([I)V", (void*)bubbleSort},
        {"selectionSort", "([I)V", (void*)selectionSort},
        {"insertSort", "([I)V", (void*)insertSort},
        {"mergeSort", "([I)V", (void*)mergeSort},
        {"quickSort", "([I)V", (void*)quickSort},
        {"improvedQuickSort", "([I)V", (void*)improvedQuickSort}

};

int NativeAlgorithmBaseSort::registerNatives(JNIEnv *env)
{
    jclass classForRegister =
            env->FindClass(registerClassName);
    if(classForRegister == NULL)
    {
        LogUtils::w("AlgorithmBaseSort can not find class");
        return -1;
    }

    jint isRegisterSuccess =
            env->RegisterNatives(
                    classForRegister,
                    registerMethods,
                    sizeof(registerMethods) / sizeof(registerMethods[0]));

    if(isRegisterSuccess < 0)
    {
        LogUtils::w("AlgorithmBaseSort can not find methods");
        return -1;
    }

    return 0;

}
