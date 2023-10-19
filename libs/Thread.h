
#pragma once
#include <pthread.h>

typedef enum class ThreadStatus
{
    THREAD_INACTIVE = 0,
    THREAD_ACTIVE,
    THREAD_PAUSE,
    THREAD_STOP
} e_ThreadStatus;

typedef pthread_t ThreadHandle;

class CThread
{
public:
    ThreadHandle m_hThread;
    e_ThreadStatus m_threadStatus;
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
};