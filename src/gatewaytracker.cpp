#include "../include/gatewaytracker.h"

std::string GatewayTracker::gatewayIP = "";
std::string GatewayTracker::gatewayMAC = "";

void GatewayTracker::setGatewayIP(
    const std::string& ip)
{
    gatewayIP = ip;
}

std::string GatewayTracker::getGatewayIP()
{
    return gatewayIP;
}

std::string GatewayTracker::getGatewayMAC()
{
    return gatewayMAC;
}

bool GatewayTracker::learnGatewayMac(
    const std::string& ip,
    const std::string& mac)
{
    if(ip != gatewayIP)
        return false;

    if(gatewayMAC.empty())
    {
        gatewayMAC = mac;
        return true;
    }

    return false;
}

bool GatewayTracker::detectGatewayMacChange(
    const std::string& ip,
    const std::string& mac)
{
    if(ip != gatewayIP)
        return false;

    if(gatewayMAC.empty())
        return false;

    return gatewayMAC != mac;
}
