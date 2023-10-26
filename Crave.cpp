#include <iostream>
#include <string>

#include "NamuCenter.h"

#define NUM_OF_ROUTES 100
#define NUM_OF_STAGES 6

int main(int argc, char* argv[]) {

    if (argc < 2){
        std::cerr << "Usage: " << argv[0] << " <arg1> <arg2>" << std::endl;
        return 1;
    }
    
    CNamuCenter* namu = new CNamuCenter(argv[1], argv[2], NUM_OF_ROUTES, NUM_OF_STAGES);
    namu->m_threadStatus = THREAD_ACTIVE;
    
    namu->Start();
    while (namu->m_threadStatus != THREAD_INACTIVE)
    {
        
    }
    if (namu)
    {
        delete (namu);
        namu = nullptr;
    }
    return 0;
}