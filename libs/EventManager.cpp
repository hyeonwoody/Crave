
#include "EventManager.h"

void CEventManager::LogExecute (int level, const char* session, int outputIndex, std::string time, const char* buffer)
{
    if (!session)
        session = "NoName";

    std::cout << time << " " << session << " : " <<  buffer << std::endl;
}
void CEventManager::Output (int level, int outputs, const char* session, int outputIndex, const char* buffer)
{
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time (&tm, "%Y-%m-%d %H:%M:%S");
    std::string time = oss.str();
    LogExecute (level, session, outputIndex, time, buffer);
}

void CEventManager::LogOutput (int level, int outputs, const char* session, int outputIndex, const char *format, ...)
{
    char buffer[MAX_LOG_MESSAGE];

    va_list args;
    va_start (args, format);
    assert(format);
    int len = vsnprintf (buffer, MAX_LOG_MESSAGE-1, format, args);
    va_end(args);

    if (0 <= len && len < MAX_LOG_MESSAGE -1)
    {
        Output (level, outputs, session, outputIndex, buffer);
    }
}