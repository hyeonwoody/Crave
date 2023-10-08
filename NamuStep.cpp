#include <string>
#include <iostream>
#include "NamuStep.h"



bool CNamuStep::CurlInit(CURL* pCurl, NamuPage* pNamuPage)
{   
    pCurl = curl_easy_init();
    if (pCurl) {
        curl_easy_setopt(pCurl, CURLOPT_URL, pNamuPage->m_url.c_str());
        // curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWriteCallback);
        // curl_easy_setopt(curl, CURLOPT_WRITEDATA, &html);

        // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        // curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, CurlDebugCallback);
        // curl_easy_setopt(curl, CURLOPT_DEBUGDATA, NULL);        
    } else {
        std::cerr << "Failed to initialize libcurl." << std::endl;
    }
}

// std::string CNamuFrontStep::MakeUrl(std::string name)
// {
//     const std::string prefix = "https://namu.wiki/w/";
//     return prefix + name;
// }

// std::string CNamuBackStep::MakeUrl(std::string name)
// {
//     const std::string prefix = "https://namu.wiki/backlink/";
//      // Find the first occurrence of ' ' in the string
//     size_t pos = name.find_first_of(' ');

//     // Continue replacing consecutive spaces with a single "%20"
//     while (pos != std::string::npos) {
//         // Find the position of the first character after consecutive spaces
//         size_t endPos = name.find_first_not_of(' ', pos);

//         // Replace the consecutive spaces with "%20"
//         name.replace(pos, endPos - pos, "%20");

//         // Find the next position of a space after the replacement
//         pos = name.find_first_of(' ', endPos);
//     }

//     std::cout << name << std::endl;
//     return prefix + name;
// }