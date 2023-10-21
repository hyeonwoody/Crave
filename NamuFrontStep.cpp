#include <string>
#include <iostream>
#include "NamuStep.h"
#include "./libs/Curl.cpp"


std::string CNamuFrontStep::MakeUrl (std::string name)  {
        const std::string prefix = "https://namu.wiki/w/";
        return prefix + name;
}

bool CNamuFrontStep::MakeLinks (std::string url)  {
    m_curl = curl_easy_init();
    if (m_curl)
    {
        curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());
    }
    else {
       return false;
    }
        
    curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, CurlWriteFrontCallback);
    curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, m_currentTarget);

    curl_easy_setopt(m_curl, CURLOPT_VERBOSE, 0L);
    // curl_easy_setopt(m_curl, CURLOPT_DEBUGFUNCTION, CurlDebugCallback);
    // curl_easy_setopt(m_curl, CURLOPT_DEBUGDATA, NULL);  
    // curl_easy_setopt(curl, CURLOPT_WRITEDATA, &html);

    // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    // curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, CurlDebugCallback);
    // curl_easy_setopt(curl, CURLOPT_DEBUGDATA, NULL);        
    CURLcode res = curl_easy_perform(m_curl);
    return true;
}

bool CNamuFrontStep::GetLinks (std::string html)  {
    std::smatch match;
    std::string::const_iterator searchStart(html.cbegin());
    std::regex hrefRegex("href=['\"]/w/([^'\"]*)['\"]");
    while (std::regex_search(searchStart, html.cend(), match, hrefRegex)) {
        if (match.size() == 2) {
            std::string input = match[1];
            std::string result;
            for (size_t i = 0; i < match[1].length(); i++) {
                if (input[i] == '%') 
                {
                    if (i + 2 < input.length()) {
                        char decoded_char = (from_hex(input[i + 1]) << 4) | from_hex(input[i + 2]);
                        result += decoded_char;
                        i += 2;
                    }
                }
                else if (input[i] == '+') 
                {
                    result += ' ';
                } 
                else if (input[i] == '#')
                {
                    break;
                }
                else 
                {
                    result += input[i];
                }
            }

            resultInsertion (m_currentTarget, result);
        }
        searchStart = match.suffix().first;
    }
}