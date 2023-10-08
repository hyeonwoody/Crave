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
    ThreadMain();
    return true;
}

bool CNamuCenter::Stop()
{
    return true;
}

void CNamuCenter::ThreadMain()
{   
    frontStep->Start();
    backStep->Start();
}