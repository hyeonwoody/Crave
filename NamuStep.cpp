#include <string>
#include <cstring>
#include <iostream>
#include "NamuStep.h"
#include "./libs/Curl.cpp"


void CNamuStep::ThreadMain()
{

    int a = 0;
}

std::string CNamuBackStep::MakeUrl(std::string name)
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

bool CNamuBackStep::MakeLinks (std::string url)  {
    m_curl = curl_easy_init();
     std::vector<std::string> a;
    if (m_curl)
    {
        curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());
    }
    else {
        return false;
    }
        
        curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, CurlWriteCallback);
        curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, currentTarget);

        curl_easy_setopt(m_curl, CURLOPT_VERBOSE, 1L);
        curl_easy_setopt(m_curl, CURLOPT_DEBUGFUNCTION, CurlDebugCallback);
        curl_easy_setopt(m_curl, CURLOPT_DEBUGDATA, NULL);  

        CURLcode res = curl_easy_perform(m_curl);
    
        return true;   
}