#include <jni.h>
#include "LogUtils.h"
#include "NativeAlgorithmBaseSort.h"
#include "NativeAlgorithmHeapSort.h"
#include "NativeAlgorithmBinarySearch.h"
#include "NativeAlgorithmUnionFind.h"
#include "NativeAlgorithmGraph.h"

extern "C"
{


JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved)
{
    JNIEnv* env = NULL;

    jint isJniOk = vm->GetEnv((void**)&env, JNI_VERSION_1_6);
    if(isJniOk != JNI_OK)
    {
        return -1;
    }

    LogUtils::w("JNI_ON_LOAD_GET_ENV_OK");

    NativeAlgorithmBaseSort::registerNatives(env);
    NativeAlgorithmHeapSort::registerNatives(env);
    NativeAlgorithmBinarySearch::registerNatives(env);
    NativeAlgorithmUnionFind::registerNatives(env);
    NativeAlgorithmGraph::registerNatives(env);

    LogUtils::w("JNI_On_LOAD_Finish");
    return JNI_VERSION_1_6;
}

}
