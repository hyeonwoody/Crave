
#pragma once

#include <string>
#include <vector>
#include <queue>
#include <map>
#include <memory>
#include "./libs/Thread.h"
#include <curl/curl.h>
#include "./dataStructure/ThreadSafeMap.h"


class CNamuStep
{
public:
    CNamuStep()
    {
    }
    
    typedef struct NamuPage
    {
        std::string name;
        size_t cnt;
        std::queue <std::pair <std::string, std::string>> nextPage; //prev=>cur
        ThreadSafeMap<std::string, std::string> historyMap; //cur<=prev
        void* privateData;
    };
    

    
    virtual void ThreadMain();
    CURL* m_curl;
    NamuPage* m_currentTarget;
private:

protected:
    bool curlInit(std::string url);
};

class CNamuFrontStep : public CNamuStep, public CThread
{
public:


    CNamuFrontStep(std::string front) : CThread("FrontStep") 
    {
        m_currentTarget = new NamuPage();
        m_currentTarget->name = front;
        m_threadStatus = e_ThreadStatus::THREAD_INACTIVE;
    }
    // Implement the Init and other virtual functions

    void ThreadMain() override{
        // Implement ThreadMain logic
        while (m_threadStatus != e_ThreadStatus::THREAD_INACTIVE)
        {
            std::string url = MakeUrl(m_currentTarget->name);
            MakeLinks(url);
            
            if (m_currentTarget->cnt == 0) {
                m_currentTarget->cnt = m_currentTarget->nextPage.size();
            }
            
             m_currentTarget->name = m_currentTarget->nextPage.front().second;
            m_currentTarget->nextPage.pop();
            m_currentTarget->cnt--;
            
        }
    }
    std::string MakeUrl(std::string name);
    bool MakeLinks (std::string url);
    
protected:
    CURL* m_curl;
};

class CNamuBackStep : public CNamuStep, public CThread
{
public:
    CNamuBackStep(std::string back) : CThread ("BackStep")
    {
        m_currentTarget = new NamuPage();
        m_currentTarget->name = back;
        m_threadStatus = e_ThreadStatus::THREAD_INACTIVE;
    }
    //virtual bool Delete ();

    virtual void ThreadMain() override {
        // Implement ThreadMain logic
        while (m_threadStatus != e_ThreadStatus::THREAD_INACTIVE)
        {
            std::string url = MakeUrl(m_currentTarget->name);
            MakeLinks(url);
            if (m_currentTarget->cnt == 0) {
                
                m_currentTarget->cnt = m_currentTarget->nextPage.size();
            }
            
             m_currentTarget->name = m_currentTarget->nextPage.front().second;
            m_currentTarget->nextPage.pop();
            m_currentTarget->cnt--;
        }
    }

    std::string MakeUrl(std::string name);
    bool MakeLinks (std::string url);

protected:
    
};


