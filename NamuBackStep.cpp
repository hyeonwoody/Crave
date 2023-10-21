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


bool CNamuBackStep::GetLinks (std::string html)
{
    std::smatch match;
    
    std::string::const_iterator searchStart(html.cbegin());

    std::regex hrefRegey("href=['\"]/w/([^'\"]*)['\"]");
    while (std::regex_search(searchStart, html.cend(), match, hrefRegey)) {
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
        

    std::regex hrefRegex("href=['\"]/backlink/([^'\"]+)['\"][^>]*>Next");
    if (std::regex_search(searchStart, html.cend(), match, hrefRegex)){
        if (match.size() == 2){
            std::string input = match[1];
            
            if (input.find("?from=") != std::string::npos)
            {
                m_currentTarget->target = input;
                return true;
            }
        }
    }
    return false;
}
