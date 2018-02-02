//
// Created by Amuro on 2018/1/16.
//

#ifndef LOGUTILS_H
#define LOGUTILS_H

#include <android/log.h>
#include <stdio.h>
#include <stdarg.h>

#define DEFAULT_DEBUG_TAG "jni" // 这个是自定义的LOG的标识
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__) // 定义LOGF类型

class LogUtils
{
public:
    static void d(const char* tag, const char* fmt, ...);
    static void d(const char* fmt, ...);
    static void w(const char* tag, const char* fmt, ...);
    static void w(const char* fmt, ...);
    static void e(const char* tag, const char* fmt, ...);
    static void e(const char* fmt, ...);
};

#endif //LOGUTILS_H
