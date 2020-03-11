#include "gtest/gtest.h"
#include "main/logging.h"

TEST(LoggingTest, LogTest) {
    Log::ReportingLevel() = kLogInfo;
    Log().Get(kLogInfo) << "info";
    Log().Get(kLogDebug) << "debug";
    Log().Get(kLogTrace) << "trace";
}