
#pragma once

#include <string>
#include <vector>
#include <set>
#include <memory>
#include <curl/curl.h>


class CNamuStep
{
public:
    CNamuStep()
    {
        m_threadActive = false;
    }
    
    typedef struct NamuPage
    {
        std::string m_name;
        std::string m_url;
        std::string* m_html;
        int64_t transferedSize;
        std::set<std::string> m_link;
        NamuPage* prev;
        NamuPage* next;
    };
    virtual bool Start();
    virtual bool Stop();
    virtual void ThreadMain();
    bool CurlInit(CURL* pCurl, NamuPage* pNamuPage);
    CURL* m_curl;
    NamuPage* currentTarget;
private:

protected:
    bool m_threadActive;
};

class CNamuFrontStep : public CNamuStep
{
public:
    CNamuFrontStep(std::string front)
    {
        currentTarget = new NamuPage();
        currentTarget->m_name = front;
    }
    // Implement the Init and other virtual functions

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
    CURL* m_curl;
};

class CNamuBackStep : public CNamuStep
{
public:
    CNamuBackStep(std::string back)
    {
        currentTarget = new NamuPage();
        currentTarget->m_name = back;
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


