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

    CNamuStep::NamuPage *frontCurrent = frontStep->m_currentTarget;

    std::map<std::string, int> frontMap;
    std::map<std::string, int> backMap;
    while (m_threadStatus != e_ThreadStatus::THREAD_INACTIVE)
    {

        pthread_mutex_lock(&frontStep->m_mutex);
        // for (const auto& pair : frontCurrent->historyMap)
        // {   
        //     std::pair<std::map<std::string,int>::iterator,bool> ret;
        //     ret = frontMap.insert (std::make_pair (pair.first, pair.second));
        //     if ( !ret.second ) {
        //         std::cout << "element " << ret.first->first << "already existed";
        //         std::cout << " with a value of " << ret.first->second << '\n';
        //     }
        // }
        pthread_mutex_unlock(&frontStep->m_mutex);
    }

    free(frontCurrent);

    this->Close();
    this->Stop();
}