#include "../include/detector.h"

std::unordered_map<
    std::string,
    std::unordered_set<std::string>
> Detector::macToIPs;




bool Detector::detectIpMacConflict(
    const std::string& oldMac,
    const std::string& newMac
)
{
    return oldMac != newMac;
}



bool Detector::isGratuitousArp(
    const std::string& senderIP,
    const std::string& targetIP,
    uint16_t opcode
)
{
    return (opcode == 2) &&
           (senderIP == targetIP);
}




bool Detector::detectMultipleIpsPerMac(
    const std::string& ip,
    const std::string& mac
)
{
    macToIPs[mac].insert(ip);

    return macToIPs[mac].size() > 3;
}




bool Detector::isBroadcastMac(
    const std::string& mac
)
{
    return mac == "ff:ff:ff:ff:ff:ff" ||
           mac == "FF:FF:FF:FF:FF:FF";
}



