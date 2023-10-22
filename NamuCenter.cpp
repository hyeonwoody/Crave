

#include "NamuCenter.h"
#include <stack>
#include <queue>
#include <thread>
#include <chrono>

#define _FRONTBACK 2



void CNamuCenter::Stop()
{
    if (frontStep)
    {
        frontStep->Stop();
        delete (frontStep);
        frontStep = nullptr;
    }
    if (backStep)
    {
        backStep->Stop();
        delete (backStep);
        backStep = nullptr;
    }
    m_threadStatus = THREAD_INACTIVE;
}

void CNamuCenter::Close()
{
    if (frontStep)
    {
        frontStep->Close();
    }

    if (backStep)
    {
        backStep->Close();
    }
}

bool CNamuCenter::checkElement (std::string tmpElement)
{
    for (auto& it : finalResult)
    {
        for (size_t i=0; i <it.size(); ++i)
        {
            if (tmpElement == it[i])
            {
                return true;
            }
        }
    }
    return false;
}

bool CNamuCenter::resultAlreadyExist(std::vector<std::string> tmpResult) {
    for (const auto& final : finalResult) {
        if (std::equal(final.begin(), final.end(), tmpResult.begin())) {
            return true;
        }
    }

    return false;
}
void CNamuCenter::ThreadMain()
{   
#if _FRONTBACK == 2
    frontStep->Start();
    backStep->Start();

    while (m_threadStatus != THREAD_INACTIVE)
    {
        int a = 0;
    }

#elif _FRONTBACK == 1
    frontStep->Start();
    backStep->Start();

    CNamuStep::NamuPage *frontCurrent = frontStep->m_currentTarget;
    CNamuStep::NamuPage *backCurrent = backStep->m_currentTarget;

    std::map<std::string, std::string> frontMap;
    std::map<std::string, std::string> backMap;
    static int cnt = 0;
    while (m_threadStatus != THREAD_INACTIVE)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        if (finalResult.size() > n_route)
        {
            break;
        }
        for (const auto & pair : frontCurrent->historyMap)
        {
            frontMap.insert(pair);
        }
        for (const auto & pair : backCurrent->historyMap)
        {
            backMap.insert(pair);
        }
            
        for (const auto & pair : backMap)
        {
            if (finalResult.size() > n_route)
            {
                break;
            }
            if (frontMap.find(pair.first) != frontMap.end())
            {
                std::cout <<"FOUND!"<<cnt++<<std::endl;
                                
                std::string frontTarget = frontMap[pair.first];
                if (checkElement (frontTarget))
                {
                    continue;
                }
                std::string backTarget = pair.first;
                
                std::stack <std::string> tmpFront;
                std::vector <std::string> tmpResult;
            
                int a = 0;
                
                tmpResult.push_back (origin);
                do {
                    tmpFront.push(frontTarget);
                    frontTarget = frontMap[frontTarget];
                } while (frontMap[frontTarget] != origin);
                
                while (!tmpFront.empty())
                {
                    tmpResult.push_back(tmpFront.top());
                    tmpFront.pop();
                } 
                do {
                    tmpResult.push_back (backTarget);
                    backTarget = backMap[backTarget];
                } while (backTarget != destination);
                tmpResult.push_back (destination);

                if ((!resultAlreadyExist(tmpResult))
                    && (tmpResult.size() > n_stage)
                    )
                {
                    finalResult.push_back(tmpResult);
                    resultCnt++;
                }
            }   
        }
    }

    free(frontCurrent);
    free(backCurrent);

    this->Close();
    std::string tmp;
    for (auto& it : finalResult)
    {
        for (auto& itt : it)
        {
            tmp += itt + "=>";
<<<<<<< HEAD
<<<<<<< HEAD
        }
        std::cout << tmp.substr(0, tmp.length() - 2) << std::endl;
        tmp.clear();
=======
            std::cout << itt << "->";
        }
        std::cout << tmp.substr(0, tmp.length() - 2) << std::endl;
>>>>>>> be9dfc439b13b10bac5193d6f3138c1d7a17ad3e
=======
            std::cout << itt << "->";
        }
        std::cout << tmp.substr(0, tmp.length() - 2) << std::endl;
>>>>>>> be9dfc439b13b10bac5193d6f3138c1d7a17ad3e
    }
    this->Stop();
    


#elif _FRONTBACK == 0
    frontStep->Start();


    CNamuStep::NamuPage *frontCurrent = frontStep->m_currentTarget;
    std::map<std::string, std::string> frontMap;
    while (m_threadStatus != 0)
    {
        for (const auto & pair : frontCurrent->historyMap)
        {
            frontMap.insert(pair);
        }
        int cnt = 0;
        for (const auto & pair : frontMap)
        {
            if (frontMap.find(destination) != frontMap.end())
            {
                std::cout <<"FOUND!"<<cnt++<<std::endl;
                                
                std::string frontTarget = frontMap[destination];
                if (checkElement(frontTarget))
                {
                    continue;
                }
                
                std::stack <std::string> tmpFront;
                std::vector <std::string> tmpResult;
            
                int a = 0;
                
                tmpResult.push_back(origin);
                if (frontMap[frontTarget] == origin)
                {
                    tmpFront.push (frontTarget);
                }
                while (frontMap[frontTarget] != origin)
                {
                        tmpFront.push(frontTarget);
                        frontTarget = frontMap[frontTarget];
                } 
                    
                while (!tmpFront.empty())
                {
                        tmpResult.push_back(tmpFront.top());
                        tmpFront.pop();
                }
                tmpResult.push_back (destination);

                if ((!resultAlreadyExist(tmpResult))
                    //&& tmpResult.size() > m_stage
                    )
                {
                    finalResult.push_back(tmpResult);
                    resultCnt++;
                }
            }   
            else
            {
                std::cout << "Not Yet" << cnt++ <<std::endl;
            }
        }
    }
#endif
}