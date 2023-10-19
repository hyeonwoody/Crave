
#include "NamuStep.h"
#include "libs/Thread.h"

class CNamuCenter : public CThread
{
public:
    CNamuCenter (std::string front, const std::string back) : CThread ("NamuCenter"){
        vfront.push_back(front);
        vback.push_back(back);

        data = new int;

        frontStep = new CNamuFrontStep(front);
        backStep = new CNamuBackStep(back);
    }

public :
    
    bool AddPage ();
    bool Found ();
    
    void Close();
    void ThreadMain();
    CNamuFrontStep* frontStep;
    CNamuBackStep* backStep;
    int* data;

    std::vector<std::string> vfront;
    std::vector<std::string> vback;

protected :
};