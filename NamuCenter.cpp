#include <thread>

#include "NamuCenter.h"


bool CNamuCenter::AddPage()
{
    return true;
}

bool CNamuCenter::Found()
{
    return false;
}

bool CNamuCenter::Start()
{
    m_threadActive = true;
    ThreadMain();
    return true;
}

bool CNamuCenter::Stop()
{   
    m_threadActive = false;
    return true;
}

void CNamuCenter::ThreadMain()
{   
    // std::thread frontThread(&CNamuFrontStep::Start, frontStep);
    // std::thread backThread(&CNamuBackStep::Start, backStep);
    
    // CNamuStep::NamuPage *frontTarget = frontStep->currentTarget;
    // CNamuStep::NamuPage *backTarget = backStep->currentTarget;

    // while (m_threadActive) 
    // {
    //     if (frontTarget->m_link.size())
    //     {
    //         frontTarget->m_link.empty();
    //     }
        
    // }



    // frontThread.join();
    // backThread.join();
    frontStep->Start();
}