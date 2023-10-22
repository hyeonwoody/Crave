
#include "NamuStep.h"
#include "./libs/Curl.cpp"

int64_t CNamuStep::Duration()
{
    std::random_device rd;
    std::mt19937_64 gen(rd()); // Mersenne Twister 64-bit PRNG
    std::uniform_int_distribution<int64_t> distribution(0, 3000);
    return distribution(gen) + 4400;
}

bool CNamuStep::_curlInit(std::string url, CurlBuffer* tmp)
{

    this->m_curl = curl_easy_init();
    if (this->m_curl)
    {
        curl_easy_setopt(this->m_curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, _CurlWriteStepCallback);
        curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, tmp);

        curl_easy_setopt(m_curl, CURLOPT_VERBOSE, 0L);
    }
    else {
        return false;
    }
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

bool CNamuStep::blockDetection (std::string html)
{
    if (html.find("<h1>비정상") != std::string::npos)
    {
        return true;
    }
    return false;
}

bool CNamuStep::ParseHtml (std::string html)
{
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
            if (m_current->ResultInsert (m_current->getStage() + e_step, result))
            {
                //Found Route
                m_current->Traverse (e_step, result);
            }
            
        }
        searchStart = match.suffix().first;
    }

    std::regex hrefRegey("href=['\"]/backlink/([^'\"]+)['\"][^>]*>Next");
    if (std::regex_search(searchStart, html.cend(), match, hrefRegey)){
        if (match.size() == 2){
            std::string input = match[1];
            
            if (input.find("?from=") != std::string::npos)
            {
                m_current->setTarget(input);
                return true;
            }
        }
    }
    return false;
}

std::string CNamuStep::_GetHtml (std::string url)  {


    
    CurlBuffer* html = new CurlBuffer ();
    std::string tmp;
    _curlInit(url, html);
    CURLcode res = curl_easy_perform(this->m_curl);

    if (html->privateData)
    {
        tmp = static_cast<const char*> (html->privateData);
        delete html->privateData;
        html->privateData = nullptr;
    }
    
    if (html)
    {
        delete html;
        html = nullptr;
    }
    
    return tmp;
}

std::string CNamuStep::GetHtml (std::string url)  {

    NamuPage* tmp = new NamuPage();
    
    std::string html;
    curlInit(url, tmp);
    CURLcode res = curl_easy_perform(this->m_curl);
    std::cout << static_cast<const char*> (tmp->privateData) <<std::endl;
    if (tmp->privateData)
    {
        html = static_cast<const char*> (tmp->privateData);
        delete tmp->privateData;
        tmp->privateData = nullptr;
    }
    
    if (tmp)
    {
        delete tmp;
        tmp = nullptr;
    }
    
    return html;
}

void CNamuStep::GetNextTarget ()
{   
    if (!m_currentTarget->nextPage.empty()){
        m_currentTarget->target = m_currentTarget->nextPage.front().second;
        m_currentTarget->nextPage.pop();
        m_currentTarget->name = m_currentTarget->target;
    }
    
}

bool CNamuStep::resultInsertion (NamuPage* current, std::string result)
{
    if ((current->historyMap.find(result) == current->historyMap.end())
        && (result.find("분류") == std::string::npos)
        && (result.find("/") == std::string::npos))
        {
            current->nextPage.push (std::make_pair (current->name, result));
            current->historyMap.insert (std::make_pair (result, current->name));
        }
}