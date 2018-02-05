//
// Created by Amuro on 2018/1/28.
//

#ifndef SHINEALGORITHM_NATIVEARRAYUTILS_H
#define SHINEALGORITHM_NATIVEARRAYUTILS_H

#include <jni.h>

class NativeArrayUtils
{

public:
    static void swap(int &a, int &b);
    static void showArray(const char* title, int *arr, int count);
};


#endif //SHINEALGORITHM_NATIVEARRAYUTILS_H
