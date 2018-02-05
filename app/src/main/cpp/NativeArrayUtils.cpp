//
// Created by Amuro on 2018/1/28.
//

#include "NativeArrayUtils.h"
#include "LogUtils.h"

void NativeArrayUtils::swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void NativeArrayUtils::showArray(const char* title, int *arr, int count)
{
    LogUtils::w(title);

    for(int i = 0; i < count; i++)
    {
        LogUtils::w("arr -> %d", arr[i]);
    }
}
