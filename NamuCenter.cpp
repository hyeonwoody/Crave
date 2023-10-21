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
    backStep->Start();

    CNamuStep::NamuPage *frontCurrent = frontStep->m_currentTarget;
    CNamuStep::NamuPage *backCurrent = backStep->m_currentTarget;

    std::map<std::string, int> frontMap;
    std::map<std::string, int> backMap;
    static int cnt = 0;
    while (m_threadStatus != THREAD_INACTIVE)
    {
    
        if (frontCurrent->historyMap.find(frontCurrent->nextPage.front().first) != frontCurrent->historyMap.end())
        {
            std::cout <<"FOUND!"<<cnt++<<std::endl;
        }   
        else
        {
            std::cout << "Not Yet" << cnt++ <<std::endl;
        }
                // for (const auto& pair : frontCurrent->historyMap)
        // {   
        //     std::pair<std::map<std::string,int>::iterator,bool> ret;
        //     ret = frontMap.insert (std::make_pair (pair.first, pair.second));
        //     if ( !ret.second ) {
        //         std::cout << "element " << ret.first->first << "already existed";
        //         std::cout << " with a value of " << ret.first->second << '\n';
        //     }
        // }
    }

    free(frontCurrent);

    this->Close();
    this->Stop();
}