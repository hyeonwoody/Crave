#include <string>
#include <vector>
#include <memory>
#include <curl/curl.h>
#include "./libs/Curl.cpp"

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
        std::vector<std::string> m_link;
    };
    virtual bool Start();
    virtual bool Stop();
    virtual void ThreadMain();
    virtual std::string MakeUrl(std::string name) = 0;
    virtual std::vector<std::string> MakeLinks (std::string url) = 0;
    bool CurlInit(CURL* pCurl, NamuPage* pNamuPage);
    CURL* m_curl;
private:

protected:
    NamuPage* currentTarget;
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
    }

    virtual std::string MakeUrl(std::string name) override {
        // Implement MakeUrl logic
        const std::string prefix = "https://namu.wiki/w/";
        return prefix + name;
    }

    virtual std::vector<std::string> MakeLinks (std::string url) override {
        CurlInit(m_curl, currentTarget);
        
        curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, CurlWriteCallback);

        curl_easy_setopt(m_curl, CURLOPT_VERBOSE, 1L);
        curl_easy_setopt(m_curl, CURLOPT_DEBUGFUNCTION, CurlDebugCallback);
        curl_easy_setopt(m_curl, CURLOPT_DEBUGDATA, NULL);  

        CURLcode res = curl_easy_perform(m_curl);
        std::vector<std::string> a;
        return a;
    }


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
    }

    virtual std::string MakeUrl(std::string name) override
    {

    const std::string prefix = "https://namu.wiki/backlink/";
     // Find the first occurrence of ' ' in the string
    size_t pos = name.find_first_of(' ');

    // Continue replacing consecutive spaces with a single "%20"
    while (pos != std::string::npos) {
        // Find the position of the first character after consecutive spaces
        size_t endPos = name.find_first_not_of(' ', pos);

        // Replace the consecutive spaces with "%20"
        name.replace(pos, endPos - pos, "%20");

        // Find the next position of a space after the replacement
        pos = name.find_first_of(' ', endPos);
    }

    return prefix + name;
    } 

    virtual std::vector<std::string> MakeLinks (std::string url) override {
        CurlInit(m_curl, currentTarget);
        
        curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, CurlWriteCallback);

        curl_easy_setopt(m_curl, CURLOPT_VERBOSE, 1L);
        curl_easy_setopt(m_curl, CURLOPT_DEBUGFUNCTION, CurlDebugCallback);
        curl_easy_setopt(m_curl, CURLOPT_DEBUGDATA, NULL);  

        CURLcode res = curl_easy_perform(m_curl);
        std::vector<std::string> a;
        return a;
    }

protected:
};