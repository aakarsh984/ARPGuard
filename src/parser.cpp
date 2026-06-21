#include "../include/parser.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <arpa/inet.h>
#include <pcap.h>

std::string Parser::macToString(const uint8_t mac[6])
{
    std::stringstream ss;

    for(int i = 0; i < 6; i++)
    {
        ss << std::hex
           << std::setw(2)
           << std::setfill('0')
           << (int)mac[i];

        if(i != 5)
            ss << ":";
    }

    return ss.str();
}

std::string Parser::ipToString(const uint8_t ip[4])
{
    return std::to_string(ip[0]) + "." +
           std::to_string(ip[1]) + "." +
           std::to_string(ip[2]) + "." +
           std::to_string(ip[3]);
}



ArpInfo Parser::parseArpPacket(const u_char* packet)
{
    const ArpHeader* arp =
        reinterpret_cast<const ArpHeader*>(packet + 14);
	ArpInfo info;
    uint16_t opcode = ntohs(arp->opcode);

    std::cout << "\n================================\n";

    if(opcode == 1)
    {
        std::cout << "ARP REQUEST\n";
    }
    else if(opcode == 2)
    {
        std::cout << "ARP REPLY\n";
    }
    else
    {
        std::cout << "UNKNOWN ARP OPCODE\n";
    }

    std::cout << "================================\n";

    std::cout << "Sender IP  : "
              << ipToString(arp->senderIP)
              << std::endl;

    std::cout << "Sender MAC : "
              << macToString(arp->senderMac)
              << std::endl;

    std::cout << "Target IP  : "
              << ipToString(arp->targetIP)
              << std::endl;

    std::cout << "Target MAC : "
              << macToString(arp->targetMac)
              << std::endl;

  info.opcode    = ntohs(arp->opcode);
    info.senderIP  = ipToString(arp->senderIP);
    info.senderMAC = macToString(arp->senderMac);
    info.targetIP  = ipToString(arp->targetIP);
    info.targetMAC = macToString(arp->targetMac);
    return info;

}
