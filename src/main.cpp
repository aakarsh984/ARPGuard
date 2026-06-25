#include "../include/sniffer.h"
#include "../include/gatewaytracker.h"
#include <unistd.h>
#include<iostream>
int main(int argc, char* argv[])
{
    if (geteuid() != 0) {
        std::cerr << "Error: Run with sudo" << std::endl;
        return 1;
    }
    if (argc < 2) {
        std::cerr << "Usage: sudo ./arpguard <interface>" << std::endl;
        std::cerr << "Example: sudo ./arpguard eth1" << std::endl;
        return 1;
    }



//remeber to change it
GatewayTracker::setGatewayIP(
    "10.101.181.207"
);
    PacketSniffer sniffer;
    sniffer.listInterfaces();
    sniffer.startCapture(argv[1]);
    return 0;
}
