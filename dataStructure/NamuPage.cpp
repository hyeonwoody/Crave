#include <algorithm>
#include <queue>
#include <stack>
#include "NamuPage.h"

uint64_t _CNamuPage::uniqueID = 0;
CNamuPageMiniMap<_CNamuPage> _CNamuPage::miniMap;

_CNamuPage* _CNamuPage::MoveTarget (EStep step)
{   
    _CNamuPage* tmp = this;
    switch (step)
    {
        case FRONTSTEP :
        {
            if (this->getIndex() == -1)
            {
                tmp = this->getFirstPrev();
                this->setIndex(0);
            }
            if (!this->next.empty())
            {   
                tmp = tmp->getNext();
                if (tmp->getFirstPrev()->increamentIndex(step)) // true if tmp is not the last 
                {
                    tmp->setIndex(-1); // mark for turning back (BFS)
                }
            }
            break;
        }
        case BACKSTEP :
        {   
            if (this->getIndex() == -1)
            {
                tmp = this->getFirstNext();
                this->setIndex(0);
            }
            if (!tmp->prev.empty())
            {
                tmp = tmp->getPrev();
                if (tmp->getFirstNext()->increamentIndex(step))
                {
                    tmp->setIndex(-1); // mark for turning back (BFS)
                }
            }
            break;
        }
    }
    
    
    return tmp;
}

std::vector<std::string> _CNamuPage::Traverse()
{
    _CNamuPage* origin = this;
    _CNamuPage* destination = this;
    std::deque <std::string> dqRoute;
    std::vector <std::string> ret;
    
    while (origin->stage != 1)
    {
        if (origin->getFirstPrev() == nullptr)
            return ret;
        origin = origin->getFirstPrev();
        dqRoute.push_front (origin->getName());
    }
    dqRoute.push_back (destination->getName());
    while (destination->stage != -1)
    {
        if (destination->getFirstNext() == nullptr)
            return ret;
        destination = destination->getFirstNext();
        dqRoute.push_back (destination->getName());
    }

    while (!dqRoute.empty())
    {
        ret.push_back (dqRoute.front());
        dqRoute.pop_front();
    }

    return ret;
}

std::vector<std::string> _CNamuPage::Traverse(EStep step, std::string result)
{
    _CNamuPage* origin = this;
    _CNamuPage* destination = this;
    std::vector <std::string> value;

    std::stack <std::string> stackName;
    std::queue <std::string> queueName;

    switch (step)
    {
        case FRONTSTEP :
        {
            do {
                stackName.push(origin->getName() + "(" + origin->getDisplayName() + ")");
                origin = origin->getFirstPrev();
            } while (origin->getStage() != 0);
            stackName.push (origin->getName() + "(" + origin->getDisplayName() + ")");
            
            while (!stackName.empty())
            {
                value.push_back(stackName.top());
                stackName.pop();
            }

            destination = destination->getNext(result);
            queueName.push (destination->getName() + "(" + destination->getDisplayName() + ")");
            do {
                destination = destination->getFirstNext();
                queueName.push (destination->getName() + "(" + destination->getDisplayName() + ")");
            } while (destination->getStage() != -1);
            queueName.push (destination->getName() + "(" + destination->getDisplayName() + ")");

            while (!queueName.empty())
            {
                value.push_back(queueName.front());
                queueName.pop();
            }
            break;
        }
        case BACKSTEP :
        {   
            stackName.push(origin->getName() + "(" + origin->getDisplayName() + ")");
            origin->getPrev (result);
            do {
                stackName.push(origin->getName() + "(" + origin->getDisplayName() + ")");
                origin->getFirstPrev();
            } while (origin->getStage() != 0);
            stackName.push(origin->getName() + "(" + origin->getDisplayName() + ")");

            while (!stackName.empty())
            {
                value.push_back(stackName.top());
                stackName.pop();
            }

            do {
                destination->getFirstNext();
                queueName.push (destination->getName() + "(" + destination->getDisplayName() + ")");
            } while (destination->getStage() != -1);
            queueName.push (destination->getName() + "(" + destination->getDisplayName() + ")");

            while (!queueName.empty())
            {
                value.push_back(queueName.front());
                queueName.pop();
            }
            break;
        }
    };

    return value;
}

void _CNamuPage::Bind (_CNamuPage* target, int64_t stage)
{
    if (stage > 0)
    {
        if (this->getNext(target->getName()) == nullptr)
        {
            this->addNext (target);
            target->addPrev (this);
        }
    }
    else if (stage < 0)
    {
        if (this->getPrev(target->getName()) == nullptr)
        {
            this->addPrev (target);
            target->addNext (this);
        }   
    }
}

bool _CNamuPage::UpdateShorter(int64_t originalStage, int64_t stage, std::string resultName)
{

}

bool _CNamuPage::RouteConfirm (int64_t frontStage, int64_t backStage, std::string name)
{
    
}

bool _CNamuPage::ResultInsert (int64_t stage, std::string resultName, void*& resultPage)
{   

    if ((resultName.find ("분류:") != std::string::npos)
        ||(resultName.find("/") != std::string::npos))
    {
        return false;
    }

    _CNamuPage* search = miniMap.find(resultName);
    if (search != nullptr)
    {
        resultPage = search;
        if ((stage < 0 && 0 < search->getStage()) || (search->getStage() < 0 && 0 < stage))
        { 
            // Found Route
            this->Bind (search, stage);
            return true;
        }
        else if ((search->getStage()) * stage > 0) // found in the same step
        {
            this->Bind (search, stage);
        }
        else // search == destination
        {
        }
        return false;
    }
    
    _CNamuPage* result = new _CNamuPage(resultName, "", resultName, stage); //name 
    resultPage = result;
    this->Bind (result, stage);
    return false;
}

_CNamuPage::_CNamuPage (std::string name, std::string displayName = "", std::string target = "", int64_t stage = 0)
{
    this->name = name;
    this->displayName = name;
    this->target = target;
    this->stage = stage;
    this->id = uniqueID++;
    this->index = 0;
    
    miniMap.pushElement(this);
}