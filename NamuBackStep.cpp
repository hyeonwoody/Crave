#include <string>
#include <iostream>
#include "NamuStep.h"
#include "./libs/Curl.cpp"

std::string CNamuBackStep::MakeUrl (std::string name)  {
    const std::string prefix = "https://namu.wiki/backlink/";
    size_t pos = name.find_first_of(' ');

    while (pos != std::string::npos) {
        size_t endPos = name.find_first_not_of(' ', pos);
        name.replace(pos, endPos - pos, "%20");

        // Find the next position of a space after the replacement
        pos = name.find_first_of(' ', endPos);
    }

    return prefix + name;
}

bool CNamuBackStep::MakeLinks (std::string url)  {
    curlInit(url);
        
        
    curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, CurlWriteStepCallback);
    curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, m_currentTarget);

    curl_easy_setopt(m_curl, CURLOPT_VERBOSE, 1L);
        // curl_easy_setopt(m_curl, CURLOPT_DEBUGFUNCTION, CurlDebugCallback);
        // curl_easy_setopt(m_curl, CURLOPT_DEBUGDATA, NULL);  
        // curl_easy_setopt(curl, CURLOPT_WRITEDATA, &html);

        // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        // curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, CurlDebugCallback);
        // curl_easy_setopt(curl, CURLOPT_DEBUGDATA, NULL);        
    CURLcode res = curl_easy_perform(m_curl);
    std::cout << static_cast<const char*> (m_currentTarget->privateData) <<std::endl;
    return true;
}