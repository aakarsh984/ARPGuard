#ifndef GATEWAYTRACKER_H
#define GATEWAYTRACKER_H

#include <string>

class GatewayTracker
{
private:
    static std::string gatewayIP;
    static std::string gatewayMAC;

public:

    static void setGatewayIP(
        const std::string& ip
    );

    static bool learnGatewayMac(
        const std::string& ip,
        const std::string& mac
    );

    static bool detectGatewayMacChange(
        const std::string& ip,
        const std::string& mac
    );

    static std::string getGatewayIP();
    static std::string getGatewayMAC();
};

#endif
