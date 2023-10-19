
#pragma once

#include <string>
#include <vector>
#include <set>
#include <memory>
#include "./libs/Thread.h"
#include <curl/curl.h>


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
        std::set<std::string> m_link;
        NamuPage* prev;
        NamuPage* next;
    };

    virtual void ThreadMain();
    bool CurlInit(CURL* pCurl, NamuPage* pNamuPage);
    CURL* m_curl;
    NamuPage* currentTarget;
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
        m_threadActive = false;
    }
    // Implement the Init and other virtual functions

    void ThreadMain() override{
        // Implement ThreadMain logic
        while (m_threadActive)
        {
            currentTarget->m_url = MakeUrl(currentTarget->m_name); 
            MakeLinks(currentTarget->m_url);
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
        m_threadActive = false;
    }
    //virtual bool Delete ();

    virtual void ThreadMain() override {
        // Implement ThreadMain logic
        while (m_threadActive)
        {
            currentTarget->m_url = MakeUrl(currentTarget->m_name); 
            MakeLinks(currentTarget->m_url);
        }
    }

    std::string MakeUrl(std::string name);
    bool MakeLinks (std::string url);

protected:
};


