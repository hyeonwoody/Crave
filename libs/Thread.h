
#pragma once
#include <pthread.h>

typedef pthread_t ThreadHandle;

class CThread
{
public:
    ThreadHandle m_hThread;
    bool m_threadActive;
public:
    CThread(const char *sName = NULL);
    virtual void ThreadMain() = 0;

    bool Start();
    bool Stop();
    void Close();
#define THREAD_NAME_MAX 16
    char *m_sName;
};