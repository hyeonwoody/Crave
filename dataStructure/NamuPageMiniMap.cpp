#include "NamuPageMiniMap.h"
#include "NamuPage.h"

// 템플릿 클래스 인스턴스화
template class CNamuPageMiniMap<_CNamuPage>;

std::vector <_CNamuPage> miniMap;

template <typename T>
T* CNamuPageMiniMap<T>::find(std::string name)
{
    for (size_t i = 0; i < frontMap.size(); ++i)
    {

        if (name ==  frontMap[i]->getName())
        {
            return frontMap[i];
        }
    }
    for (size_t i = 0; i < backMap.size(); ++i)
    {
        if (name ==  backMap[i]->getName())
        {
            return backMap[i];
        }
    }
    return nullptr;
}


template <typename T>
void CNamuPageMiniMap<T>::pushElement (T* element)
{
    if (element != nullptr)
    {
        if (element->getStage() > 0)
        {
            frontMap.push_back(element);
        }
        else 
        {
            backMap.push_back(element);
        }
    }
}

