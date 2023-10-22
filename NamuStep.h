
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
#include "./dataStructure/NamuPage.h"
#include "./dataStructure/ThreadSafeMap.h"
#include <thread> //Sleep
#include <chrono> //Sleep
#include <random> //Random Time

class CNamuStep
{
public:
    static std::vector<std::vector<std::string>> routes; 
    typedef struct 
    {
        std::string target;
        std::string name;
        size_t cnt;
        std::queue <std::pair <std::string, std::string>> nextPage; //prev=>cur
        ThreadSafeMap<std::string, std::string> historyMap; //cur<=prev
        void* privateData;
    } NamuPage;

    typedef struct
    {
        void* privateData;
        size_t transferedSize;
    } CurlBuffer;

    
    

    _CNamuPage* m_current;
    NamuPage* m_currentTarget;
    bool resultInsertion (NamuPage* current, std::string key);
private:
    
protected:
    EStep e_step;
    CURL* m_curl;
    
    bool blockDetection (std::string html);
    bool curlInit(std::string url, NamuPage* tmp);
    bool _curlInit(std::string url, CurlBuffer* tmp);
    std::string GetHtml (std::string url);
    std::string _GetHtml (std::string url);
    void GetNextTarget ();
    int64_t Duration();


    bool ParseHtml (std::string html);
};

class CNamuFrontStep : public CNamuStep, public CThread
{
public:


    CNamuFrontStep(std::string front) : CThread("FrontStep") 
    {
        m_currentTarget = new NamuPage();
        m_currentTarget->target = front;
        m_currentTarget->name = front;
        e_step = FRONTSTEP;
        m_current = new _CNamuPage (front, front, e_step);

        m_threadStatus = THREAD_INACTIVE;
        m_currentTarget->historyMap.insert (std::make_pair (front, front));
    }

    void ThreadMain() override{
        while (m_threadStatus != THREAD_INACTIVE)
        {
            // std::string url = MakeUrl(m_currentTarget->target);
            // std::string html = GetHtml (url);
            // if (blockDetection(html))
            // {
            //     continue;
            // }
            // GetLinks(html);
            // GetNextTarget();

            // std::this_thread::sleep_for(std::chrono::milliseconds(Duration()));
            std::string url = MakeUrl (m_current->getTarget());  
            std::string html = _GetHtml (url);
            
            if (blockDetection(html))
            {
                continue;
            }

            ParseHtml(html);
            m_current = m_current->MoveTarget(e_step);
            int a = 0;
        }

        
        while (m_threadStatus != THREAD_INACTIVE)
        {
            
            
        }


    }
    std::string MakeUrl(std::string name);
    bool GetLinks (std::string url);
    bool MakeLinks (std::string url);

    
    
protected:
};

class CNamuBackStep : public CNamuStep, public CThread
{
public:
    CNamuBackStep(std::string back) : CThread ("BackStep")
    {
        m_currentTarget = new NamuPage();
        m_currentTarget->target = back;
        m_currentTarget->name = back;
        e_step = BACKSTEP;
        m_current = new _CNamuPage (back, back, 0);
        
        m_threadStatus = THREAD_INACTIVE;
        m_currentTarget->historyMap.insert (std::make_pair (back, back));
    }
    //virtual bool Delete ();

    virtual void ThreadMain() override {
        // Implement ThreadMain logic
        
        while (m_threadStatus != THREAD_INACTIVE)
        {
            // std::string url = MakeUrl(m_currentTarget->target);
            // std::string html = GetHtml(url);

            // if (blockDetection(html))
            // {
            //     continue;
            // }

            // if (GetLinks(html)) 
            // {
            //     continue;
            // } 
            // else 
            // {
            //     GetNextTarget();
            // }
            // std::this_thread::sleep_for(std::chrono::milliseconds(Duration()));

            std::string url = MakeUrl (m_current->getTarget());  
            std::string html = _GetHtml (url);
            
            if (blockDetection(html))
            {
                continue;
            }

            if (ParseHtml(html))
            {
                continue;
            }

            m_current = m_current->MoveTarget(e_step);
            int a = 0;
        }

        
    }

    std::string MakeUrl(std::string target);
    bool GetLinks (std::string html);

protected:
    
};


