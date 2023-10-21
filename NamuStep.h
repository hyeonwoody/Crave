
#pragma once
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <memory>

#include "./libs/Thread.h"
#include <curl/curl.h>
#include "./dataStructure/ThreadSafeMap.h"
#include <thread> //Sleep
#include <chrono> //Sleep
#include <random> //Random Time

class CNamuStep
{
public:
    CNamuStep()
    {
    }
    
    typedef struct NamuPage
    {
        std::string target;
        std::string name;
        size_t cnt;
        std::queue <std::pair <std::string, std::string>> nextPage; //prev=>cur
        ThreadSafeMap<std::string, std::string> historyMap; //cur<=prev
        void* privateData;
    };
    
    CURL* m_curl;
    NamuPage* m_currentTarget;
    bool resultInsertion (NamuPage* current, std::string key);
private:

protected:
    bool curlInit(std::string url, NamuPage* tmp);
    int64_t Duration();
};

class CNamuFrontStep : public CNamuStep, public CThread
{
public:


    CNamuFrontStep(std::string front) : CThread("FrontStep") 
    {
        m_currentTarget = new NamuPage();
        m_currentTarget->name = front;
        m_threadStatus = THREAD_INACTIVE;
        m_currentTarget->historyMap.insert (std::make_pair (front, front));
    }
    // Implement the Init and other virtual functions

    void ThreadMain() override{
        // Implement ThreadMain logic
        while (m_threadStatus != THREAD_INACTIVE)
        {
            std::string url = MakeUrl(m_currentTarget->name);
            MakeLinks(url);
            
            if (m_currentTarget->cnt == 0) {
                m_currentTarget->cnt = m_currentTarget->nextPage.size();
            }
            if (!m_currentTarget->nextPage.empty())
            {
                m_currentTarget->name = m_currentTarget->nextPage.front().second;
                m_currentTarget->nextPage.pop();
            }
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
        m_currentTarget->target = back;
        m_currentTarget->name = back;
        m_threadStatus = THREAD_INACTIVE;
        m_currentTarget->historyMap.insert (std::make_pair (back, back));
    }
    //virtual bool Delete ();

    virtual void ThreadMain() override {
        // Implement ThreadMain logic
        
        while (m_threadStatus != THREAD_INACTIVE)
        {
            std::string url = MakeUrl(m_currentTarget->target);
            std::string html = GetHtml(url);

            if (GetLinks(html)) 
            {
                continue;
            } 
            else 
            {
                GetNextTarget();
            }
            
        }
    }

    std::string MakeUrl(std::string target);
    std::string GetHtml (std::string url);
    bool GetLinks (std::string html);
    void GetNextTarget ();

protected:
    
};


