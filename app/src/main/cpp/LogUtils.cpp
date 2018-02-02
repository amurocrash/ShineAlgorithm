//
// Created by Amuro on 2018/1/16.
//

#include <string>
#include "LogUtils.h"

void LogUtils::d(const char *tag, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    __android_log_vprint(ANDROID_LOG_DEBUG, tag, fmt, args);

    va_end(args);
}

void LogUtils::d(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    __android_log_vprint(ANDROID_LOG_DEBUG, DEFAULT_DEBUG_TAG, fmt, args);

    va_end(args);
}

void LogUtils::w(const char *tag, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    __android_log_vprint(ANDROID_LOG_WARN, tag, fmt, args);

    va_end(args);
}

void LogUtils::w(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    __android_log_vprint(ANDROID_LOG_WARN, DEFAULT_DEBUG_TAG, fmt, args);

    va_end(args);
}

void LogUtils::e(const char* tag, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    __android_log_vprint(ANDROID_LOG_ERROR, tag, fmt, args);

    va_end(args);
}

void LogUtils::e(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    __android_log_vprint(ANDROID_LOG_ERROR, DEFAULT_DEBUG_TAG, fmt, args);

    va_end(args);
}

