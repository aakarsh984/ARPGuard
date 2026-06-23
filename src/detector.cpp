#include "../include/detector.h"

bool Detector::detectIpMacConflict(
    const std::string& oldMac,
    const std::string& newMac
)
{
    return oldMac != newMac;
}
