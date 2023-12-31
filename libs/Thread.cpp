#include "Thread.h"
#include <cstring>

CThread::CThread(const char *sName)
{
    this->m_hThread = 0;
    this->m_sName = NULL;
    this->m_mutex = PTHREAD_MUTEX_INITIALIZER;
    if (sName)
    {
        this->m_sName = new char[THREAD_NAME_MAX];
        strncpy(this->m_sName, sName, THREAD_NAME_MAX);
        this->m_sName[THREAD_NAME_MAX - 1] = '\0';
    }
}

static void *MetaThread(void *opaque)
{
    CThread *instance = reinterpret_cast<CThread *>(opaque);
    instance->m_threadStatus = THREAD_ACTIVE;
    instance->ThreadMain();
    return NULL;
}

bool CThread::Start()
{
    if (this->m_hThread == 0 && pthread_create(&this->m_hThread, NULL, MetaThread, this))
    {
        this->m_hThread = 0;
        return false;
    }
    if (m_sName)
    {
        pthread_setname_np (this->m_hThread, m_sName);
    }
}

bool CThread::Stop()
{
    if (this->m_hThread)
    {
        this->m_threadStatus = THREAD_INACTIVE;
        pthread_join(this->m_hThread, NULL);
    }
    this->m_hThread = 0;
    return true;
}

void CThread::Close()
{
    this->m_hThread = 0;
}