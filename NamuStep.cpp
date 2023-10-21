
#include "NamuStep.h"
#include "./libs/Curl.cpp"

int64_t CNamuStep::Duration()
{
    std::random_device rd;
    std::mt19937_64 gen(rd()); // Mersenne Twister 64-bit PRNG
    std::uniform_int_distribution<int64_t> distribution(0, 3000);
    return distribution(gen);
}

bool CNamuStep::curlInit(std::string url, NamuPage* tmp)
{

    this->m_curl = curl_easy_init();
    if (this->m_curl)
    {
        curl_easy_setopt(this->m_curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, CurlWriteStepCallback);
        curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, tmp);

        curl_easy_setopt(m_curl, CURLOPT_VERBOSE, 0L);
    }
    else {
        return false;
    }
}

bool CNamuStep::resultInsertion (NamuPage* current, std::string result)
{
    if ((current->historyMap.find(result) == current->historyMap.end())
        && (result.find("분류") == std::string::npos))
        {
            current->nextPage.push (std::make_pair (current->name, result));
            current->historyMap.insert (std::make_pair (result, current->name));
        }
}