
#pragma once
#include <vector>
#include <string>
#include "NamuPage.h"

#define MAXIMUM_STAGE 7

class CNamuPageMiniMap
{   
    
    private :
        std::vector <std::pair<int64_t, std::string>> miniMap;
    public :
        CNamuPageMiniMap ()
        {
            int a = 0;
        }   
    public :
        void pushElement (int64_t stage, std::string name);
        bool find (std::string name, int64_t* position);
};