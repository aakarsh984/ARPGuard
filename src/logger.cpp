#include "../include/logger.h"

#include <fstream>
#include <iostream>
#include <iomanip>
#include <ctime>

void Logger::logAlert(
    const std::string& severity,
    const std::string& detectionType,
    const std::string& ip,
    const std::string& oldMac,
    const std::string& newMac)
{
    // Open file in append mode
    std::ofstream logFile("../logs/alerts.log", std::ios::app);

    if (!logFile.is_open())
    {
        std::cerr << "Failed to open alerts.log\n";
        return;
    }

    // Current timestamp
    std::time_t now = std::time(nullptr);

    // Console Output
    std::cout
        << "\n=====================================\n"
        << "[" << severity << "] "
        << detectionType << "\n"
        << "IP      : " << ip << "\n"
        << "Old MAC : " << oldMac << "\n"
        << "New MAC : " << newMac << "\n"
        << "=====================================\n";

    // File Output
    logFile
        << "\n=====================================\n"
        << "Time      : "
        << std::put_time(std::localtime(&now),
                         "%Y-%m-%d %H:%M:%S")
        << "\n"
        << "Severity  : " << severity << "\n"
        << "Detection : " << detectionType << "\n"
        << "IP        : " << ip << "\n"
        << "Old MAC   : " << oldMac << "\n"
        << "New MAC   : " << newMac << "\n"
        << "=====================================\n";
}
