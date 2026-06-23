#ifndef DETECTOR_H
#define DETECTOR_H

#include <string>

class Detector
{
public:
    static bool detectIpMacConflict(
        const std::string& oldMac,
        const std::string& newMac
    );
};

#endif
