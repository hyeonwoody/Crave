
#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>
#include "./libs/Thread.h"
#include <curl/curl.h>
#include "./dataStructure/ThreadSafeQueue.h"


class CNamuStep
{
public:
    CNamuStep()
    {
    }
    
    typedef struct NamuPage
    {
        std::string m_name;
        std::string m_url;
        int round;
        std::map<std::string, int> m_link;
        NamuPage* prev;
        NamuPage* next;
    };

    virtual void ThreadMain();
    bool CurlInit(CURL* pCurl, NamuPage* pNamuPage);
    CURL* m_curl;
    NamuPage* currentTarget;
    ThreadSafeQueue <std::string> dataCenter;
private:

protected:
};

class CNamuFrontStep : public CNamuStep, public CThread
{
public:


    CNamuFrontStep(std::string front) : CThread("FrontStep") 
    {
        currentTarget = new NamuPage();
        currentTarget->m_name = front;
        m_threadStatus = e_ThreadStatus::THREAD_INACTIVE;
        pthread_mutex_init(&m_mutex, NULL);
    }
    // Implement the Init and other virtual functions

    void ThreadMain() override{
        // Implement ThreadMain logic
        while (m_threadStatus != e_ThreadStatus::THREAD_INACTIVE)
        {
            currentTarget->m_url = MakeUrl(currentTarget->m_name); 
            pthread_mutex_lock(&m_mutex); 
            MakeLinks(currentTarget->m_url);
            pthread_mutex_unlock (&m_mutex);
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
    CNamuBackStep(std::string back)
    {
        currentTarget = new NamuPage();
        currentTarget->m_name = back;
        m_threadStatus = e_ThreadStatus::THREAD_INACTIVE;
        pthread_mutex_init(&m_mutex, NULL);
    }
    //virtual bool Delete ();

    virtual void ThreadMain() override {
        // Implement ThreadMain logic
        while (m_threadStatus != e_ThreadStatus::THREAD_INACTIVE)
        {
            currentTarget->m_url = MakeUrl(currentTarget->m_name);
            pthread_mutex_lock(&m_mutex); 
            MakeLinks(currentTarget->m_url);
            pthread_mutex_unlock (&m_mutex);
        }
    }

    std::string MakeUrl(std::string name);
    bool MakeLinks (std::string url);

protected:
    
};


