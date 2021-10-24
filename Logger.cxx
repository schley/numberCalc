#include <fstream>
#include <sstream>

#include "Logger.hxx"
        
std::ofstream Aoct::Logger::loggerOss; 
  
Aoct::Logger::LoggingEnabled Aoct::Logger::logTypeOn_ = 
            {{ true, true, true, true, true, true, true }};

        
Aoct::Logger::Logger()
{
    loggerOss.open("./calc_debug.log", std::ios::out);
}
        
Aoct::Logger::~Logger()
{
    loggerOss.close();
}
        
void Aoct::Logger::trace(const std::string& traceLog)
{
    if (logTypeOn_[(int) LoggerTypes::TRACE])
    {
        loggerOss << "[TRACE] " << traceLog << "\n";
    }
}
void Aoct::Logger::trace(std::ostringstream& traceLog)
{
    if (logTypeOn_[(int) LoggerTypes::TRACE])
    {
        trace(traceLog.str());
        traceLog.str("");
    }
}
        
void Aoct::Logger::info(const std::string& informationLog)
{
    if (logTypeOn_[(int) LoggerTypes::INFO])
    {
        loggerOss << "[INFO ] " << informationLog << "\n";
    }
}
void Aoct::Logger::info(std::ostringstream& informationLog)
{
    if (logTypeOn_[(int) LoggerTypes::INFO])
    {
        info(informationLog.str());
        informationLog.str("");
    }
}
        
void Aoct::Logger::perf(const std::string& performanceLog)
{
    if (logTypeOn_[(int) LoggerTypes::PERF])
    {
        loggerOss << "[PERF ] " << performanceLog << "\n";
    }
}
void Aoct::Logger::perf(std::ostringstream& performanceLog)
{
    if (logTypeOn_[(int) LoggerTypes::PERF])
    {
        perf(performanceLog.str() );
        performanceLog.str("");
    }
}

void Aoct::Logger::debug(const std::string& debugLog)
{
    if (logTypeOn_[(int) LoggerTypes::DEBUG])
    {
        loggerOss << "[DEBUG] " << debugLog << std::endl;
    }
}
void Aoct::Logger::debug(std::ostringstream& debugLog)
{
    if (logTypeOn_[(int) LoggerTypes::DEBUG])
    {
        debug(debugLog.str() );
        debugLog.str("");
    }
}
        
void Aoct::Logger::warn(const std::string& warningLog)
{
    if (logTypeOn_[(int) LoggerTypes::WARN])
    {
        loggerOss << "[WARN ]" << warningLog << std::endl;
    }
}
void Aoct::Logger::warn(std::ostringstream& warningLog)
{
    if (logTypeOn_[(int) LoggerTypes::WARN])
    {
        warn(warningLog.str() );
        warningLog.str("");
    }
}
        
void Aoct::Logger::error(const std::string& errorLog)
{
    if (logTypeOn_[(int) LoggerTypes::ERROR])
    {
        loggerOss << "[ERROR] " << errorLog << "\n";
    }
	std::cout << "[ERROR] " << errorLog << std::endl;
}
void Aoct::Logger::error(std::ostringstream& errorLog)
{
    if (logTypeOn_[(int) LoggerTypes::ERROR])
    {
        error(errorLog.str());
        errorLog.str("");
    }
}

void Aoct::Logger::fatal(const std::string& fatalLog)
{
    if (logTypeOn_[(int) LoggerTypes::FATAL])
    {
        loggerOss << "[FATAL] " << fatalLog << "\n";
    }
}
void Aoct::Logger::fatal(std::ostringstream& fatalLog)
{
    if (logTypeOn_[(int) LoggerTypes::FATAL])
    {
        fatal(fatalLog.str() );
        fatalLog.str("");
    }
}

bool Aoct::Logger::isEnabled(const Aoct::LoggerTypes type)
{
    bool currEnabled = Logger::logTypeOn_[(int) type];
    return currEnabled;
}

bool Aoct::Logger::isDebugEnabled()
{
    bool debugEnabled = isEnabled(LoggerTypes::DEBUG);
    return debugEnabled;
}       

bool Aoct::Logger::isTraceEnabled()
{
	bool traceEnabled = isEnabled(LoggerTypes::TRACE);
	return traceEnabled;
}

void Aoct::Logger::logStream(std::ostringstream& logOss, const LoggerTypes type)
{
    std::string currLog = logOss.str().c_str(); 
    logString(currLog, type);
    logOss.str("");
}

void Aoct::Logger::logString(const std::string& logString, 
                            const LoggerTypes type)
{
    if (logTypeOn_[(int) type])
    {
        switch (type)
        {
        case LoggerTypes::TRACE :
            trace(logString);
            break;
        case LoggerTypes::INFO :
            info(logString);
            break;
        case LoggerTypes::PERF :
            perf(logString);
            break;
        case LoggerTypes::DEBUG :
            debug(logString);
            break;
        case LoggerTypes::WARN :
            warn(logString);
            break;
        case LoggerTypes::ERROR :
            error(logString);
            break;
        case LoggerTypes::FATAL :
            fatal(logString);
            break;
        default :
            break;
        };
    }
} 
    
