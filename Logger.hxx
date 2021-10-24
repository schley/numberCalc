#if !defined BPL_LOGGER_HXX_
#define      BPL_LOGGER_HXX_

#include <iostream>
#include <sstream>
#include <fstream>
#include <array>

namespace Aoct
{
    enum class LoggerTypes : int
    {
       TRACE = 0,
       INFO  = 1,
       PERF  = 2,
       DEBUG = 3,
       WARN  = 4,
       ERROR = 5,
       FATAL = 6
    };

    class Logger
    {
    public:
        Logger();
        ~Logger();
        // static std::ofstream loggerOss; 

        static void trace(const std::string& traceLog);
        static void trace(std::ostringstream& traceLog);

        static void info(const std::string& informationLog);
        static void info(std::ostringstream& informationLog);

        static void perf(const std::string& performanceLog);
        static void perf(std::ostringstream& performanceLog);

        static void debug(const std::string& performanceLog);
        static void debug(std::ostringstream& performanceLog);

        static void warn(const std::string& performanceLog);
        static void warn(std::ostringstream& performanceLog);

        static void error(const std::string& performanceLog);
        static void error(std::ostringstream& performanceLog);

        static void fatal(const std::string& fatalLog);
        static void fatal(std::ostringstream& fatalLog);

        static bool isEnabled(const LoggerTypes type);

        static bool isTraceEnabled();
        static bool isInfoEnabled();
        static bool isPerfEnabled();
        static bool isDebugEnabled();

        static void logStream(std::ostringstream& logOss, 
                              const LoggerTypes type);
        static void logString(const std::string& logString, 
                              const LoggerTypes type); 
    private:
        static std::ofstream loggerOss;
        static constexpr int NUMBER_LOGGER_TYPES = (int)LoggerTypes::FATAL + 1;
        using LoggingEnabled = std::array<bool, NUMBER_LOGGER_TYPES>;
        static LoggingEnabled logTypeOn_; 
    }; // class Logger

} // namespace Bpl

#endif    // BPL_LOGGER_HXX_
