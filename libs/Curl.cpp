#include <string>
#include <iostream>
#include <regex>
#include <curl/curl.h>
#include "../NamuStep.h"

inline char from_hex(char ch) {
    return isdigit(ch) ? ch - '0' : tolower(ch) - 'a' + 10;
}

static size_t CurlWriteFrontCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    // size_t totalSize = size * nmemb;

    //std::regex hrefRegex("href=['\"](/w/[^'\"]*)['\"]");
    std::regex hrefRegex("href=['\"]/w/([^'\"]*)['\"]");
    CNamuStep::NamuPage *data = (CNamuStep::NamuPage *)output;
    
    size_t totalSize = size * nmemb;
    std::string html = static_cast<char*> (contents);
    std::smatch match;
    std::string::const_iterator searchStart(html.cbegin());
    
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
            if ((data->historyMap.find(result) == data->historyMap.end()) && (result.find("분류") == std::string::npos))
            {
                data->nextPage.push(std::make_pair (data->name, result));
                data->historyMap.insert(std::make_pair (result, data->name));
            }
            
        }
        searchStart = match.suffix().first;
    }
    
    //output->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

static size_t CurlWriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    // size_t totalSize = size * nmemb;

    
    CNamuStep::NamuPage *data = (CNamuStep::NamuPage *)output;
    // data->m_html = (uint8_t *) realloc (data->m_html, data->transferedSize + totalSize +1); 
    // if (data->m_html == NULL)
    // {
    //     return 0;
    // }
    // memcpy(data->m_html, contents, data->transferedSize + totalSize);
    // data->transferedSize += totalSize;
    // data->m_html[data->transferedSize] = 0;
    // return totalSize;
    size_t totalSize = size * nmemb;
    output->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

static int CurlDebugCallback (CURL *handle, curl_infotype type, char *data, size_t size, void *clinetp){
    std::string text;
    std::string info;
    switch (type) {
        case CURLINFO_TEXT:
            text = "== Info:";
            info = std::string(data, size);
        case CURLINFO_HEADER_OUT:
            text = "=> Send header:";
            info = std::string(data, size);
            break;
        case CURLINFO_DATA_OUT:
            text = "=> Send data: " + std::to_string(size);
            break;
        case CURLINFO_SSL_DATA_OUT:
            text = "=> Send SSL data: " + std::to_string(size);
            break;
        case CURLINFO_HEADER_IN:
            text = "<= Recv header:";
            info = std::string(data, size);
            break;
        case CURLINFO_DATA_IN:
            text = "<= Recv data: " + std::to_string(size);
            break;
        case CURLINFO_SSL_DATA_IN:
            text = "<= Recv SSL data: " + std::to_string(size);
            break;
        default: /* in case a new one is introduced to shock us */
            return 0;
    }
    std::cout << "CURL : "<<text.c_str();
    if (info.size() > 0)
        std::cout << info.c_str();
    std::cout << std::endl;
    return 0;

}