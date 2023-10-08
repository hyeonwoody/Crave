
#pragma once
#include <pthread.h>

typedef pthread_t ThreadHandle;

class CThread
{
private:
    ThreadHandle m_hThread;

public:
    CThread(const char *sName = NULL);
    virtual void ThreadMain() = 0;

    bool Start();
    void Stop();
    void Close();
#define THREAD_NAME_MAX 16
    char *m_sName;
};