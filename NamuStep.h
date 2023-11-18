
#pragma once
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <memory>

#include "./libs/Base.h"
#include "./libs/Thread.h"
#include <curl/curl.h>
#include "./dataStructure/NamuPage.h"
#include "./dataStructure/NamuPageMiniMap.h"
#include "./dataStructure/ThreadSafeMap.h"
#include "./dataStructure/ThreadSafeQueue.h"
#include <thread> //Sleep
#include <chrono> //Sleep
#include <random> //Random Time
#include <tuple>

class CNamuStep : virtual public CBase, virtual public CThread
{
public:
    static ThreadSafeQueue <_CNamuPage*> foundRoute; // binder, currentTarget
    static CNamuPageMiniMap<_CNamuPage> miniMap;

    CNamuStep (std::string target) : CThread(NULL) 
    {
        m_currentTarget = new NamuPage();
        m_currentTarget->target = target;
        m_currentTarget->name = target;
        
        m_current = new _CNamuPage (target, target, target, e_step);

        m_threadStatus = THREAD_INACTIVE;
        m_currentTarget->historyMap.insert (std::make_pair (target, target));
    }

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

class CNamuFrontStep : virtual public CNamuStep
{
public:

    CNamuFrontStep(std::string front) : CNamuStep (front), CThread("FrontStep") 
    {
        e_step = FRONTSTEP;
    }

    void ThreadMain() override{
        while (m_threadStatus != THREAD_INACTIVE)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(Duration()));
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
                eventManager.LogOutput (LOG_LEVEL_INFO, m_sName, __FUNCTION__, 0, "Block Detected");
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

class CNamuBackStep : virtual public CNamuStep
{
public:

    CNamuBackStep(std::string back) : CNamuStep (back), CThread("BackStep") 
    {
        e_step = BACKSTEP;
    }


    //virtual bool Delete ();

    virtual void ThreadMain() override {
        // Implement ThreadMain logic
        
        while (m_threadStatus != THREAD_INACTIVE)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(Duration()));
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
                eventManager.LogOutput (LOG_LEVEL_INFO, m_sName, __FUNCTION__, 0, "Block Detected");
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


