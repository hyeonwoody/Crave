
#include "NamuStep.h"
#include "libs/Thread.h"

class CNamuStep;

class CNamuCenter : public CThread
{
public:
    CNamuCenter (std::string front, const std::string back, size_t routes, size_t stages) : CThread ("NamuCenter"){

        origin = front;
        destination = back;
        
        n_route = routes;
        n_stage = stages;

        frontStep = new CNamuFrontStep(front);
        backStep = new CNamuBackStep(back);
    }

public :
    
    void Close();
    void Stop();
    void ThreadMain();

protected :
private:

    CNamuFrontStep* frontStep;
    CNamuBackStep* backStep;

    std::string origin;
    std::string destination;

    size_t n_stage;
    size_t n_route;

    std::vector<std::vector<std::string>> finalResult;
    bool resultAlreadyExist(std::vector <std::string> tmpResult);
    bool checkElement (std::string tmpElement);
    int resultCnt;
};