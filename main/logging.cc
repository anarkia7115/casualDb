#include "main/logging.h"
#include "main/utils.h"

namespace casualdb {
std::string Log::LogLevelName(LogLevel log_level) {
    switch (log_level)
    {
    case kLogError:
        return "ERROR";
    case kLogWarning:
        return "WARNING";
    case kLogInfo:
        return "INFO";
    case kLogDebug:
        return "DEBUG";
    case kLogTrace:
        return "TRACE";
    default:
        return "UNKNOWN";
    }
}

std::ostringstream& Log::Get(LogLevel log_level) {
    os << "- " << NowTime();
    os << " [" << LogLevelName(log_level) << "] ";
    message_level = log_level;
    return os;
}

LogLevel& Log::ReportingLevel() {
    static LogLevel reporting_level = kLogTrace;
    return reporting_level;
}

Log::~Log() {
    if (message_level <= Log::ReportingLevel()) {
        os << std::endl;
        fprintf(stderr, "%s", os.str().c_str());
        fflush(stderr);
    }
}
} // namespace casualdb