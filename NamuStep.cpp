#include <string>
#include <cstring>
#include <iostream>
#include "NamuStep.h"
#include "./libs/Curl.cpp"


void CNamuStep::ThreadMain()
{

    int a = 0;
}

bool CNamuStep::curlInit(std::string url)
{

    this->m_curl = curl_easy_init();
    if (this->m_curl)
    {
        curl_easy_setopt(this->m_curl, CURLOPT_URL, url.c_str());
    }
    else {
        return false;
    }
}
