#ifndef LOGGING_H_
#define LOGGING_H_

#include <string>
#include <iostream>
#include <sstream>

namespace casualdb {
enum LogLevel {
    kLogError, 
    kLogWarning, 
    kLogInfo, 
    kLogDebug, 
    kLogTrace
};

class Log {
public:
    Log() {};
    virtual ~Log();
    std::ostringstream& Get(LogLevel log_level = kLogInfo);
public: 
    static LogLevel& ReportingLevel();
private:
    std::string LogLevelName(LogLevel log_level);
protected:
    std::ostringstream os;
private:
    LogLevel message_level;
};
} // namespace casualdb

#endif // LOGGING_H_