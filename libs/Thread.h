
#pragma once
#include <pthread.h>

enum EThreadStatus
{
    THREAD_INACTIVE = 0,
    THREAD_ACTIVE,
    THREAD_PAUSE,
    THREAD_STOP
};

typedef pthread_t ThreadHandle;

class CThread
{
public:
    ThreadHandle m_hThread;
    EThreadStatus m_threadStatus;
public:
    CThread(const char *sName = NULL);
    virtual void ThreadMain() = 0;

    bool Start();
    bool Stop();
    void Close();
#define THREAD_NAME_MAX 16
    char *m_sName;
public:
    pthread_mutex_t m_mutex;
    pthread_cond_t m_cond;
};