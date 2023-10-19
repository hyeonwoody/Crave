#include <thread>

#include "NamuCenter.h"


bool CNamuCenter::AddPage()
{
    return true;
}

bool CNamuCenter::Found()
{
    return false;
}

void CNamuCenter::Close()
{
    if (frontStep)
    {
        delete (frontStep);
        frontStep = nullptr;
    }

    if (backStep)
        delete (backStep);
        backStep = nullptr;
}

void CNamuCenter::ThreadMain()
{   
    frontStep->Start();

    CNamuStep::NamuPage *frontCurrent = frontStep->currentTarget;
    CNamuStep::NamuPage *backCurrent = frontStep->currentTarget;

    std::map<std::string, int> frontMap;
    std::map<std::string, int> backMap;
    while (m_threadStatus != e_ThreadStatus::THREAD_INACTIVE)
    {

        pthread_mutex_lock(&frontStep->m_mutex);
        for (const auto& pair : frontCurrent->m_link)
        {
            frontMap[pair.first] = pair.second;
        }
        pthread_mutex_unlock(&frontStep->m_mutex);
    }
    this->Close();
    this->Stop();
}