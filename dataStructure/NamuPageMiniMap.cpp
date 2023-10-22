#include "NamuPageMiniMap.h"

bool CNamuPageMiniMap::find(std::string name, int64_t* stage)
{
    for (size_t i = 0; i < miniMap.size(); ++i)
    {
        if (name == miniMap[i].second)
        {
            *stage = miniMap[i].first;
            return true;
        }
    }
    return false;
}


void CNamuPageMiniMap::pushElement(int64_t stage, std::string name)
{
    miniMap.push_back (std::make_pair(stage, name));
}
