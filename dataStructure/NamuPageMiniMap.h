
#pragma once
#include <vector>
#include <string>

#define MAXIMUM_STAGE 7

template <typename T>
class CNamuPageMiniMap
{   
    
    private :
        std::vector <T*> frontMap;
        std::vector <T*> backMap;
    public :
        CNamuPageMiniMap ()
        {
        }   
    public :
        void pushElement (T* element);
        T* find (std::string name);
};