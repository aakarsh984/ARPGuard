#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class Logger
{
public:

    static void logAlert(
        const std::string& severity,
        const std::string& detectionType,
        const std::string& ip,
        const std::string& oldMac,
        const std::string& newMac
    );
};

#endif
