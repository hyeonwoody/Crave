
#pragma once
#define MAX_LOG_MESSAGE 1024
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cassert>
#include <sstream>
#include <cstdarg>


    enum {
        LOG_LEVEL_ERROR,
        LOG_LEVEL_INFO,
    };
class CEventManager
{
public:


    static void Output (int level, const char* session, const char* func, int outputIndex, const char* buffer);
    static void LogExecute (int level, const char* session, const char* func, int outputIndex, std::string time, const char* buffer);
    static void LogOutput (int level, const char* session, const char* func, int outputIndex, const char *format, ...);
};

extern class CEventManager eventManager;

// #define LOG_CALL (level, s, o, f, ...)
//         do {
//             int __logOutputs__ = EventManager::isEnabled ((s), (level));
//             if (__logOutputs__)
//             EventManager::LogOutput ((level), __logOutput__, (s), (o), (f), ##__VA_ARGS__);
//         } while (0)

// #define LOG_CALL (level, s, f, ...) LOG_CALL (level, (s), -1, (f), ##__VA__ARGS__)
// #define INFO(s, f, ...) LOG_CALL (LOG_LEVEL_INFO, (s), (f), ##__VA_ARGS__)