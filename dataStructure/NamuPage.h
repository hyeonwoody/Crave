#pragma once
#include <string>
#include <vector>

#include "NamuPageMiniMap.h"

enum EStep : int64_t
{
    FRONTSTEP = 1,
    BACKSTEP = -1,
};

class _CNamuPage
{   
    public :
        static uint64_t uniqueID;
        static CNamuPageMiniMap<_CNamuPage> miniMap;
        _CNamuPage (std::string name, std::string target, int64_t stage);
    public :
    private :
        uint64_t id;
        std::string target;
        std::string name;
        std::string displayName;
        int64_t stage;
        void* privateData;
        int64_t index;
        std::vector <_CNamuPage*> next;
        std::vector <_CNamuPage*> prev;
    
    public :
        std::vector<std::string> Traverse(EStep step, std::string result);
        void Connect (_CNamuPage* current, _CNamuPage* target, int64_t stage);
        bool UpdateShorter(int64_t originalStage, int64_t stage, std::string resultName);
        bool ResultInsert (int64_t stage, std::string resultName, void*& resultPage);
        bool RouteConfirm (int64_t frontStage, int64_t backStage, std::string name);

        _CNamuPage* MoveTarget(EStep step);

    public :
        uint64_t getId() const {return this->id;}
        const std::string& getName() const {return this->name;}
        const std::string& getDisplayName() const {return this->displayName;}
        const std::string& getTarget() const {return this->target;}
        int64_t getStage() const {return this->stage;}
        const void* getPrivateData() const {return this->privateData;}
        int64_t getIndex() const {return this->index;}
        _CNamuPage* getNext() const {return this->next[this->index];}
        _CNamuPage* getPrev() const {return this->prev[this->index];}

        _CNamuPage* getFirstNext() const {return this->next[0];}
        _CNamuPage* getFirstPrev() const {return this->prev[0];}

        _CNamuPage* getNext(std::string name) const 
        {
            for (const auto& nextPage : this->next) {
                if (nextPage->getName() == name) 
                    return nextPage;
            }
            return nullptr;
        }
        _CNamuPage* getPrev(std::string name) const 
        {
            for (const auto& prevPage : this->prev) {
                if (prevPage->getName() == name) 
                    return prevPage;
            }
            return nullptr;
        }
        
        void setName(std::string name) {this->name = name;}
        void setTarget(std::string target) {this->target = target;}
        void setStage(int64_t stage) {this->stage = stage;}
        void setPrivateData(void* privateData) {this->privateData = privateData;}
        void setIndex(int64_t index) {this->index = index;}
        void addNext(_CNamuPage* next) {this->next.push_back (next);}
        void addPrev(_CNamuPage* prev) {this->prev.push_back (prev);}

        bool increamentIndex (EStep step) 
        {
            ++this->index;
            switch (step)
            {
                case FRONTSTEP :
                {
                    return this->index != this->next.size(); 
                    break;
                }
                case BACKSTEP :
                {
                    return this->index != this->prev.size();
                    break;
                }
            }
        }
        bool decrementIndex() 
        {
            --this->index;
        }
};