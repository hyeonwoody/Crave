#include <string>
#include <iostream>
#include "NamuStep.h"
#include "./libs/Curl.cpp"

std::string CNamuFrontStep::MakeUrl (std::string name)  {
        // Implement MakeUrl logic
        const std::string prefix = "https://namu.wiki/w/";
        return prefix + name;
}

std::vector<std::string> CNamuFrontStep::MakeLinks (std::string url)  {
    std::vector<std::string> a;
        m_curl = curl_easy_init();
    if (m_curl)
    {
        curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());
    }
    else {
       return a;
    }
        
        
        curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, CurlWriteCallback);
        curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &currentTarget->m_html);

        curl_easy_setopt(m_curl, CURLOPT_VERBOSE, 1L);
        // curl_easy_setopt(m_curl, CURLOPT_DEBUGFUNCTION, CurlDebugCallback);
        // curl_easy_setopt(m_curl, CURLOPT_DEBUGDATA, NULL);  
        // curl_easy_setopt(curl, CURLOPT_WRITEDATA, &html);

        // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        // curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, CurlDebugCallback);
        // curl_easy_setopt(curl, CURLOPT_DEBUGDATA, NULL);        
        CURLcode res = curl_easy_perform(m_curl);
        return a;
}